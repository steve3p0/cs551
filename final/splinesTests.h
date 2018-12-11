/* Least Sqauares Polynomial Regression Library - Testing
 * Steve Braich
 * CS 551
 *
 * References:
 *   - https://en.wikipedia.org/wiki/Least_squares
 *   - https://en.wikipedia.org/wiki/Polynomial_least_squares
 *   - https://www.wikiwand.com/en/Linear_least_squares#/Example
 */


#ifndef FPTOOLKIT_LEASTSQUARES_TESTS_H
#define FPTOOLKIT_LEASTSQUARES_TESTS_H

#include <stdbool.h>
#include "splines.h"

/* Using a data structure to hold each x, y
 * coordinate that the polynomial passes thru
 */
typedef struct point
{
    double x;
    double y;
} Point;

/* TestInput: Created this typedef to make it to create tests
 * You can create the input statically pretty easy
 */
typedef struct test_input
{
    double expectedArray[100];
    int index;
    double initial;
    double *diagona;
} TestInput;

/* Used to evaluate eequality of double (floating point numbers)
 * https://stackoverflow.com/questions/17333/what-is-the-most-effective-way-for-float-and-double-comparison
 */
bool Equality(double a, double b, double epsilon)
{
    if (fabs(a-b) < epsilon) return true;
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
}

/* This function will run whatever function passed into it
 * Also, the input and expected values are passed in as well.
 */
int run_test(char *test_name, Spline *s, double *expect)
{


    double array[100];
    array = fill_diagonals(s, 1, 1, array);

    bool expectA_pass = Equality(A, expectA, 0.01);
    bool expectB_pass = Equality(B, expectB, 0.01);

    if (expectA_pass && expectB_pass)
    {
        printf("PASS - %s\n\n", test_name);

        return 1;
    }
    else
    {
        printf("FAIL - %s\n", test_name);
        printf("\tExpected A Value: %f\n", expectA);
        printf("\t  Actual A Value: %f\n", A);
        printf("\tExpected B Value: %f\n", expectB);
        printf("\t  Actual B Value: %f\n", B);
        printf("\t  Input Values:\n");
        printf("\t\t   n (degree): %d\n", input->n);
        printf("\t\t points(x, y): ");

        int i;
        for (i = 0; i < input->n; i++)
        {
            printf("(%f, %f)", input->data[i].x, input->data[i].y);
            if (i < input->n - 1)
            {
                printf(", ");
            }
        }
        printf("\n");

        return 0;
    }

    free(input);
}

/* Least Squares Tests
 * TODO: Add more edge casees
 */
int test_splines()
{
    printf("\nRunning Splines Tests...\n\n");

    // Integration Tests
    int count = 0;
    int pass = 0;
    TestInput *input_ptr;
    printf("Integration Tests...\n\n");

    // NOTE: It is very easy to statically initialize these input structs.
    // I have to create multiple instances of them.  I free up the memory
    // for each one in function 'run_test'
    count++;
    Spline *s = init();
    s->n = 6;
    s->d = 10;
    double x[s->n] = { 177.00, 249.00, 311.00, 381.00, 416.00, 455.00 };
    double y[s->n] = { 211.00, 315.00, 460, 469, 311, 195};
    double d[s->d] = { 1.0, 5184.0, -134, 3844, -132, 4900, -105, 1225, -74, 89 };
    s->x = x;
    s->y = y;
    s->D = d;
    pass += run_test("test_least_squares_wikipedia_example", s);

//    count++;
//    TestInput input_wiki_ex2 = { 4, {{1, 6}, {2, 5}, {3, 7}, {4, 10}}, 1};
//    input_ptr = &input_wiki_ex2;
//    pass += run_test("test_least_squares_wikipedia_example", &find_equation_quad, input_ptr, 1.4, 3.5);
//

//    count++;
//    TestInput input_ones = { 1, {{1, 1}}, 1};
//    input_ptr = &input_ones;
//    pass += run_test("test_least_squares_n1_{{1, 1}}", &leastsquares, input_ptr, 1);
//
//    count++;
//    TestInput input3 = { 2, {{0, 1}, {0, 2}}, 1};
//    input_ptr = &input3;
//    pass += run_test("test_least_squares_n2_DIV0{{0, 1}, {0, 2}}", &leastsquares, input_ptr, 3);
//
//    count++;
//    TestInput input4 = { 3, {{1, 1}, {2, 4}, {3, 9}}, 2.5};
//    input_ptr = &input4;
//    pass += run_test("test_least_squares_n3_{1, 2, 3}, {1, 4, 9}", &leastsquares, input_ptr, 6.25);
//
//    count++;
//    TestInput input5 = { 3, {{2, .5}, {2.75, .363636}, {4, .25}}, 3};
//    input_ptr = &input5;
//    pass += run_test("test_least_squares_n3_{{2, .5}, {2.75, .363636}, {4, .25}}", &leastsquares, input_ptr, .329545);
//
//    count++;
//    TestInput input_neg = { 2, {{-1, -20}, {-5, -2}}, 1};
//    input_ptr = &input_neg;
//    pass += run_test("test_least_squares_n2_neg", &leastsquares, input_ptr, -29);

    // TODO: What are some other good edge cases?

    printf("\nCompleted Least Squares Tests: %d out of %d tests PASSED\n", pass, count);
}

#endif //FPTOOLKIT_LEASTSQUARES_TESTS_H
