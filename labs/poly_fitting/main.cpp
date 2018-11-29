//Polynomial Fit
#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std;

#include <stdio.h>
#include <string.h>
#include <ctype.h>


int main()
{
    int i,j,k,n,N;

    //set precision
    cout.precision(4);
    cout.setf(ios::fixed);

    //To find the size of arrays that will store x,y, and z values
    int degree;
    printf("\n\tEnter the no. of data pairs to be entered: ");
    scanf("%d", &N);

    double x[N],y[N];

    //Input x-values
    printf("\nEnter the x-axis values:\n");
    for (i = 0; i < N; i++)
    {
        scanf("%lf", &x[i]);
    }

    //Input y-values
    printf("\nEnter the y-axis values:\n");
    for (i = 0; i < N; i++)
    {
        scanf("%lf", &y[i]);
    }

    // n is the degree of Polynomial
    printf("\nWhat degree of Polynomial do you want to use for the fit?\n");
    scanf("%d", &n);

    // Array that will store the values of sigma(xi),
    // sigma(xi^2),sigma(xi^3)....sigma(xi^2n)
    double X[2 * n + 1];

    for (i = 0; i < 2 * n + 1; i++)
    {
        X[i]=0;

        // consecutive positions of the array will store N,
        // sigma(xi),sigma(xi^2),sigma(xi^3)....sigma(xi^2n)
        for (j = 0; j < N; j++)
        {
            X[i] = X[i] + pow(x[j], i);
        }
    }

    // B is the Normal matrix(augmented) that will store the equations,
    // 'a' is for value of the final coefficients
    double B[n + 1][n + 2], a[n + 1];

    for (i = 0; i <= n; i++)
    {
        // Build the Normal matrix by storing the corresponding coefficients
        // at the right positions except the last column of the matrix
        for (j = 0; j<= n; j++)
        {
            B[i][j] = X[i + j];
        }
    }

    // Array to store the values of sigma(yi),sigma(xi*yi),sigma(xi^2*yi)...sigma(xi^n*yi)
    double Y[n + 1];
    for (i = 0;i < n + 1; i++)
    {
        Y[i] = 0;

        // consecutive positions will store sigma(yi),
        // sigma(xi*yi),sigma(xi^2*yi)...sigma(xi^n*yi)
        for (j = 0; j < N; j++)
        {
            Y[i] = Y[i] + pow(x[j], i) * y[j];
        }
    }

    // load the values of Y as the last column of B(Normal Matrix but augmented)
    for (i = 0; i <= n; i++)
    {
        B[i][n + 1] = Y[i];
    }

    // n is made n+1 because the Gaussian Elimination part below was for n equations,
    // but here n is the degree of polynomial and for n degree we get n+1 equations
    n = n + 1;

    printf("\nThe Normal(Augmented Matrix) is as follows:\n");
    // print the Normal-augmented matrix
    for (i = 0; i < n; i++)
    {
        for (j = 0; j <= n; j++)
        {
            printf("%f\t", B[i][j]);
        }

        printf("\n");
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // From now Gaussian Elimination starts(can be ignored)
    // to solve the set of linear equations (Pivotisation)
    for (i = 0; i < n; i++)
    {
        for (k = i + 1; k < n; k++)
        {
            if (B[i][i] < B[k][i])
            {
                for (j = 0; j <= n; j++)
                {
                    double temp = B[i][j];
                    B[i][j] = B[k][j];
                    B[k][j] = temp;
                }

            }
        }
    }

    // loop to perform the gauss elimination
    for (i = 0; i < n - 1; i++)
    {
        for (k = i + 1; k < n; k++)
        {
            double t = B[k][i] / B[i][i];
            for (j = 0; j <= n; j++)
            {
                //make the elements below the pivot elements equal to zero or elimnate the variables
                B[k][j] = B[k][j] - t *  B[i][j];
            }

        }
    }

    // back-substitution
    for (i = n - 1; i >= 0; i--)
    {
        // x is an array whose values correspond to the values of x,y,z..
        a[i] = B[i][n];

        // make the variable to be calculated equal to the rhs of the last equation
        for (j = 0; j < n; j++)
        {
            //t hen subtract all the lhs values except the coefficient
            // of the variable whose value is being calculated
            if (j != i)
            {
                a[i] = a[i] - B[i][j] * a[j];
            }
        }

        // now finally divide the rhs by the coefficient of the variable to be calculated
        a[i] = a[i] / B[i][i];
    }

    printf("\nThe values of the coefficients are as follows:\n");
    for (i = 0; i < n; i++)
    {
        // Print the values of x^0,x^1,x^2,x^3,....
        //cout << "x^" << i << "=" << a[i] << endl;
        printf("x^%d = %f\n", i, a[i]);
    }

    printf("\nHence the fitted Polynomial is given by:\ny = ");
    for (i=0;i<n;i++)
    {
        //cout << " + (" << a[i] << ")" << "x^" << i;
        printf(" + (%f)x^%d", a[i], i);

    }

    printf("\n");

    return 0;

}