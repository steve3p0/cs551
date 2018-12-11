#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// A simplified version of gaussian elimination.
// row reduces an n by n+1 matrix 
// No partial pivoting here.


#define M 100


void print_matrix(double m[M][M + 1], int n)
{
    int r, c;

    for (r = 0; r < n; r++)
    {
        for (c = 0; c <= n; c++)
        {
            printf(" %10.3lf", m[r][c]);
        }
        printf("\n");

    }
    printf("\n");
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


int demo()
{

    double m[M][M + 1];
    int n, r, c;
    double x[M];
    int s;

    scanf("%d", &n);;   // n = number of equations

    // Input data defining your equations

    for (r = 0; r < n; r++)
    {
        for (c = 0; c <= n; c++)
        {
            scanf("%lf", &m[r][c]);
        }
    }



    // Output the original form
    print_matrix(m, n);

    s = gaussian_elimination(m, n, x);
    if (s == 0)
    {
        printf("Simple gaussian_elimination fails.\n");
        printf("A smarter version might succeed.\n");
        exit(0);
    }

    // Output the modified form
    print_matrix(m, n);

    // Ouptut the solution
    for (r = 0; r < n; r++)
    {
        printf("%.16lf\n", x[r]);
    }
    printf("\n");

}

