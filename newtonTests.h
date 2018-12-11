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

#include <string.h>
#include <stdbool.h>
#include "newton.h"

typedef struct test
{
    int count;
    int pass;

    char testname [100][1000];
    char results  [100][1000];
    char messages [100][1000];
    char failed   [100][1000];

    char stdinout[1000];
    int passfail[100];

} Test;

// Used to evaluate eequality of double (floating point numbers)
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

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);

    return result;
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

////////////////////////////////////////////////////

int test_dummy(char *test_name, char *output)
{
    printf("PASS - %s\n", test_name);
    //printf("FAIL - %s\n", test_name);
    return 1;
}

// TODO: Finish rest of unit tests
int test_runner()
{
    printf("\nRunning Tests...\n\n");

    int count = 0;
    int pass = 0;
    char test_output[1000];
    //char *output;

    //Test t

    count++;
    pass += test_dummy("test_dummy1", test_output);

    count++;
    pass += test_dummy("test_dummy2", test_output);

    count++;
    pass += test_dummy("test_dummy3", test_output);

    printf("\nTest Runner: %d out of %d tests PASSED\n", pass, count);
}




#endif //NEWTON_NEWTONTESTS_H
