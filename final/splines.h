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

#include <unistd.h>

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

    //double *coefficients;
    double coefficients[M];

    double *A;  // A Coefficients
    double *B;  // B Coefficients

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

    s->A = (double*)malloc(M*sizeof(double));
    s->B = (double*)malloc(M*sizeof(double));
}

/* Read File as Data Points
 * Read data from the file into n (number of points) and the x and y arrays
 */
void *read_file(Spline *s)
{
    // Get current working directory
    char cwd[100];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("Current working dir: %s\n", cwd);
    }

    printf("Enter in a filename: ");
    char filename[100];
    scanf("%s", filename);

    FILE *f = fopen(filename, "r");
    //FILE *f = fopen("/home/steve/workspace_psu/cs551/final/spline_test_data_2", "r");
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

/* C1(x) = a0 + a1x^2 + a2x^3
 * from 2nd page of Final Project Assignement
 */
double C(double *x, double *y, int i, int x_coord, double *A, double *B)
{
    double y_point =  y[i] + ((y[i + 1] - y[i]) / (x[i + 1] - x[i])) * (x_coord - x[i])
                      + A[i] *    (x_coord - x[i])    * (x_coord - x[i + 1])
                      + B[i] * pow(x_coord - x[i], 2) * (x_coord - x[i + 1]);

    return y_point;
}

/* Calculate Natural Splines
 * Process the calculations for loading the tridiagonal matrix
 */
void *calculate(Spline *s)
{
    load_diagonals(s);


    for (int i = 0; i < s->d; i++)
    {
        s->tridiagonal[i][i]     = s->D[i];
        s->tridiagonal[i][i + 1] = s->R[i];
        s->tridiagonal[i + 1][i] = s->L[i + 1];
        s->tridiagonal[i][s->d]  = s->Q[i];
    }

    s->Print(s);

    // do gaussian elimination
    gaussian_elimination(s->tridiagonal, s->d, s->coefficients);

    int i;
    int j;
    for (i = 0, j = 0; i < s->d; i += 2, j++)
    {
        s->A[j] = s->coefficients[i];
        s->B[j] = s->coefficients[i + 1];
    }


    // for each data point
    for (int i = 0; i < s->n; i++)
    {
        // range of spline: x[i] to x[i+1]
        for (int j = s->x[i]; j < s->x[i + 1]; j++)
        {
            // Plot Cubic Spline
            G_point(j, C(s->x, s->y, i, j, s->A, s->B));
        }
    }

    G_wait_key();

    printf("\tLog - calculate: Splines successfully calculated...\n");
}




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



