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
    int n;      // n number of x,y data points
    int d;      // diagonal length

    double *x;  // x-coordinate
    double *y;  // y-coordinate

    double *D;  // Middle Diagonal
    double *R;  // Right Diagonal
    double *L;  // Left Diagonal
    double *Q;  // Q Vector

    //double **tridiagonal;
    double tridiagonal[M][M + 1];

    //double *X;
    double X[M];

    double *A;  // A Coefficients
    double *B;  // B Coefficients

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

void init(Spline *s)
{
    s->d = 2 * (s->n - 1);

    s->x = (double*)malloc(M*sizeof(double));
    s->y = (double*)malloc(M*sizeof(double));

    s->D = (double*)malloc(M*sizeof(double));
    s->L = (double*)malloc(M*sizeof(double));
    s->R = (double*)malloc(M*sizeof(double));
    s->Q = (double*)malloc(M*sizeof(double));

    for (int i = 0; i < s->d + 1; ++i)
        for (int j = 0; j < s->d; ++j)
            s->tridiagonal[i][j] = 0;

    //s->X = (double*)malloc(M*sizeof(double));
}

/* Read File as Data Points
 * Read data from the file into n (number of points) and the x and y arrays
 */
void *read_file(Spline *s)
{
    //FILE *f = fopen("/home/steve/workspace_psu/cs551/final/spline_test_data_2", "r");
    FILE *f = fopen("/home/steve/workspace_psu/cs551/final/final_test_1_input", "r");

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
        //TODO: G_load_rectangle(x[i] - 2.0, y[i] - 2.0, 5.0, 5.0);
    }

    fclose(f);

    printf("\tLog - read_file: Splines successfully read from file...\n");
}

/* Print Matrix
 * Print a 2-D Array. Used for Debugging
 */
void print_matrix(double m[M][M + 1], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n + 1; j++)
        {
            printf(" %10.6lf", m[i][j]);
        }
        printf("\n");
    }
}

int gaussian_elimination(double m[M][M + 1], int n, double x[M])
// return 1 for success, 0 for failure
{
    int i, j, k;
    double v, sum;

    // reduce matrix to upper triangular form

    for (j = 0; j < n - 1; j++)
    {

        // print_matrix(m,n) ;

        if (m[j][j] == 0)
        { return 0; }

        for (k = j + 1; k < n; k++)
        {

            v = m[k][j] / m[j][j];
            for (i = 0; i <= n; i++)
            {
                m[k][i] = m[k][i] - v * m[j][i];
            }

        }


    }

    // Output the upper triangular form
    //   print_matrix(m,n) ;


    // Now do the back substitution
    for (j = n - 1; j >= 0; j--)
    {

        sum = 0.0;
        for (k = j + 1; k < n; k++)
        {
            sum += (m[j][k] * x[k]);
        }

        if (m[j][j] == 0)
        { return 0; }

        x[j] = (m[j][n] - sum) / m[j][j];
    }


    return 1;
}

void load_diagonals(Spline *s)
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
        s->D[i]     = -(s->x[j + 1] - s->x[j - 1]);
        s->L[i + 1] =   s->x[j + 1] - s->x[j];
        s->R[i + 1] =   s->x[j + 2] - s->x[j + 1];

        s->Q[i - 1] = ((s->y[j + 1] - s->y[j])     / (s->x[j + 1] - s->x[j]))
                      - ((s->y[j]     - s->y[j - 1]) / (s->x[j]     - s->x[j - 1]));

        //printf("D[%d] = %lf\n", i, s->D[i]);
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

        s->Q[i + 1] = -s->Q[i];

        //printf("D[%d] = %lf\n", i, s->D[i]);
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

    s->Q[0] = 0;
    s->Q[s->d - 1] = 0;
}

/* Calculate Natural Splines
 * Process the calculations for loading the tridiagonal matrix
 */
void *calculate(Spline *s)
{
    for (int i = 0; i < s->n; ++i) printf("point %d\tx: %lf\ty: %lf\n", i + 1, s->x[i], s->y[i]);

    load_diagonals(s);

//    printf("\n"); for (int i = 0; i < s->d; i++) printf("D[%d] = %lf\n", i, s->D[i]);
//    printf("\n"); for (int i = 0; i < s->d; i++) printf("L[%d] = %lf\n", i, s->L[i]);
//    printf("\n"); for (int i = 0; i < s->d; i++) printf("R[%d] = %lf\n", i, s->R[i]);
//    printf("\n"); for (int i = 0; i < s->d; i++) printf("R[%d] = %lf\n", i, s->Q[i]);

    for (int i = 0; i < s->d; i++)
    {
        s->tridiagonal[i][i]     = s->D[i];
        s->tridiagonal[i][i + 1] = s->R[i];
        s->tridiagonal[i + 1][i] = s->L[i + 1];
        s->tridiagonal[i][s->d]  = s->Q[i];
    }

    s->Print(s);

    printf("DEBUG: print tridiagonal matrix.... LET'S TAKE A LOOKN\n");
    //print_matrix(s->tridiagonal, M);
    print_matrix(s->tridiagonal, s->d);

    // do gaussian elimination
    gaussian_elimination(s->tridiagonal, s->d, s->X);

    printf("DEBUG: print X matrix.... GAUSSIAN ELIMINATION\n");
    print_matrix(s->X, s->d);

//    int tA = 0;
//    int tB = 0;
//    double A[999], B[999];
//    for (int i = 0; i < s->d; i++)
//    {
//        if (i % 2)
//        {
//            B[tB] = s->X[i];
//            ++tB;
//        }
//        else
//        {
//            A[tA] = s->X[i];
//            ++tA;
//        }
//    }

    int i;
    int j;
    double A[10], B[10];
    for (i = 0, j = 0; i < s->d; i += 2, j++)
    {
        A[j] = s->X[i];
        B[j] = s->X[i + 1];
    }

//    printf("\n"); for (int i = 0; i < s->d; i++) printf("A[%d] = %lf\n", i, A[i]);
//    printf("\n"); for (int i = 0; i < s->d; i++) printf("B[%d] = %lf\n", i, B[i]);

    double yVal = 0;
    for (int i = 0; i < s->n; i++)
    {
        for (int j = s->x[i]; j < s->x[i + 1]; j++)
        {
            yVal = s->y[i] + ((s->y[i + 1] - s->y[i]) / (s->x[i + 1] - s->x[i])) * (j - s->x[i])
                   + A[i] *    (j - s->x[i])    * (j - s->x[i + 1])
                   + B[i] * pow(j - s->x[i], 2) * (j - s->x[i + 1]);
            G_point(j, yVal);
        }
    }

//    double yVal = 0;
//    for (int i = 1; i <= s->n; ++i)
//    {
//        for (int j = s->x[i - 1]; j < s->x[i]; ++j)
//        {
//            yVal = s->y[i - 1] + ((s->y[i] - s->y[i - 1]) / (s->x[i] - s->x[i - 1])) * (j - s->x[i - 1])
//                   + A[i - 1] *    (j - s->x[i - 1])    * (j - s->x[i])
//                   + B[i - 1] * pow(j - s->x[i - 1], 2) * (j - s->x[i]);
//            G_point(j, yVal);
//        }
//    }

    G_wait_key();

    printf("\tLog - calculate: Splines successfully calculated...\n");
}

//double C(double )
//{
//
//    yVal = s->y[i - 1] + ((s->y[i] - s->y[i - 1]) / (s->x[i] - s->x[i - 1])) * (j - s->x[i - 1])
//           + A[i - 1] * (j - s->x[i - 1]) * (j - s->x[i])
//           + B[i - 1] * pow(j - s->x[i - 1], 2) * (j - s->x[i]);
//
//    yVal = s->y[i - 1] + ((s->y[i] - s->y[i - 1]) / (s->x[i] - s->x[i - 1])) * (j - s->x[i - 1])
//           + A[i - 1] * (j - s->x[i - 1]) * (j - s->x[i])
//           + B[i - 1] * pow(j - s->x[i - 1], 2) * (j - s->x[i]);
//
//    return 0;
//}


/* Print Tridiagonal Matrix
 * Print the matrix in the format specified by Dr. Ely
 */
void *print_tridiagonal(Spline *s)
{
    for (int i = 0; i < s->d; i++)
    {
        for (int j = 0; j < s->d + 1; j++)
        {
            if (s->tridiagonal[i][j] != 0 || j == s->d)
            {
                printf(" %10.3lf", s->tridiagonal[i][j]);
            }
            else
            {
                printf("-----------");
            }
        }
        printf("\n");
    }

    printf("\tLog - print: Tridiagonal matrix successfully printed...\n");
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
    //realloc(s->R, 0);
    //realloc(s->L, 0);
    //realloc(s->Q, 0);

    //realloc(s->tridiagonal, 0);

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
    s->Print = print_tridiagonal;

    // Draw is virtual.  It must be defined in the client
    //s->Draw = draw;
    s->Destroy = destroy;

    // Private members
    s->Init = init;

    printf("\tLog - new: Splines successfully allocated...\n");

    return s;
}


#endif //SPLINES_H



