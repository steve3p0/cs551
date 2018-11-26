/* Least Sqauares Polynomial Regression Library
 * Steve Braich
 * CS 551
 *
 * References:
 *   - https://en.wikipedia.org/wiki/Least_squares
 *   - https://en.wikipedia.org/wiki/Polynomial_least_squares
 *   - https://stackoverflow.com/questions/5083465/fast-efficient-least-squares-fit-algorithm-in-c
 */

#ifndef FPTOOLKIT_LEASTSQUARES_H
#define FPTOOLKIT_LEASTSQUARES_H

/* Using a data structure to hold each x, y
 * coordinate that the polynomial passes thru
 */
typedef struct point
{
    double x;
    double y;
} Point;

typedef double (*interpolate)(int n, double x, Point *data);

double leastsquares(int n, double x, Point *data);
double leastsquares_estimate(int i, int n, double x, Point *data);


/* function: leastsquares
 * Evaluates a Least Squares polynomial of degree < n that passes thru
 * the set of data points represented by x, y.
 * Returns a summation of estimated Y coordinates
 * outputs:
 *    y  Estimated y - the result of f(x)
 * inputs:
 *    n     number of points (degree)
 *    x     x represents 'x' in f(x) to evaluate
 *    data  the set of X, Y data points
 */
double leastsquares(int n, double x, Point *data)
{

    // Data set:

    double coef_0deg = 0;
    double coef_B1 = 0;
    double coef_B2 = 0;
    double coef_B1sq = 0;
    double coef_B2sq = 0;
    double coef_B1B2 = 0;


    double y = 0;

    int i;
    for (i = 0; i < n; i++)
    {
        printf("[%f - (B1 + %f*B2)]^2 + \n", data[i].y, data[i].x);

        // Square: [y - (B1 + xB2)]^2

        // y part
        coef_0deg += data[i].y * data[i].y;
        coef_B1   += data[i].y * (-1);
        coef_B2   += data[i].y * (-1 * data[i].x);

        // B1 part: -1 is coeffecient of B1
        coef_B1   += (-1) * data[i].y;
        coef_B1sq += (-1) * (-1);
        coef_B1B2 += (-1) * (-1 * data[i].x);

        // xB2 part
        coef_B2   +=  (-1 * data[i].x) * data[i].y;
        coef_B1B2 +=  (-1 * data[i].x) * (-1);
        coef_B2sq +=  (-1 * data[i].x) * (-1 * data[i].x);

        //y += leastsquares_estimate(i, n, x, data) * data[i].y;

        //printf("{%f, %f}, ", data[i].x, data[i].y);
    }

    printf("coef_0deg: %f\n", coef_0deg);
    printf("coef_B1: %f\n", coef_B1);
    printf("coef_B2: %f\n", coef_B2);
    printf("coef_B1sq: %f\n", coef_B1sq);
    printf("coef_B2sq: %f\n", coef_B2sq);
    printf("coef_B1B2: %f\n", coef_B1B2);

    printf("\n");

    // Partial Derivative of B1
    double partialB1_0deg = 0 * coef_0deg;
    double partialB1_B1   = 1 * coef_B1;
    double partialB1_B2   = 0 * coef_B2;
    double partialB1_B1sq = 2 * coef_B1sq;
    double partialB1_B2sq = 0 * coef_B2sq;
    double partialB1_B1B2 = 1 * coef_B1B2; // left with B2

    printf("partialB1_0deg: %f\n", partialB1_0deg);
    printf("partialB1_B1: %f\n", partialB1_B1);
    printf("partialB1_B2: %f\n", partialB1_B2);
    printf("partialB1_B1sq: %f\n", partialB1_B1sq);
    printf("partialB1_B2sq: %f\n", partialB1_B2sq);
    printf("partialB1_B1B2: %f\n", partialB1_B1B2);

    printf("\n");

    // Partial Derivative of B1
    double partialB2_0deg = 0 * coef_0deg;
    double partialB2_B1   = 0 * coef_B1;
    double partialB2_B2   = 1 * coef_B2;
    double partialB2_B1sq = 0 * coef_B1sq;
    double partialB2_B2sq = 2 * coef_B2sq;
    double partialB2_B1B2 = 1 * coef_B1B2; // left with B2

    printf("partialB2_0deg: %f\n", partialB2_0deg);
    printf("partialB2_B1: %f\n", partialB2_B1);
    printf("partialB2_B2: %f\n", partialB2_B2);
    printf("partialB2_B1sq: %f\n", partialB2_B1sq);
    printf("partialB2_B2sq: %f\n", partialB2_B2sq);
    printf("partialB2_B1B2: %f\n", partialB2_B1B2);

    printf("\n");

    //return y;
    return 3.5 + 1.4 * x;

}

/* function: leastsquares_estimate
 * Estimate Y (pixelY) for a Given X (x) using Least Squares Regression
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
double leastsquares_estimate(int i, int n, double x, Point *data)
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

#endif //FPTOOLKIT_LEASTSQUARES_H



