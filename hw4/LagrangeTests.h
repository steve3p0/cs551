/* Lagrange Polynomial Interpolation Library - Testing
 * Steve Braich
 * CS 551
 *
 * References:
 *     https://en.wikipedia.org/wiki/Lagrange_polynomial
 *     https://math.stackexchange.com/questions/523907/explanation-of-lagrange-interpolating-polynomial
 *     https://stackoverflow.com/questions/17333/what-is-the-most-effective-way-for-float-and-double-comparison
 */


#ifndef FPTOOLKIT_LAGRANGE_TESTS_H
#define FPTOOLKIT_LAGRANGE_TESTS_H

#include <stdbool.h>
#include "Lagrange.h"

/* TestInput: Created this typedef to make it to create tests
 * You can create the input statically pretty easy
 */
typedef struct test_input
{
    int n;
//    double x[100];
//    double y[100];
    Point data[100];
    double k;
} TestInput;

/* Used to evaluate eequality of double (floating point numbers)
 * https://stackoverflow.com/questions/17333/what-is-the-most-effective-way-for-float-and-double-comparison
 */
bool Equality(double a, double b, double epsilon)
{
    if (fabs(a-b) < epsilon) return true;
    return false;
}

/* This function will run whatever function passed into it
 * Also, the input and expected values are passed in as well.
 */
int run_test(char *test_name, interpolate f, TestInput *input, double expect)
{
    double actual = f(input->n, input->k, input->data);

    if (Equality(actual, expect, 0.01))
    {
        printf("PASS - %s\n", test_name);

        return 1;
    }
    else
    {
        printf("FAIL - %s\n", test_name);
        printf("\tExpected Value: %f\n", expect);
        printf("\t  Actual Value: %f\n", actual);
        printf("\t  Input Values:\n");
        printf("\t\t   n (degree): %d\n", input->n);
        printf("\t\t k in f(x): %f\n", input->k);
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

/* Lagrange Tests
 * TODO: Add more edge casees
 */
int test_lagrange()
{
    printf("\nRunning Lagrange Tests...\n\n");

    // Integration Tests
    int count = 0;
    int pass = 0;
    TestInput *input_ptr;
    printf("Integration Tests...\n\n");

    // NOTE: It is very easy to statically initialize these input structs.
    // I have to create multiple instances of them.  I free up the memory
    // for each one in function 'run_lagrange_test'
    count++;
    TestInput input_zero = { 1, {{0, 0}}, 0};
    input_ptr = &input_zero;
    pass += run_test("test_lagrange_n1_{{0, 0}}", &lagrange, input_ptr, 0);

    count++;
    TestInput input_ones = { 1, {{1, 1}}, 1};
    input_ptr = &input_ones;
    pass += run_test("test_lagrange_n1_{{1, 1}}", &lagrange, input_ptr, 1);

    count++;
    TestInput input3 = { 2, {{0, 1}, {0, 2}}, 1};
    input_ptr = &input3;
    pass += run_test("test_lagrange_n2_DIV0{{0, 1}, {0, 2}}", &lagrange, input_ptr, 3);

    count++;
    TestInput input4 = { 3, {{1, 1}, {2, 4}, {3, 9}}, 2.5};
    input_ptr = &input4;
    pass += run_test("test_lagrange_n3_{1, 2, 3}, {1, 4, 9}", &lagrange, input_ptr, 6.25);

    count++;
    TestInput input5 = { 3, {{2, .5}, {2.75, .363636}, {4, .25}}, 3};
    input_ptr = &input5;
    pass += run_test("test_lagrange_n3_{{2, .5}, {2.75, .363636}, {4, .25}}", &lagrange, input_ptr, .329545);

    count++;
    TestInput input_neg = { 2, {{-1, -20}, {-5, -2}}, 1};
    input_ptr = &input_neg;
    pass += run_test("test_lagrange_n2_neg", &lagrange, input_ptr, -29);

    // TODO: What are some other good edge cases?

    printf("\nCompleted Lagrange Tests: %d out of %d tests PASSED\n", pass, count);
}

#endif //FPTOOLKIT_LAGRANGE_TESTS_H
