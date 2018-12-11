/* HW #2: Newton's Method
 * Steve Braich
 * CS 551
 *
 * References:
 *   - https://en.wikipedia.org/wiki/Spline_interpolation
 *   - https://en.wikipedia.org/wiki/Spline_(mathematics)
 *   - Dr. Ely's Naive Newton's Method Code
 */

#ifndef HW2_NEWTON_H
#define HW2_NEWTON_H

#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <complex.h>

#define M 100

typedef struct newton
{
    // need epsilon
    // need tolerance
    // need MAX iterations

    // Complex Number (in the form of a + bi)
    // See for Newton's Method
    // This contains the guess
    double a;
    double b;
    double gr;
    double gi;

    // f(x): User defined Polynomial
    // We find the roots for this
    int deg;         // Degree of f(x)
    double coef[M];  // Coefficients of f(x)

    // p(x): Derivative of f(x) Polynomial
    // Also known as f'(x) or f prime
    int pdeg;        // Degree of p(x)
    double pcoef[M]; // Coefficients of p(x) - f'(x)

    // Complex Numbers
    complex x;
    complex y;
    complex m;

    // do we need this here?
    int k;

    // Public Functions
    complex (*Power)();
    complex (*F)    ();
    complex (*P)    ();
//    complex (*Power)(complex x, int k);
//    complex (*F)    (complex x, int deg, double coef[100]);
//    complex (*P)    (complex x, int pdeg, double pcoef[100]);

//    void (*Load) ();     // Wired up in main
//    void (*New) ();
//    void (*Solve) ();
//    void (*Print)(const struct spline*);
//    void (*Draw) ();    //  Virtual
//    void (*Destroy)();  // Deconstructor


} Newton;




#endif //HW2_NEWTON_H
