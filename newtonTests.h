/* HW #2: Newton's Method Test Library
 * Steve Braich
 * CS 551
 *
 * References:
 *   - https://en.wikipedia.org/wiki/Spline_interpolation
 *   - https://en.wikipedia.org/wiki/Spline_(mathematics)
 *   - Dr. Ely's Naive Newton's Method Code
 *   - https://stackoverflow.com/questions/17333/what-is-the-most-effective-way-for-float-and-double-comparison
 */

#ifndef NEWTON_NEWTONTESTS_H
#define NEWTON_NEWTONTESTS_H

#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "newton.h"

typedef struct test
{
    int index;
    int count;
    int pass;

    //char **testname;
    char testname [10][100];
    char results  [10][100];
    char messages [10][10];
    char failed   [10][10];

    char stdinout[1000];
    int passfail[100];

} Test;

// Used to evaluate equality of double (floating point numbers)
// https://stackoverflow.com/questions/17333/what-is-the-most-effective-way-for-float-and-double-comparison
bool Equality(double a, double b, double epsilon)
{
    if (fabs(a-b) < epsilon)
    {
        return true;
    }
    return false;
}

bool CompareArrays(int n, double *a, double *b)
{
    for (int i = 0; i < n; i++)
    {
        if (!Equality(a[i], b[i], 0.01))
        {
            return false;
        }
    }

    return true;
}

void print_array(int n, double *array, char *name)
{
    printf("\n");
    for (int i = 0; i < n; i++)
    {
        printf("%s[%d] = %10.10lf\n", name, i, array[i]);
    }

    printf("\n");
}

//char *concat(const char *s1, const char *s2)
char *concat(char *s1, char *s2)
{
    if (s1 == NULL)
        return s2;
    else if (s2 == NULL)
        return s1;

    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);

    return result;
}

char *concat1(char *s1, char *s2)
{

    int strlen_s1 = 0;
    int strlen_s2 = 0;

    if (s1 != NULL)
        strlen_s1 = strlen(s1);

    if (s2 != NULL)
        strlen_s2 = strlen(s2);

    char *result = malloc(strlen_s1 + strlen_s2 + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);

    return result;
}

//////////////////////////////////////////////////////

Test *init_test()
{
    Test *t = malloc(sizeof(Test));
    t->index = 0;
    t->count = 0;
    t->pass = 0;
}

void pass(char *testname, Test *t)
{
    strcpy(t->testname[t->index], testname);
    strcpy(t->results[t->index], "FAIL");

    t->pass++;
    t->index++;
    t->count++;
}

void fail(char *testname, Test *t)
{
    strcpy(t->testname[t->index], testname);
    strcpy(t->results[t->index], "FAIL");

    t->index++;
    t->count++;
}

void print(Test *t)
{
    for (int i = 0; i < t->count; i++)
    {
        //printf("%d: (%s) - (%s)\n", i, t->testname[i], t->results[i]);
        printf("\t%s - %s\n", t->results[i], t->testname[i]);
    }

    printf("\nTest Runner: %d out of %d tests PASSED\n", t->pass, t->count);
}

//////////////////////////////////////////////////////

void test_dummy(char *testname, Test *t)
{
    //pass(testname, t);
    fail(testname, t);
}


////// Integration TESTS ////////////////////////////////////

void test_solve_wiki(char *testname, Test *t)
{
    Newton *n = init();

    // Guess real
    n->gr =  30;
    // Guess Imaginary
    n->gi = -30;

    // Degree of Polynomial
    n->deg  = 2;

    // Enter Coefficients
    n->coef[0] = 612;
    n->coef[1] = 0;
    n->coef[2] = 1;

    // Now Solve it!
    n->Solve(n);
    n->Print(n);
    n->Destroy(n);

    //pass(testname, t);
    fail(testname, t);
}

void test_solve_graded_input1(char *testname, Test *t)
{
    Newton *n = init();

    // Guess real
    n->gr =  -5;
    // Guess Imaginary
    n->gi = -5;

    // Degree of Polynomial
    n->deg  = 1;

    // Enter Coefficients
    n->coef[0] = 12;
    n->coef[1] =  3;

    // Now Solve it!
    n->Solve(n);
    n->Print(n);
    n->Destroy(n);

    //pass(testname, t);
    fail(testname, t);
}

void test_solve_graded_input2(char *testname, Test *t)
{
    Newton *n = init();

    // Guess real
    n->gr =  -2;
    // Guess Imaginary
    n->gi = -2;

    // Degree of Polynomial
    n->deg  = 3;

    // Enter Coefficients
    n->coef[0] = 1;
    n->coef[1] = 1;
    n->coef[2] = 1;
    n->coef[3] = 1;

    // Now Solve it!
    n->Solve(n);
    n->Print(n);
    n->Destroy(n);

    //pass(testname, t);
    fail(testname, t);
}

void test_solve_graded_input3(char *testname, Test *t)
{
    Newton *n = init();

    // Guess real
    n->gr =  3;
    // Guess Imaginary
    n->gi = -3;

    // Degree of Polynomial
    n->deg  = 4;

    // Enter Coefficients
    n->coef[0] = -16;
    n->coef[1] = 0;
    n->coef[2] = 0;
    n->coef[3] = 0;
    n->coef[4] = 1;

    // Now Solve it!
    n->Solve(n);
    n->Print(n);
    n->Destroy(n);

    //pass(testname, t);
    fail(testname, t);
}

void test_solve_graded_input4(char *testname, Test *t)
{
    Newton *n = init();

    // Guess real
    n->gr =  3;
    // Guess Imaginary
    n->gi = -3;

    // Degree of Polynomial
    n->deg  = 4;

    // Enter Coefficients
    n->coef[0] = -63;
    n->coef[1] = -6;
    n->coef[2] = 1640;
    n->coef[3] = 3716;
    n->coef[4] = 1587;
    n->coef[5] = 126;

    // Now Solve it!
    n->Solve(n);
    n->Print(n);
    n->Destroy(n);

    //pass(testname, t);
    fail(testname, t);
}

void test_solve_graded_input5(char *testname, Test *t)
{
    Newton *n = init();

    // Guess real
    n->gr =  0;
    // Guess Imaginary
    n->gi = 2;

    // Degree of Polynomial
    n->deg  = 4;

    // Enter Coefficients
    n->coef[0] = -1;
    n->coef[1] = 0;
    n->coef[2] = 0;
    n->coef[3] = 0;
    n->coef[4] = 0;
    n->coef[5] = 0;
    n->coef[6] = 0;
    n->coef[7] = 1;

    // Now Solve it!
    n->Solve(n);
    n->Print(n);
    n->Destroy(n);

    //pass(testname, t);
    fail(testname, t);
}

// TODO: Finish rest of unit tests
int test_runner()
{
    printf("\nRunning Tests...\n\n");

    Test *t = init_test();

    test_solve_wiki("test_solve: Wikipedia Example: f(x) = x^2 - 612", t);
    test_solve_graded_input1("test_solve: graded input 1: f(x) = 3x + 12", t);
    test_solve_graded_input2("test_solve: graded input 2: f(x) = x^3 + x^2 + x + 1", t);

    // These one is fucked up
    test_solve_graded_input3("test_solve: graded input 3: f(x) = x^4 - 16", t);

    // This has multiple roots
    test_solve_graded_input4("test_solve: graded input 4: f(x) = 126x^5 + 1587x^4 + 3716x^3 + 1640x^2 - 6x - 63", t);

    // fucked up: root (k = 00) = +inf + -nani
    test_solve_graded_input5("test_solve: graded input 5: f(x) = x^7 - 1", t);

    print(t);
    free(t);
}

#endif //NEWTON_NEWTONTESTS_H
