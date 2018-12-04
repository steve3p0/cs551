/*************************************************
*************CUBIC SPLINE PROGRAM*****************
*************************************************
The program asks the user to enter the data-points and then returns the cubic splines equations
for each interval
Equation for ith interval being:
ai(x-xi)^3+bi(x-xi)^2+ci(x-xi)+di*/

#include<stdio.h>
#include<math.h>
#include "FPToolkit.h"
#include "splines.h"
#include "gauss_elimS.h"


void saveUserClicks(Point *data, int size)
{
    double tmp[2];

    // Fill the data points array with user clicks
    for(int i = 0; i < size; ++i)
    {
        // Wait for the user to click
        G_wait_click(tmp);

        // What is this doing?
        G_fill_circle(tmp[0], tmp[1], 2);

        // Convert double[2] to Point typedef
        data[i].x = tmp[0];
        data[i].y = tmp[1];
    }
}

int main()
{
    int m;

    printf("Enter the no. of data-points:\n");
    scanf("%d", &m);

    int n = m - 1;  //Now (n+1) is the total no. of data-points, following our convention
    double x[n + 1]; //array to store the x-axis points
    double y[n + 1]; //array to store the y-axis points

    printf("Enter the x-axis values:\n");
    int i;
    for (i = 0; i < n + 1; i++)
    {
        scanf("%lf", &x[i]);
    }

    printf("Enter the y-axis values:\n");
    for (i = 0; i < n + 1; i++)
    {
        scanf("%lf", &y[i]);
    }

    // array to store the successive interval widths
    double h[n];
    for (i = 0; i < n; i++)
    {
        h[i] = x[i + 1] - x[i];
    }

    // Matrix to store the tridiagonal system of equations that will solve for Si's
    double tri[n - 1][n];
    // to initialize tri[n-1][n]
    tridiagonalCubicSplineGen(n, h, tri, y);
    printf("The tridiagonal system for the Natural spline is:\n\n");
    printMatrix(n - 1, n, tri);

    // Perform Gauss Elimination
    double sig[n + 1]; //array to store Si's
    double sigTemp[n - 1]; //array to store the Si's except S0 and Sn
    sig[0] = 0;
    sig[n] = 0;

    gaussEliminationLS(n - 1, n, tri, sigTemp);
    for (i = 1; i < n ;i++)
    {
        sig[i] = sigTemp[i - 1];
    }

    //Print the values of Si's
    for (i = 0;i < n + 1; i++)
    {
        printf("\nSig[%d] = %lf\n", i, sig[i]);
    }

    // Calculate the values of ai's, bi's, ci's, and di's
    double a[n]; //array to store the ai's
    double b[n]; //array to store the bi's
    double c[n]; //array to store the ci's
    double d[n]; //array to store the di's
    cSCoeffCalc(n, h, sig, y, a, b, c, d);

    printf("The equations of cubic interpolation polynomials between the successive intervals are:\n\n");
    for (i = 0; i < n; i++)
    {
        printf("P%d(x) b/w [%lf,%lf] = %lf*(x-%lf)^3+%lf*(x-%lf)^2+%lf*(x-%lf)+%lf\n",
               i, x[i], x[i + 1], a[i], x[i], b[i], x[i], c[i], x[i], d[i]);
    }
}