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

/* Using a data structure to hold each x, y
 * coordinate that the polynomial passes thru
 */
typedef struct point
{
    double x;
    double y;
} Point;

typedef double (*interpolate)(int n, double x, Point *data);

double lagrange(int n, double x, Point *data);
double lagrange_estimate(int i, int n, double x, Point *data);


/* function: lagrange
 * Evaluates a Lagrange polynomial of degree < n that passes thru
 * the set of data points represented by x, y.
 * Returns a summation of estimated Y coordinates
 * outputs:
 *    y  Estimated y - the result of f(x)
 * inputs:
 *    n     number of points (degree)
 *    x     x represents 'x' in f(x) to evaluate
 *    data  the set of X, Y data points
 */
double lagrange(int n, double x, Point *data)
{
    double y = 0;

    int i;
    for (i = 0; i < n; i++)
    {
        y += lagrange_estimate(i, n, x, data) * data[i].y;
    }

    return y;
}

/* function: lagrange_estimate
 * Estimate Y (pixelY) for a Given X (x) using Lagrange Interpolation
 * Note: This function is f(x) that returns y
 * Returns a product of estimated Y coordinates
 * outputs:
 *  pixelY  Estimated Y Coordinate pixel on the window screen
 * inputs:
 *    i     indexer (x sub i)
 *    n     number of points (degree)
 *    x     x represents 'x' in f(x) to evaluate
 *    data  the set of X, Y data points
 */
double lagrange_estimate(int i, int n, double x, Point *data)
{
    double y = 1;

    int j;
    for (j = 0; j < n; j++)
    {
        if (j != i)
        {
            // Don't DIVIDE by ZERO!
            double denominator = data[i].x - data[j].x;
            if (denominator != 0)
            {
                y *= (x - data[j].x) / denominator;
            }
        }
    }

    return y;
}

#endif //FPTOOLKIT_LAGRANGE_H



