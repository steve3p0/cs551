#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <complex.h>
#include "newton.h"
#include "newtonTests.h"

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

complex f(complex x, int deg, double coef[100])
{
    complex ans;
    int k;

    ans = 0;
    for (k = deg; k >= 0; k--)
    {
        ans = ans + coef[k] * my_pow(x, k);
    }

    return ans;
}

complex p(complex x, int pdeg, double pcoef[100])
{
    complex ans;
    int k;

    ans = 0;
    for (k = pdeg; k >= 0; k--)
    {
        ans = ans + pcoef[k] * my_pow(x, k);
    }

    return ans;
}

int do_newton()
{
    // This program finds the roots of a function using Newton's Method.
    // Define the function and its derivative.

    int k, deg, pdeg;
    double a,b,gr,gi, coef[100], pcoef[100], temp;
    complex x, y, m;

    printf("Input a complex number (in the form of a + bi) seed for Newton's Method:\n");
    printf("a = ");
    scanf("%lf", &gr);
    printf("\nb = ");
    scanf("%lf", &gi);

    // Allow user to define a polynomial
    printf("Defining polynomial f(x) in standard form:\n  What is the degree of f(x)?:  ");
    scanf("%d", &deg);

    for (k = deg; k >= 0; k--)
    {
        printf("coefficient of %d degree term: ", k);
        scanf("%lf", &temp);
        coef[k] = temp;
    }
    //printf("f(x) = %lfx^3 + %lfx^2 + %lfx + %lf\n", coef[3], coef[2], coef[1], coef[0]);

    // Create derivative polynomial p(x) based on f(x)
    pdeg = deg-1;
    for (k = pdeg; k >= 0; k--)
    {
        pcoef[k] = coef[k + 1] * (k + 1);
    }
    //printf("p(x) = %lfx^2 + %lfx + %lf\n", pcoef[2], pcoef[1], pcoef[0]);

    // Invoke Netwon's Method (gr, gi are components of guess x)
    x = gr + gi * I;

    for(k = 0; k < 20; k++)
    {
        y = f(x, deg, coef);
        m = p(x, pdeg, pcoef);
        x = (m * x-y) / m;
        a = creal(x);
        b = cimag(x);
        printf("root = %lf + %lfi\n", a, b);
    }
}


// Main Menu
// TODO: Figure out a way to make menus testable.
int main()
{
    while (1)
    {
        printf("\n\n");
        printf("\tNewton's Method: Find Roots\n");
        printf("\t----------------------------------------------------\n\n");
        printf("\tEnter 'G' to Run Graphics Test (FP Toolkit)\n");
        printf("\tEnter 'T' to Run Automated Tests\n");
        printf("\tEnter 'F' to Load Data Points from a File\n");
        printf("\tEnter 'Q' to Quit\n\n");
        printf("\tOr enter the number of points to create splines from: ");

        char menu[100];
        scanf("%s", menu);

        char *ptr;
        int n = strtol(menu, &ptr, 10);
        printf("\n");

        if (n > 0 && n < 101)
        {
            do_newton();
        }
        else if (strlen(menu) == 1)
        {
            char choice = toupper(menu[0]);
            int *n_ptr = malloc(sizeof(int));

            switch (choice)
            {
                //case 'g':
                case 'G':
                    // Environment Test
                    //test_fpitoolkit_graphics();
                    break;
                case 'T':
                    // Run tests

                    test_runner();

                    //test_splines();
                    //test_newton();
                    break;
//                case 'F':
//                    ; // <-- labels like case have to precede statements
//                    Spline *s = init();
//                    // wire up methods
//                    s->Load = read_file;
//                    s->Draw = plot;
//
//                    // Let's do it!
//                    s->Load(s);
//                    // Draw window AFTER loading from file
//                    draw_window();
//                    s->Solve(s);
//                    s->Draw(s);
//                    s->Destroy(s);
//
//                    G_wait_key();
//                    G_close();
//
//                    break;
                case 'Q':
                    printf("\n\n");
                    return 0;
                default:
                    printf("\n\n'%s' is not a valid menu selection.\n\n", menu);
            }
        }
        else
        {
            printf("\n\n'%s' is not a valid menu selection.\n\n", menu);
        }

    }
}