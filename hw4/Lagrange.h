/* Lagrange Polynomial Interpolation Library
 * Steve Braich
 * CS 551
 *
 * References:
 *     https://en.wikipedia.org/wiki/Lagrange_polynomial
 *     https://math.stackexchange.com/questions/523907/explanation-of-lagrange-interpolating-polynomial
 */

#ifndef FPTOOLKIT_LAGRANGE_H
#define FPTOOLKIT_LAGRANGE_H

typedef struct point
{
    double x;
    double y;
} Point;

//typedef double (*interpolate)(int n, double k, double *x, double *y);
typedef double (*interpolate)(int n, double k, Point *data);

//double lagrange(int n, double k, double *x, double *y);
double lagrange(int n, double k, Point *data);
//double lagrange_estimate(int i, int n, double k, double *x);
double lagrange_estimate(int i, int n, double k, Point *data);


/* function: lagrange
 * Evaluates a Lagrange polynomial of degree < n that passes thru
 * the set of data points represented by x, y.
 * Returns a summation of estimated Y coordinates
 * outputs:
 *  pixelY  Estimated Y Coordinate pixel on the window screen
 * inputs:
 *    n     number of points (degree)
 *    k     k represents 'k' in f(k) to evaluate
 *    *x    pointer to array of n number of x coordinates
 *    *y    pointer to array of n number of y coordinates
 */
//double lagrange(int n, double k, double *x, double *y)
double lagrange(int n, double k, Point *data)
{
    double pixelY = 0;

    int i;
    for (i = 0; i < n; i++)
    {
        pixelY += lagrange_estimate(i, n, k, data) * data[i].y;
    }

    return pixelY;
}

/* function: lagrange_estimate
 * Estimate Y (pixelY) for a Given X (k) using Lagrange Interpolation
 * Note: This function is f(x) that returns y
 * Returns a product of estimated Y coordinates
 * outputs:
 *  pixelY  Estimated Y Coordinate pixel on the window screen
 * inputs:
 *    i     indexer (x sub i)
 *    n     number of points (degree)
 *    k     k represents 'k' in f(k) to evaluate
 *    *x    pointer to array of n number of x coordinates
 */
double lagrange_estimate(int i, int n, double k, Point *data)
{
    double pixelY = 1;

    int j;
    for (j = 0; j < n; j++)
    {
        if (j != i)
        {
            double denominator = data[i].x - data[j].x;
            if (denominator != 0)
            {
                pixelY *= (k - data[j].x) / denominator;
            }
        }
    }

    return pixelY;
}

#endif //FPTOOLKIT_LAGRANGE_H



