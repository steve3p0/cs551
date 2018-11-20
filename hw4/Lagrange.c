/* HW #4: Lagrange Polynomial Interpolation Library
 * Steve Braich
 * CS 551
 *
 * Source and References:
 *   - Quadratic FPToolkit.c - Dr. David Ely
 *   - https://en.wikipedia.org/wiki/Lagrange_polynomial
 *   - https://math.stackexchange.com/questions/523907/explanation-of-lagrange-interpolating-polynomial
 *   - https://stackoverflow.com/questions/19305982/xlib-closing-window-always-causes-fatal-io-error
 *
 * Dependencies:
 *   - X11 Lib https://www.x.org/wiki/ProgrammingDocumentation/
 *   - Lagrange.h      - Steve Braich
 *   - LagrangeTests.h - Steve Braich
 *   - FPToolkit.h     - Dr. David Ely
 * ======================================================================================================
 * PARTS OF THIS CODE WERE TAKEN FROM THE FOLLOWING:
 *
 *  Quadratic FPToolkit.c : A simple set of graphical tools.
 *  FPToolkitDemo.c
 *  Copyright (C) 2018  Ely
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License (version 3)
 *  as published by the Free Software Foundation.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 *  This code assumes an underlying X11 environment.
 *
 *  Most freshly installed unbuntu environments do not have the X11 developr
 *  stuff they'll need to do graphics. To download X11 developer stuff, connect
 *  to the internet and issue the following two commands.  Each will ask for
 *  your password and each will take a few minutes.  At some point it might
 *  even look like nothing is happening....be patient :
 *
 *  sudo  apt-get  install  libx11-dev
 *  sudo  apt-get  install  xorg-dev
 *
 * ======================================================================================================
 *  Modification: Steve Braich
 *  Renamed FPToolkit.c to FPToolkit.h,
 *  Reason: This file is a header file, thus it should have a .h extension.
 *  SEE https://stackoverflow.com/questions/1695224/what-do-c-and-h-file-extensions-mean-to-c
 *  I am using an IDE (JetBrains CLION) which will get bent out of shape if you don't.
 *  This IDE allows me to step thru code visually among other great features.
 * ======================================================================================================
 *  TO COMPILE AND RUN THIS CODE
 * ======================================================================================================
 *  If this file and the following files are in the same directory:
 *
 *  - Lagrange.c (this file)
 *  - Lagrange.h
 *  - LagrangeTests.h
 *  - FPToolkit.h
 *
 *  do the following to compile:
 *
 *  cc Langrange.c -lm -lX11
 *  ./a.out
 * ======================================================================================================
 */


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "FPToolkit.h"
#include "Lagrange.h"
#include "LagrangeTests.h"

/* Steve Braich: Test FPI Toolkit Graphics
 * This function graphs serveral objects using Xll.
 * Use this code to test the environment works with Xll
 */
int test_fpitoolkit_graphics()
{
    int    swidth, sheight ;
    double lowleftx, lowlefty, width, height ;
    double x[10], y[10] ;
    double numxy ;
    double a[20], b[20] ;
    double numab ;

    // must do this before you do 'almost' any other graphical tasks
    swidth = 400 ;  sheight = 600 ;
    G_init_graphics (swidth,sheight) ;  // interactive graphics

    // clear the screen in a given color
    G_rgb (0.3, 0.3, 0.3) ; // dark gray
    G_clear () ;

    // draw a point
    G_rgb (1.0, 0.0, 0.0) ; // red
    G_point (200, 580) ; // hard to see

    // draw a line
    G_rgb (0.0, 1.0, 0.0) ; // green
    G_line (0,0, swidth-1, sheight-1) ;

    // aligned rectangles
    G_rgb (0.0, 0.0, 1.0) ; // blue
    lowleftx = 200 ; lowlefty = 50 ; width = 10 ; height = 30 ;
    G_rectangle (lowleftx, lowlefty, width, height) ;
    lowleftx = 250 ;
    G_fill_rectangle (lowleftx, lowlefty, width, height) ;

    // triangles
    G_rgb (1.0, 1.0, 0.0) ; // yellow
    G_triangle (10, 300,  40,300,  60,250) ;
    G_fill_triangle (10,100,  40,100,  60,150) ;

    // circles
    G_rgb (1.0, 0.5, 0.0) ; // orange
    G_circle (100, 300, 75) ;
    G_fill_circle (370, 200, 50) ;

    // polygons
    G_rgb (0.0, 0.0, 0.0) ; // black
    x[0] = 100 ;   y[0] = 100 ;
    x[1] = 100 ;   y[1] = 300 ;
    x[2] = 300 ;   y[2] = 300 ;
    x[3] = 300 ;   y[3] = 100 ;
    x[4] = 200 ;   y[4] = 175 ;
    numxy = 5 ;
    G_polygon (x,y,numxy) ;

    G_rgb (0.4, 0.2, 0.1) ; // brown
    a[0] = 300 ;   b[0] = 400 ;
    a[1] = 350 ;   b[1] = 450 ;
    a[2] = 275 ;   b[2] = 500 ;
    a[3] = 125 ;   b[3] = 400 ;
    numab = 4 ;
    G_fill_polygon (a,b,numab) ;

    //===============================================

    double p[2], q[2] ;

    G_rgb(1,0,0) ;
    G_wait_click(p) ;
    G_fill_circle(p[0],p[1],2) ;
    G_wait_click(q) ;
    G_fill_circle(q[0],q[1],2) ;
    G_rgb(0,1,0.5) ;
    G_line(p[0],p[1], q[0],q[1]) ;

    int key ;
    key =  G_wait_key() ; // pause so user can see results

    G_save_image_to_file("demo.xwd") ;
}


/* Draw Lagrange Polynomial
 * Create the Window to draw the Language Polynomial. Wait for user
 * to click on the window and store the clicks as data points,
 * Lastly, draw the Lagrange polynomial.
 */
int draw_lagrange(int degree)
{
    int swidth;
    int sheight;

    // must do this before you do 'almost' any other graphical tasks
    swidth = 800;
    sheight = 600;
    G_init_graphics(swidth, sheight);  // interactive graphics

    // clear the screen in a given color
    G_rgb(0.3, 0.3, 0.3);
    G_clear();

    // Let's make it red
    G_rgb(1, 0, 0);

    // x and y coordinates of each point
    Point data[100];

    // Store data points
    // read each user left mouse click
    double point[2];

    int i;
    for (i = 0; i < degree; ++i)
    {
        G_wait_click(point);
        G_fill_circle(point[0], point[1], 2);

        data[i].x = point[0];
        data[i].y = point[1];
    }

    // Draw the Polynomial
    for (i = 0; i < swidth; ++i)
    {
        double start_y = lagrange(degree, (double)i,     data);
        double end_y   = lagrange(degree, (double)i + 1, data);

        G_line (i, start_y, i + 1, end_y);
    }

    int key = G_wait_key();
}

/* Main Menu
 * TODO: Figure out a way to make menus testable.
 */
int main()
{
     while (1)
    {
        printf("\n\n");
        printf("\tPolynomial Interpolation Graphing Tool\n");
        printf("\t--------------------------------------\n\n");
        printf("\tEnter 'g' to Run Graphics Test (FP Toolkit)\n");
        printf("\tEnter 't' to Run Automated Tests\n");
        printf("\tEnter 'q' to Quit\n\n");
        printf("\tOr enter in the number of points (1-100) to Graph a Quadratic: ");

        int degree;

        char menu[100];
        scanf("%s", menu);

        char *ptr;
        degree = strtol(menu, &ptr, 10);

        if (degree > 0 && degree < 101)
        {
            draw_lagrange(degree);
        }
        else if (strlen(menu) == 1)
        {
            char choice = toupper(menu[0]);

            switch (choice)
            {
                //case 'g':
                case 'G':
                    // Environment Test
                    test_fpitoolkit_graphics();
                    break;
                case 'T':
                    // Run tests
                    test_lagrange();
                    //test_newton();
                    break;
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