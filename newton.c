#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <complex.h>
#include "newton.h"
#include "newtonTests.h"


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
            Newton *n = init();
            n->Load(n);
            n->Solve(n);
            n->Print(n);
            n->Destroy(n);

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