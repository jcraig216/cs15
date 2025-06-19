/*
 * main.cpp
 *
 * CS15 Lab 04: Recursion
 * 
 * Driver that creates a maze and solves it.
 * 
 * Originally created by Chris Gregg (Feb 2014) based on maze creater at
 *                         http://azerdark.wordpress.com/2009/03/29/588/
 * Edited and updated by:
 *        Eliza Schreibman and Mark A. Sheldon (Feb 2017)
 *        Tonya Sinha and Matias Korman (Feb 2019)
 *        Elizabeth Hom (Sept 2020)
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "Maze.h"
#include "Solver.h"

using namespace std;

int  getMazeSize();

/* main
 *    Purpose: Creates a maze and then solves it!
 * Parameters: None
 *    Returns: int - 0 for a successful exit, 1 for unsuccessful
 */
int main()
{
    int size;

    cout << "MAZE CREATOR and SOLVER\n\n";
    size = getMazeSize();
    Maze maze1;
    maze1.init(size);
    /* Print original maze */
    cout << "HERE IS YOUR MAZE: \n\n";
    maze1.print();

    /* Solve and print maze */
    Solver solver1(&maze1);
    solver1.solve();
    cout << "Your Recursive solution:\n\n";
    maze1.print();

    cout << "The calculated path length is: "<< solver1.path_length()
         << endl << endl;

    /* This time, solve maze and keep track of path length */
    Maze maze2;
    maze2.init(size);
    cout << "New maze of the same size" << endl << endl;
    maze2.print();

    Solver solver2(&maze2);
    int pathLength = solver2.solve_and_count();
    cout << "Solved in " << pathLength << " steps: " << endl << endl;
    maze2.print();

    return 0;
}

/* getMazeSize
 *    Purpose: Asks user for maze size and returns maze size
 * Parameters: None
 *    Returns: None
 *       Note: This function wants a number and uses a square matrix
 *             (2 * size) + 1 on a side. Including a border on all sides,
 *             that means the maze area is (2 * size) - 1 square
 */
int getMazeSize()
{
    string prompt = "Pick maze size in [2 .. 29]\n"
                    "Maze will be (2 * size) - 1 on a side:  ";
    int    mazeSize = -1;
    string restOfLine;
        
    /* As long as input is invalid and not EOF */
    while (not cin.fail() and (mazeSize < 2 or mazeSize > 29)) {
        cout << prompt;
        cin  >> mazeSize;
        getline(cin, restOfLine);
    }

    if (cin.fail()) {
        exit(1);     /* They must have given up -- exit program */
    }

    return mazeSize;
}
