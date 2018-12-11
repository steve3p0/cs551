/* HW #4: Least Squares Polynomial Interpolation Library
 * Steve Braich
 * CS 551
 *
 * Source and References:
 *   - Quadratic FPToolkit.c - Dr. David Ely
 *   - https://en.wikipedia.org/wiki/Least_squares
 *   - https://en.wikipedia.org/wiki/Polynomial_least_squares
 *   - https://www.wikiwand.com/en/Linear_least_squares#/Example
 *
 * Dependencies:
 *   - X11 Lib https://www.x.org/wiki/ProgrammingDocumentation/
 *   - LeastSquares.h      - Steve Braich
 *   - LeastSquaresTests.h - Steve Braich
 *   - FPToolkit.h         - Dr. David Ely
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
 *  your password and each will take a few minutes.  At some Point it might
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
 *  - LeastSquares.c (this file)
 *  - LeastSquares.h
 *  - LeastSquaresTests.h
 *  - FPToolkit.h
 *
 *  do the following to compile:
 *
 *  cc LeastSquares.c -lm -lX11
 *  ./a.out
 * ======================================================================================================
 */

#include <stdio.h>
#include <math.h>
#include "FPToolkit.h"
#include "bsplines.h"

void drawWindow()
{
    // Draw the window
    G_init_graphics(800, 600);
    G_rgb(0.3,0.3,0.3);
    G_clear();
    G_rgb(1,1,0);
}

void saveUserClicks(Point *data, int size)
{
    double tmp[2];

    // Fill the data points array with user clicks
    for(int i = 0; i < size; ++i)
    {
        // Wait for the user to click
        G_wait_click(tmp);

        // What is this doing?
        G_fill_circle(tmp[0], tmp[1], 2);

        // Convert double[2] to Point typedef
        data[i].x = tmp[0];
        data[i].y = tmp[1];
    }
}

int main()
{
    int n;
    printf("Enter the number of points to create splines from.\n -> ");
    scanf("%d", &n);

    drawWindow();
    Point data[n];
    saveUserClicks(data, n);

    Point q[4];
    Point pixel;

    for (int i = 0; i < n; i++)
    {
        q[0] = data[i];
        q[1] = data[i+1];
        q[2] = data[i+2];
        q[3] = data[i+3];

        // For each Point, draw t from 0 to 1
        for(double t = 0.0; t <= 1.0; t += 0.01)
        {
            pixel = Q01234(q, t);
            G_point(pixel.x, pixel.y);
        }

        // wait before drawing any more
        G_wait_key();
    }

    G_wait_key();
    G_save_image_to_file("bsplines.xwd");
}
