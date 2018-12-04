/* Least Sqauares Polynomial Regression Library
 * Steve Braich
 * CS 551
 *
 * References:
 *   - https://en.wikipedia.org/wiki/Least_squares
 *   - https://en.wikipedia.org/wiki/Polynomial_least_squares
 *   - https://www.wikiwand.com/en/Linear_least_squares#/Example
 */

#ifndef FPTOOLKIT_LEASTSQUARES_H
#define FPTOOLKIT_LEASTSQUARES_H

typedef struct point
{
    int x;
    int y;
} Point;

Point Q01234(Point *pts, double t)
{
    Point p = { 0, 0};

    double a = (1 - 3*t + 3*pow(t, 2) -   pow(t, 3)) / 6;
    double b = (4 -       6*pow(t, 2) + 3*pow(t, 3)) / 6;
    double c = (1 + 3*t + 3*pow(t, 2) - 3*pow(t, 3)) / 6;
    double d = (                          pow(t, 3)) / 6;

    // From b_splines.txt from Professory Ely
    // x(t) = a(t)*x0 + b(t)*x1 + c(t)*x2 + d(t)*x3
    // y(t) = a(t)*y0 + b(t)*y1 + c(t)*y2 + d(t)*y3

    p.x = a*pts[0].x + b*pts[1].x + c*pts[2].x + d*pts[3].x;
    p.y = a*pts[0].y + b*pts[1].y + c*pts[2].y + d*pts[3].y;

    return p;
}

/********************
Cubic Spline coefficients calculator
Function that calculates the values of ai, bi, ci, and di's for the cubic splines:
ai(x-xi)^3+bi(x-xi)^2+ci(x-xi)+di
********************/
void cSCoeffCalc(int n, double h[n], double sig[n+1], double y[n+1], double a[n], double b[n], double c[n], double d[n])
{
    int i;
    for (i = 0; i < n; i++)
    {
        a[i] = (sig[i + 1] - sig[i]) / (h[i] * 6.0);
        b[i] = sig[i] / 2.0;
        c[i] = (y[i + 1] - y[i]) / h[i] - h[i] * (2 * sig[i] + sig[i + 1]) / 6.0;
        d[i] = y[i];
    }
}

/********************
Function to generate the tridiagonal augmented matrix
for cubic spline for equidistant data-points
Parameters:
n: no. of data-points
h: array storing the succesive interval widths
a: matrix that will hold the generated augmented matrix
y: array containing the y-axis data-points
********************/
void tridiagonalCubicSplineGen(int n, double h[n], double a[n-1][n], double y[n+1]){
    int i;
    for(i=0;i<n-1;i++){
        a[i][i]=2*(h[i]+h[i+1]);
    }
    for(i=0;i<n-2;i++){
        a[i][i+1]=h[i+1];
        a[i+1][i]=h[i+1];
    }
    for(i=1;i<n;i++){
        a[i-1][n-1]=(y[i+1]-y[i])*6/(double)h[i]-(y[i]-y[i-1])*6/(double)h[i-1];
    }
}




#endif //FPTOOLKIT_LEASTSQUARES_H



