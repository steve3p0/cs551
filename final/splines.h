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
    double *x;
    double *y;

    double *D;
    double *R;
    double *L;
    double *Q;
    double *X;

    // member methods
    //void (*new)(struct Spline *);
    //void (*spline)(*spline);

    // Load is set to read from a file by default
    // This can be overridden by the client main function (user clicks)
    void (*Load) ();
    void (*Calculate) ();
    void (*Print)(const struct spline*);

    // Draw is virtual.  It must be defined in the client
    void (*Draw) ();

    // Deconstructor
    void (*Destroy)();


} Spline;

double *fill_D(int n, double *x)
{
    double d[M];
    d[0] = 1;
    //d[diagonal_length - 1] = 2 * (x[n - 1] - x[n - 2]);

    int i;
//    for (i = 1; i < diagonal - 1; ++i)
//    {
//        /// ...
//    }

    return d;
}

double *fill_R(int n, double *x)
{
    double r[M]; // diagonal length
    r[0] = 1;
    //d[diagonal_length - 1] = 2 * (x[n - 1] - x[n - 2]);

    int i;
//    for (i = 1; i < diagonal - 1; ++i)
//    {
//        /// ...
//    }

    return r;
}

double *fill_L(int n,double *x)
{
    double L[M]; // diagonal length
    L[0] = 1;
    //d[diagonal_length - 1] = 2 * (x[n - 1] - x[n - 2]);

    int i;
//    for (i = 1; i < diagonal - 1; ++i)
//    {
//        /// ...
//    }

    return L;
}

double *fill_Q(int n,double *x)
{
    double Q[M];
    Q[0] = 1;

    int i;
//    for (i = 1; i < diagonal - 1; ++i)
//    {
//        /// ...
//    }

    return Q;
}

double **fill_M()
{}

double *fill_X()
{}

/* Read File as Data Points
 * Read data from the file into n (number of points) and the x and y arrays
 */
void *read_file(Spline *s)
{
    //FILE *f = fopen("/home/steve/workspace_psu/cs551/final.v2/spline_test_data_2", "r");
    FILE *f = fopen("/home/steve/workspace_psu/cs551/final.v2/final_test_1_input", "r");

    if (f == NULL)
    {
        printf("File I/O Error");
        exit(0);
    }

    fscanf(f, "%d", &s->n);

    for (int i = 0; i < s->n; i++)
    {
        fscanf(f, "%lf %lf\n", &s->x[i], &s->y[i]);
        //G_fill_rectangle(x[i] - 2.0, y[i] - 2.0, 5.0, 5.0);
    }

    fclose(f);

    printf("\tLog - tread_file: Splines successfully read from file...\n");
}

/* Calculate Natural Splines
 * Process the calculations for loading the tridiagonal matrix
 */
void *calculate(Spline *s)
{
    int n;
    double *x;
    double *y;

    int i;
    //int s;
    char q;
    double p[2];
    double u;
    double v;

    int diagonal = 2 * (n - 1);

    double *D = fill_D(n, x);
    double *R = fill_R(n, x);
    double *L = fill_R(n, x);
    double *Q = fill_Q(n, x);

    //print_tridiagonal(n, L, D, R, Q);

    double **tri_matrix = fill_M();

    // do gaussian elimination

    // draw cubic
    for (i = 1; i <= n; ++i)
    {


        //G_wait_key();
    }

    //G_wait_key();

    printf("\tLog - calculate: Splines successfully calculated...\n");
}

/* Print Tridiagonal Matrix
 * Print out the matrix in tridiagonal form specified by Dr. Ely
 */
void *print(Spline *s)
{

    printf("\tLog - tprint: Splines successfully printed...\n");
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
    s->x = (double*)malloc(M*sizeof(double));
    s->y = (double*)malloc(M*sizeof(double));

    s->D = (double*)malloc(M*sizeof(double));
    s->L = (double*)malloc(M*sizeof(double));
    s->R = (double*)malloc(M*sizeof(double));
    s->Q = (double*)malloc(M*sizeof(double));

    s->X = (double*)malloc(M*sizeof(double));

    // Load is set to read from a file by default
    // This can be overridden by the client main function (user clicks)
    s->Load = read_file;
    s->Calculate = calculate;
    s->Print = print;

    // Draw is virtual.  It must be defined in the client
    //s->Draw = draw;
    s->Destroy = destroy;

    printf("\tLog - new: Splines successfully allocated...\n");

    return s;
}

#endif //SPLINES_H



