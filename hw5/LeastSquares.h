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

/* Using a data structure to hold each x, y
 * coordinate that the polynomial passes thru
 */
typedef struct point
{
    double x;
    double y;
} Point;

typedef void (*find_eq_linear)(int n, Point *data);
typedef void (*find_eq_quad)(int n, Point *data, int degree);

void  find_equation_linear(int n, Point *data);
double leastsquares(double x);

// Coefficients for y = ax + b
double A = 0;
double B = 0;

/* function: find_equation_linear
 * Finds the equation for a best fit using least squares
 * outputs:
 *    A    The 'a' part of y = ax + b
 *    B    The 'b' part of y = ax + b
 * inputs:
 *    n     number of points
 *    x     x represents 'x' in f(x) to evaluate
 *    data  the set of X, Y data points
 */
void find_equation_linear(int n, Point *data)
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

    // Partial Derivative of B2
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

    // Solve for B1 and B2

    // Solve B2 by substitution with B1
    double subB2_B2coef = partialB1_B1B2 / (-1 * partialB1_B1sq);
    double subB2_const  = partialB1_B1   / (-1 * partialB1_B1sq);

    double solveB2_B1coef = partialB2_B1B2 * subB2_B2coef;
    double solveB2_const  = partialB2_B1B2 * subB2_const;
    solveB2_B1coef += partialB2_B2sq;
    solveB2_const  += partialB2_B2;

    solveB2_const = (-1 * solveB2_const); // move to other side
    double B2 = solveB2_const / solveB2_B1coef;

    // Solve B1 now that you have B2
    double sub1_const = partialB1_B1B2 * B2 + partialB1_B1;
    sub1_const = (-1 * sub1_const); // move to other side
    double B1 = sub1_const / partialB1_B1sq;

    printf("B1: %f\n", B1);
    printf("B2: %f\n", B2);

    // So in the form of y =  ax + b
    //                   y = B2x + B1

    A = B2;
    B = B1;
}

void find_equation_quad(int n, Point *data, int degree)
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

    // Partial Derivative of B2
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

    // Solve for B1 and B2

    // Solve B2 by substitution with B1
    double subB2_B2coef = partialB1_B1B2 / (-1 * partialB1_B1sq);
    double subB2_const  = partialB1_B1   / (-1 * partialB1_B1sq);

    double solveB2_B1coef = partialB2_B1B2 * subB2_B2coef;
    double solveB2_const  = partialB2_B1B2 * subB2_const;
    solveB2_B1coef += partialB2_B2sq;
    solveB2_const  += partialB2_B2;

    solveB2_const = (-1 * solveB2_const); // move to other side
    double B2 = solveB2_const / solveB2_B1coef;

    // Solve B1 now that you have B2
    double sub1_const = partialB1_B1B2 * B2 + partialB1_B1;
    sub1_const = (-1 * sub1_const); // move to other side
    double B1 = sub1_const / partialB1_B1sq;

    printf("B1: %f\n", B1);
    printf("B2: %f\n", B2);

    // So in the form of y =  ax + b
    //                   y = B2x + B1

    A = B2;
    B = B1;
}

/* function: leastsquares
 * Just apply the y = ax + b
 * outputs:
 *    returns y
 * inputs:
 *    x
 */
double leastsquares(double x)
{
    return A * x + B;
}



#endif //FPTOOLKIT_LEASTSQUARES_H



