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

    p.x = a * pts[0].x +
          b * pts[1].x +
          c * pts[2].x +
          d * pts[3].x;

    p.y = a * pts[0].y +
          b * pts[1].y +
          c * pts[2].y +
          d * pts[3].y;

    return p;
}



#endif //FPTOOLKIT_LEASTSQUARES_H



