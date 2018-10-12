#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <complex.h>

complex my_pow(complex x, int k)
{
    int c ;
    complex ans ;

    ans = 1 ;
    for(c=0;c<k;c++) {
        ans = ans*x ;
    }
    return ans ;
}

complex f(complex x, int deg, double coef[100])
{
    complex ans;
    int k ;

    ans = 0 ;
    for(k=deg;k>=0;k--)
    {
        ans = ans + coef[k]*my_pow(x,k) ;
    }

    return ans ;
}

complex p(complex x, int pdeg, double pcoef[100])
{
    complex ans ;
    int k ;

    ans = 0 ;
    for(k=pdeg;k>=0;k--) {
        ans = ans + pcoef[k]*my_pow(x,k) ;
    }

    return ans ;
}

int main()
{

    // This program finds the roots of a function using Newton's Method.
    // Define the function and its derivative.

    int k, deg, pdeg ;
    double a,b,gr,gi, coef[100], pcoef[100], temp ;
    complex x, y, m ;

    printf("Input a complex number (in the form of a + bi) seed for Newton's Method:\n") ;
    printf("a = ") ;
    scanf("%lf", &gr) ;
    printf("\nb = ") ;
    scanf("%lf", &gi) ;

    // Allow user to define a polynomial
    printf("Defining polynomial f(x) in standard form:\n  What is the degree of f(x)?:  ") ;
    scanf("%d", &deg) ;
    for(k=deg;k>=0;k--) {
        printf("coefficient of %d degree term: ", k) ;
        scanf("%lf", &temp) ;
        coef[k] = temp ;
    }
    //printf("f(x) = %lfx^3 + %lfx^2 + %lfx + %lf\n", coef[3], coef[2], coef[1], coef[0]) ;

    // Create derivative polynomial p(x) based on f(x)
    pdeg = deg-1 ;
    for(k=pdeg;k>=0;k--) {
        pcoef[k] = coef[k+1]*(k+1) ;
    }
    //printf("p(x) = %lfx^2 + %lfx + %lf\n", pcoef[2], pcoef[1], pcoef[0]) ;

    // Invoke Netwon's Method (gr, gi are components of guess x)
    x = gr + gi*I ;
    for(k=0;k<20;k++) {
        y = f(x,deg,coef);
        m = p(x,pdeg,pcoef) ;
        x = (m*x-y)/m ;
        a = creal(x) ;
        b = cimag(x) ;
        printf("root = %lf + %lfi\n", a, b) ;
    }
}