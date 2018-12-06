/* Natural Splines Interpolation Library
 * Steve Braich
 * CS 551
 *
 * References:
 *   - https://en.wikipedia.org/wiki/Spline_interpolation
 *   - https://en.wikipedia.org/wiki/Spline_(mathematics)
 */

#ifndef SPLINES_H
#define SPLINES_H

#define M 100

typedef struct spline
{
    int n;
    int d;

    double *x;
    double *y;

    double *D;
    double *R;
    double *L;
    double *Q;
    double *X;

    double *A;
    double *B;

    // member methods
    //void (*new)(struct Spline *);
    //void (*spline)(*spline);

    // Load is set to read from a file by default
    // This can be overridden by the client main function (user clicks)
    void (*Load) ();
    void (*Init) ();
    void (*Calculate) ();
    void (*Print)(const struct spline*);

    // Draw is virtual.  It must be defined in the client
    void (*Draw) ();

    // Deconstructor
    void (*Destroy)();

} Spline;

double *load_diagonals(Spline *s, int index, double initial, double *diagonal)
{
    diagonal[index] = initial;
    for (int i = index; i < s->d - 1; i++)
    {
        if (i % 2)
        {
            diagonal[i] = pow(s->x[index] - s->x[index - 1], 2);
        }
        else
        {
            index++;
            diagonal[i] = -(s->x[index] - s->x[index - 2]);
        }
    }

    return diagonal;
}

void load_D0(Spline *s)
{
    int tempN = 1;
    s->D[0] = 1;
    s->D[s->d - 1] = 2 * (s->x[s->n - 1] - s->x[s->n - 2]);

    for (int i = 1; i < s->d - 1; ++i)
    {
        if (i % 2 != 0)
        {
            ++tempN;
            s->D[i] = -(s->x[tempN] - s->x[tempN - 2]);
        }
    }

    for (int i = 2; i < s->d - 1; ++i)
    {
        if (i % 2)
        {
            s->D[i] = pow(s->x[tempN] - s->x[tempN - 1], 2);
        }
    }
}

void load_D1(Spline *s)
{
    int tempN = 1;
    s->D[0] = 1;
    s->D[s->d - 1] = 2 * (s->x[s->n - 1] - s->x[s->n - 2]);
    for (int i = 1; i < s->d - 1; ++i)
    {
        if (i % 2)
        {
            s->D[i] = pow(s->x[tempN] - s->x[tempN - 1], 2);
        }
        else
        {
            ++tempN;
            s->D[i] = -(s->x[tempN] - s->x[tempN - 2]);
        }
    }
}

void load_D(Spline *s)
{
    // A2, A3, A4, A5
    // A2 = x21 = -(x2 - x1)
    // A3 = x32 = -(x3 - x2)
    // A4 = x43 = -(x4 - x3)
    // A5 = x54 = -(x5 - x4)
    // Start at [0] till length of diagonal, step by 2
    int i, j;

    for (i = 0, j = 0; i < s->d - 1; i += 2, j++)
    {
        s->D[i]   = -(s->x[j + 1] - s->x[j - 1]);
        s->L[i+1] =  (s->x[j + 1] - s->x[j]);
        s->R[i+1] =   s->x[j + 2] - s->x[j + 1];

        //s->R[i] = s->x[tempN + 1] - s->x[tempN];
        printf("D[%d] = %lf\n", i, s->D[i]);
    }

    // B1, B2, B3, B4, B5... Bn-1
    // B1 = x10^2 = (x1 - x0)^2
    // B2 = x21^2 = (x2 - x1)^2
    // B3 = x32^2 = (x3 - x2)^2
    // B4 = x43^2 = (x4 - x3)^2
    // B5 = x53^2 = (x5 - x4)^2
    // Start at [1] till length of diagonal, step by 2

    for (i = 1, j = 1; i < s->d - 1; i += 2, j++)
    {
        s->D[i]     = pow(s->x[j] - s->x[j - 1], 2);
        s->L[i + 1] = pow(s->x[j] - s->x[j - 1], 2);
        s->R[i - 1] = (s->x[j - 1] - s->x[j - 2]) * (s->x[j] - s->x[j - 1]);

        printf("D[%d] = %lf\n", i, s->D[i]);
    }

    // A1 = 1
    // Set left side of D to 1
    s->D[0] = 1;
    // An-1
    // Set right side of D to the derivative
    s->D[s->d - 1] = 2 * (s->x[s->n - 1] - s->x[s->n - 2]);

    // Set right side of L cubic to 1
    s->L[s->d - 1] = 1;

    // Set right side to negative of the left side of L
    s->R[0] = -(s->x[1] - s->x[0]);

    // Set the right side of R (for loop doesn't hit last element of R)
    s->R[i - 1] = (s->x[j - 1] - s->x[j - 2]) * (s->x[j] - s->x[j - 1]);

}

double *load_L(Spline *s)
{
    int tempN = 0;
    for (int i = 0; i < s->d - 1; ++i)
    {
        if (i % 2)
        {
            s->L[i] = s->x[tempN + 1] - s->x[tempN];
            ++tempN;
        }
        else
        {
            s->L[i] = pow(s->x[tempN] - s->x[tempN - 1], 2);
        }
    }

}

double load_R(Spline *s)
{
    //building R
    int tempN = 1;
    s->R[0] = -(s->x[1] - s->x[0]);
    for (int i = 1; i < s->d - 1; ++i)
    {
        if (i % 2)
        {
            s->R[i] = s->x[tempN + 1] - s->x[tempN];
        }
        else
        {
            ++tempN;
            s->R[i] = (s->x[tempN - 1] - s->x[tempN - 2]) * (s->x[tempN] - s->x[tempN - 1]);
        }
    }
}

double load_Q(Spline *s)
{
    int tempN = 1;
    s->Q[0] = 0;
    s->Q[s->d - 1] = 0;
    for (int i = 1; i < s->d - 1; ++i)
    {
        if (i % 2)
        {
            s->Q[i] = ((s->y[tempN + 1] - s->y[tempN]) / (s->x[tempN + 1] - s->x[tempN]))
                      - ((s->y[tempN] - s->y[tempN - 1]) / (s->x[tempN] - s->x[tempN - 1]));
        }
        else
        {
            ++tempN;
            s->Q[i] = -s->Q[i - 1];
        }
    }
}

double **load_M()
{}

double *load_X()
{}

void init(Spline *s)
{
    s->d = 2 * (s->n - 1);

    s->x = (double*)malloc(M*sizeof(double));
    s->y = (double*)malloc(M*sizeof(double));

    s->D = (double*)malloc(M*sizeof(double));
    s->L = (double*)malloc(M*sizeof(double));
    s->R = (double*)malloc(M*sizeof(double));
    s->Q = (double*)malloc(M*sizeof(double));

    s->X = (double*)malloc(M*sizeof(double));
}

/* Read File as Data Points
 * Read data from the file into n (number of points) and the x and y arrays
 */
void *read_file(Spline *s)
{
    FILE *f = fopen("/home/steve/workspace_psu/cs551/final/spline_test_data_2", "r");
    //FILE *f = fopen("/home/steve/workspace_psu/cs551/final/final_test_1_input", "r");

    if (f == NULL)
    {
        printf("File I/O Error");
        exit(0);
    }

    fscanf(f, "%d", &s->n);

    s->Init(s);

    for (int i = 0; i < s->n; i++)
    {
        fscanf(f, "%lf %lf\n", &s->x[i], &s->y[i]);
        //G_load_rectangle(x[i] - 2.0, y[i] - 2.0, 5.0, 5.0);
    }

    fclose(f);

    printf("\tLog - read_file: Splines successfully read from file...\n");
}

/* Calculate Natural Splines
 * Process the calculations for loading the tridiagonal matrix
 */
void *calculate(Spline *s)
{
    for (int i = 0; i < s->n; ++i) printf("point %d\tx: %lf\ty: %lf\n", i + 1, s->x[i], s->y[i]);

    load_D(s);
    printf("\n"); for (int i = 0; i < s->d; i+=2) printf("D[%d] = %lf\n", i, s->D[i]);
    //load_L(s);
    printf("\n"); for (int i = 0; i < s->d; ++i) printf("L[%d] = %lf\n", i, s->L[i]);
    //load_R(s);
    printf("\n"); for (int i = 0; i < s->d; ++i) printf("R[%d] = %lf\n", i, s->R[i]);
    load_Q(s);
    printf("\n"); for (int i = 0; i < s->d; ++i) printf("R[%d] = %lf\n", i, s->Q[i]);




    double **tri_matrix = load_M();

    // do gaussian elimination

    // draw cubic
    for (int i = 1; i <= s->n; ++i)
    {


        //G_wait_key();
    }

    //G_wait_key();

    printf("\tLog - calculate: Splines successfully calculated...\n");
}

//void *print(Spline *s)
//{
//    for (int i = 0; i < diagLength; i++)
//    {
//        for (int j = 0; j < diagLength; j++)
//        {
//            printf(" %10.3lf", points[i][j]);
//        }
//        printf("\n");
//    }
//}

/* Print Tridiagonal Matrix
 * Print out the matrix in tridiagonal form specified by Dr. Ely
 */
void *print(Spline *s)
{
    int i;
    double m;


    /*
      printing the 4 arrays that make up the important tri-diagonal matrix information.
      D is an array containing the diagonal information along the main diagonal.
      L is an array containing the diagonal information left of the main diagonal.
      R is an array containing the diagonal information left of the main diagonal.
      Q is an array containing the vertical information along the far right column (the constants).

      For the code below to print the tri-diagonal matrix nicely, you must have properly created D, L, R, and Q.
      This print is not appropriate if you plan to solve an N x N+1 matrix, but gives you the basic idea behind a good looking print...
      ... examine the printf statements below.
    */
    int r, c;
    double v;
    printf("\n");
    printf("The tri-diagonal matrix is : \n");
    for (r = 0; r < s->d; r++)
    {
        for (c = 0; c <= s->d; c++)
        {
            if (c == s->d)
            {
                v = s->Q[r];
                printf(" %10.3lf", v);
            }
            else if (c == r)
            {
                v = s->D[r];
                printf(" %10.3lf", v);
            }
            else if (c == r + 1)
            {
                v = s->R[r];
                printf(" %10.3lf", v);
            }
            else if (c == r - 1)
            {
                v = s->L[r];
                printf(" %10.3lf", v);
            }
            else
            {
                v = 0;
                printf("-----------");
            }
        }
        printf("\n");
    }
    printf("\tLog - print: Splines successfully printed...\n");
}

/* Deconstructor
 * Free up any memory used by spline
 */
void *destroy(Spline *s)
{

    //free(s->D);

    realloc(s->x, 0);
    realloc(s->y, 0);

    realloc(s->D, 0);
    realloc(s->R, 0);
    realloc(s->L, 0);
    realloc(s->Q, 0);

    realloc(s->X, 0);

    realloc(s, 0);

    printf("\tLog - destroy: Splines successfully deallocated...\n");
}

/* Constructor for spline object
 * Allocate memory for spline object and intialize values
 */
Spline *new()
{
    Spline *s = (Spline*)malloc(sizeof(Spline));

    s->n = 0;

    // Load is set to read from a file by default
    // This can be overridden by the client main function (user clicks)
    s->Load = read_file;
    s->Calculate = calculate;
    s->Print = print;

    // Draw is virtual.  It must be defined in the client
    //s->Draw = draw;
    s->Destroy = destroy;

    // Private members
    s->Init = init;

    printf("\tLog - new: Splines successfully allocated...\n");

    return s;
}


#endif //SPLINES_H



