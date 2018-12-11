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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <complex.h>

#define M 100
#define MAX_ITERATIONS 20

typedef struct newton
{
    // need epsilon
    // need tolerance
    // need MAX iterations

    // Complex Number (in the form of a + bi)
    // See for Newton's Method
    // This contains the guess
    double a[MAX_ITERATIONS];
    double b[MAX_ITERATIONS];
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
    //int k;

    // Public Functions
    void (*Load)    ();
    void (*Solve)   ();
    void (*Print)   ();
    void (*Destroy) ();

    // Private Functions
    complex (*Power)();
    complex (*F)    ();
    complex (*P)    ();

//    complex (*Power)(complex x, int k);
//    complex (*F)    (complex x, int deg, double coef[100]);
//    complex (*P)    (complex x, int pdeg, double pcoef[100]);

} Newton;

complex my_pow(complex x, int k)
{
    int c;
    complex ans;

    ans = 1;
    for (c = 0; c < k; c++)
    {
        ans = ans * x;
    }

    return ans;
}

complex f(Newton *n)
{
    complex ans;

    ans = 0;
    for (int k = n->deg; k >= 0; k--)
    {
        ans = ans + n->coef[k] * my_pow(n->x, k);
    }

    return ans;
}

complex p(Newton *n)
{
    complex ans;

    ans = 0;
    for (int k = n->pdeg; k >= 0; k--)
    {
        ans = ans + n->pcoef[k] * my_pow(n->x, k);
    }

    return ans;
}

void *load(Newton *n)
{
    printf("Input a complex number (in the form of a + bi) seed for Newton's Method:\n");
    printf("a = ");
    scanf("%lf", &n->gr);
    printf("\nb = ");
    scanf("%lf", &n->gi);

    // Allow user to define a polynomial
    printf("Defining polynomial f(x) in standard form:\n  What is the degree of f(x)?:  ");
    scanf("%d", &n->deg);

    double temp;

    for (int k = n->deg; k >= 0; k--)
    {
        printf("coefficient of %d degree term: ", k);
        scanf("%lf", &temp);
        n->coef[k] = temp;
    }
}

void *find_roots(Newton *n)
{
    // Create derivative polynomial p(x) based on f(x)
    n->pdeg = n->deg - 1;
    for (int k = n->pdeg; k >= 0; k--)
    {
        n->pcoef[k] = n->coef[k + 1] * (k + 1);
    }
    //printf("p(x) = %lfx^2 + %lfx + %lf\n", pcoef[2], pcoef[1], pcoef[0]);

    // Invoke Netwon's Method (gr, gi are components of guess x)
    n->x = n->gr + n->gi * I;

    for(int k = 0; k < MAX_ITERATIONS; k++)
    {
        n->y = f(n);
        n->m = p(n);
        n->x = (n->m * n->x - n->y) / n->m;

        n->a[k] = creal(n->x);
        n->b[k] = cimag(n->x);

        //printf("root = %lf + %lfi\n", n->a[k], n->b[k]);
    }
}

void *print_roots(Newton *n)
{
    for(int k = 0; k < MAX_ITERATIONS; k++)
    {
        printf("root = %lf + %lfi\n", n->a[k], n->b[k]);
    }

}

void *destroy(Newton *n)
{
    //free(n->coef);
    //free(n->pcoef);

    free(n);

    //printf("\tLog - destroy: memory successfully deallocated...\n");
}

Newton *init()
{
    Newton *n = malloc(sizeof(Newton));

    n->gr = 0;
    n->gi = 0;

    n->deg  = 0;
    n->pdeg = 0;

    for (int i = 0; i < M; i++)
    {
        n->a[i] = 0;
        n->b[i] = 0;

        n->coef[i]  = 0;
        n->pcoef[i] = 0;
    }

    n->x = 0 * I;
    n->y = 0 * I;
    n->m = 0 * I;

    n->Load  = load;
    n->Solve = find_roots;
    n->Print = print_roots;
    n->Destroy = destroy;
}



#endif //HW2_NEWTON_H
