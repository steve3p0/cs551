/* Least Sqauares Polynomial Regression Library - Testing
 * Steve Braich
 * CS 551
 *
 * References:
 *   - https://en.wikipedia.org/wiki/Least_squares
 *   - https://en.wikipedia.org/wiki/Polynomial_least_squares
 *   - https://stackoverflow.com/questions/5083465/fast-efficient-least-squares-fit-algorithm-in-c
 */


#ifndef FPTOOLKIT_LEASTSQUARES_TESTS_H
#define FPTOOLKIT_LEASTSQUARES_TESTS_H

#include <stdbool.h>
#include "LeastSquares.h"

/* TestInput: Created this typedef to make it to create tests
 * You can create the input statically pretty easy
 */
typedef struct test_input
{
    int n;
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
        printf("\t\t x in f(x): %f\n", input->k);
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
int test_least_squares()
{
    printf("\nRunning Least Squares Tests...\n\n");

    // Integration Tests
    int count = 0;
    int pass = 0;
    TestInput *input_ptr;
    printf("Integration Tests...\n\n");

    // NOTE: It is very easy to statically initialize these input structs.
    // I have to create multiple instances of them.  I free up the memory
    // for each one in function 'run_test'
    count++;
    TestInput input_wiki_ex = { 4, {{1, 6}, {2, 5}, {3, 7}, {4, 10}}, 0};
    input_ptr = &input_wiki_ex;
    pass += run_test("test_least_squares_n1_{{0, 0}}", &leastsquares, input_ptr, 0);

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
