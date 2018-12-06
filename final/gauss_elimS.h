#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// A simplified version of gaussian elimination.
// row reduces an n by n+1 matrix 
// No partial pivoting here.

#define M 100



void print_matrix (double m[M][M+1], int n)
{
    int r;
    for (r = 0; r < n; r++)
    {
        int c;
        for (c = 0; c <= n; c++)
        {
            printf("%.16lf ", m[r][c]);
        }
        printf("\n");
    }

    printf("\n");
}

// return 1 for success, 0 for failure
int gaussian_elimination(double m[M][M + 1], int n, double x[M])
//int gaussian_elimination(double **m, int n, double *x)
{
    double v;
    double sum;

    // reduce matrix to upper triangular form
    int j;
    for (j = 0; j < n - 1; j++)
    {
        // print_matrix(m,n) ;
        if (m[j][j] == 0) return 0;

        int k;
        for (k = j + 1; k < n; k++)
        {
            v = m[k][j] / m[j][j];

            int i;
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

        int k;
        for (k = j + 1; k < n; k++)
        {
            sum += (m[j][k] * x[k]);
        }

        if (m[j][j] == 0) return 0;

        x[j] = (m[j][n] - sum) / m[j][j];
    }

    return 1;
}

int demo_gauss_elim()
{
    // n = number of equations
    printf("Enter in the number of equations: \n");
    int n;
    scanf("%d", &n);

    // Input data defining your equations
    double m[M][M + 1];
    int r;
    for (r = 0; r < n; r++)
    {
        int c;
        for (c = 0; c <= n; c++)
        {
            scanf("%lf", &m[r][c]);
        }
    }

    // Output the original form
    print_matrix(m, n) ;

    double x[M];
    int s = gaussian_elimination(m, n, x);
    if (s == 0)
    {
        printf("Simple gaussian_elimination fails.\n");
        printf("A smarter version might succeed.\n");
        return 0;
    }

    // Output the modified form
    print_matrix(m, n);

    // Ouptut the solution
    for (r = 0; r < n; r++)
    {
        printf("%.16lf\n", x[r]);
    }

    printf("\n") ;

    return 1;
}

/////////////////////////////////////////////////////////////

/*******
 Function that performs Gauss-Elimination and returns the Upper triangular matrix and solution of equations:
There are two options to do this in C.
1. Pass the augmented matrix (a) as the parameter, and calculate and store the upperTriangular(Gauss-Eliminated Matrix) in it.
2. Use malloc and make the function of pointer type and return the pointer.
This program uses the first option.
********/
void gaussEliminationLS(int m, int n, double a[m][n], double x[n - 1])
{
    int i;
    for (i = 0; i < m - 1; i++)
    {
        /*//Partial Pivoting
        for(k=i+1;k<m;k++){
            //If diagonal element(absolute vallue) is smaller than any of the terms below it
            if(fabs(a[i][i])<fabs(a[k][i])){
                //Swap the rows
                for(j=0;j<n;j++){
                    double temp;
                    temp=a[i][j];
                    a[i][j]=a[k][j];
                    a[k][j]=temp;
                }
            }
        }*/

        // Begin Gauss Elimination
        int k;
        for (k = i + 1; k < m; k++)
        {
            double term = a[k][i] / a[i][i];

            int j;
            for(j = 0; j < n; j++)
            {
                a[k][j] = a[k][j] - term * a[i][j];
            }
        }
    }

    // Begin Back-substitution
    for(i = m - 1; i >= 0; i--)
    {
        x[i] = a[i][n-1];

        int j;
        for (j = i + 1; j < n - 1; j++)
        {
            x[i] = x[i] - a[i][j] * x[j];
        }

        x[i] = x[i] / a[i][i];
    }
}

/*******
Function that copies the elements of a matrix to another matrix
Parameters: rows(m),columns(n),matrix1[m][n] , matrix2[m][n]
*******/
void copyMatrix(int m, int n, double matrix1[m][n], double matrix2[m][n]){
    int i,j;
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            matrix2[i][j]=matrix1[i][j];
        }
    }
}

/*******
Function that prints the elements of a matrix row-wise
Parameters: rows(m),columns(n),matrix[m][n]
*******/
void printMatrix(int m, int n, double matrix[m][n]){
    int i,j;
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            printf("%lf\t",matrix[i][j]);
        }
        printf("\n");
    }
}

//gaussian_elimination(double m[M][M + 1], int n, double x[M])
//gaussian_elimination(tri, n, sigTemp);
//gaussian_elimination(tri, n - 1, sigTemp);