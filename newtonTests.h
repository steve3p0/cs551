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


////////////////////////////////////////////////////

int test_dummy1(char *testname, char *output)
{
    //printf("PASS - %s\n", test_name);
    //printf("FAIL - %s\n", test_name);


//    char *s = concat("PASS - ", test_name);
//    //s = concat(s, "\n");
//    output = concat(output, s);

    //char *new_str;
    //asprintf(&new_str,"%s%s",str1,str2);

//    asprintf(&new_str,"%s%s",str1,str2);

    return 1;
}

//////////////////////////////////////////////////////

Test *init()
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


// TODO: Finish rest of unit tests
int test_runner()
{
    printf("\nRunning Tests...\n\n");

    Test *t = init();

    test_dummy("test_dummy1", t);
    test_dummy("test_dummy2", t);
    test_dummy("test_dummy3", t);

    print(t);

    //free(test_output); // deallocate the string
}




#endif //NEWTON_NEWTONTESTS_H
