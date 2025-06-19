/*
 * Maze.cpp
 *
 * CS15 Lab 4
 * 
 * Implementation of a maze class that creates directed, acyclic, perfect
 * mazes.
 * 
 * Originally created by Chris Gregg (Feb 2014) based on maze creator at
 *                         http://azerdark.wordpress.com/2009/03/29/588/
 * Edited and updated by:
 *        Eliza Schreibman and Mark A. Sheldon (Feb 2017)
 *        Tonya Sinha and Matias Korman (Feb 2019)
 *        Elizabeth Hom (Sept 2020)
 *        Hameedah Lawal (Feb 2025) - moved solve functions to Solver and  
 *                                    created an init function, a getter, 
 *                                    and a setter
 */

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <ctime>

#include "Maze.h"

/*
 * really_random == true makes the random number generator in init() use 
 * the current time for more random mazes. 
 * 
 * really_random == false seeds the random number generator with 0 so
 * maze sequences are repeatable for debugging.
 */
static const bool really_random = false;

using namespace std;

/* Constructor
 *    Purpose: Construct an instance of a maze
 * Parameters: None
 *    Returns: None
 */
Maze::Maze() { }

/* init
 *    Purpose: Initial and generate an instance of a maze
 * Parameters: int -- desired size of the maze
 *    Returns: None
 */
void Maze::init(int size)
{
    if (really_random) {
        srand(time(NULL));
    } else {
        srand(0U);
    }

    maze_size = size;
    maze_array_size = maze_size * 2 + 1; /* Actual size of array */
    generate_maze();
}

/* mark_position
 *    Purpose: Place 'marker' at position 'p'
 * Parameters: Position -- position to place 'marker'; char -- marker to place
 *    Returns: None
 */
void Maze::mark_position(Position p, char marker) 
{
    maze[p.getRow()][p.getCol()] = marker;
}

/* marker_at
 *    Purpose: One way to index the maze by using a Position object, rather
 *             than specifying row/col separately.
 * Parameters: Position -- position of the maze
 *    Returns: char& -- row/col within the maze using Position object
 *
 *       Note: Useful for functions that want to pass and return Positions
 */
char &Maze::marker_at(Position p)
{
    return maze[p.getRow()][p.getCol()];
}

/* num_rows
 *    Purpose: Getter for the number of rows in the maze
 * Parameters: None
 *    Returns: int -- the number of rows in the maze
 */
int Maze::num_rows()
{
    return maze_array_size - 1;
}

/* num_cols
 *    Purpose: Getter for the number of columns in the maze
 * Parameters: None
 *    Returns: int -- the number of columns in the maze
 */
int Maze::num_cols()
{
    return maze_array_size - 1;
}

/*************************************************************/
/*** The code below here was originally taken from         ***/
/*** https://azerdark.wordpress.com/2009/03/29/588/        ***/
/***                                                       ***/
/*** Chris Gregg added a function to convert the           ***/
/*** original mazes from an integer-based representation   ***/
/*** to a character-based one so we could have ASCII       ***/
/*** output.                                               ***/
/***                                                       ***/
/*** Mark A. Sheldon changed the principle representation  ***/
/*** to be character-based and reorganized the code to be  ***/
/*** more modular, to have abstraction boundaries, and to  ***/
/*** have better variable names.                           ***/
/***                                                       ***/
/*** You are not expected to understand this code.         ***/
/*************************************************************/

/* generate_maze
 *    Purpose: Generates and initializes a maze
 */
void Maze::generate_maze()
{
    int index = 0;
    int backtrack_x[MAX_CELLS];
    int backtrack_y[MAX_CELLS];

    initialize_maze();

    backtrack_x[index] = 1;
    backtrack_y[index] = 1;
    maze_generator(index, backtrack_x, backtrack_y, 1, 1, maze_size, 1);

    install_start_finish();
}

/* initialize_maze
 *    Purpose: Sets up a maze, including the walls and borders
 */
void Maze::initialize_maze()
{
    for (int row = 0; row < MAX_ARRAY_SIZE; ++row) {
        for (int col = 0; col < MAX_ARRAY_SIZE; ++col) {
            if (row % 2 == 0 or col % 2 == 0) {
                maze[row][col] = WALL;
            } else {
                maze[row][col] = EMPTY;
            }
        }
    }
}

/* install_start_finish
 *    Purpose: Installs the start and finish points of the maze. Currently,
 *             always starts in the upper left corner (inside border walls) and
 *             finishes in the lower right corner (also inside border walls).
 */
void Maze::install_start_finish()
{
    maze[1][1] = START;
    maze[maze_array_size - 2][maze_array_size - 2] = FINISH;
}

/* maze_generator
 *    Purpose: Generates actual maze through using a backtracking search with
 *             some randomness to generate the maze.
 */
void Maze::maze_generator(int index, int backtrack_x[MAX_CELLS],
                          int backtrack_y[MAX_CELLS], int x, int y, int n,
                          int visited)
{
    if (visited < n * n) {
        int neighbour_valid = -1;
        int neighbour_x[4];
        int neighbour_y[4];
        int step[4];

        int x_next;
        int y_next;

        if (x - 2 > 0 and is_closed(x - 2, y)) {   // upside
            neighbour_valid++;
            neighbour_x[neighbour_valid] = x - 2;;
            neighbour_y[neighbour_valid] = y;
            step[neighbour_valid] = 1;
        }

        if (y - 2 > 0 and is_closed(x, y - 2)) {   // leftside
            neighbour_valid++;
            neighbour_x[neighbour_valid] = x;
            neighbour_y[neighbour_valid] = y - 2;
            step[neighbour_valid] = 2;
        }

        if (y + 2 < n * 2 + 1 and is_closed(x, y + 2)) { // rightside
            neighbour_valid++;
            neighbour_x[neighbour_valid] = x;
            neighbour_y[neighbour_valid] = y + 2;
            step[neighbour_valid] = 3;
        }

        if (x + 2 < n * 2 + 1 and is_closed(x + 2, y)) { // downside
            neighbour_valid++;
            neighbour_x[neighbour_valid] = x + 2;
            neighbour_y[neighbour_valid] = y;
            step[neighbour_valid] = 4;
        }

        if (neighbour_valid == -1) {
            // backtrack
            x_next = backtrack_x[index];
            y_next = backtrack_y[index];
            index--;
        }

        if (neighbour_valid != -1) {
            int randomization = neighbour_valid + 1;
            int random = rand() % randomization;
            x_next = neighbour_x[random];
            y_next = neighbour_y[random];
            index++;
            backtrack_x[index] = x_next;
            backtrack_y[index] = y_next;

            int rstep = step[random];

            if (rstep == 1)
                maze[x_next + 1][y_next] = EMPTY;
            else if (rstep == 2)
                maze[x_next][y_next + 1] = EMPTY;
            else if (rstep == 3)
                maze[x_next][y_next - 1] = EMPTY;
            else if (rstep == 4)
                maze[x_next - 1][y_next] = EMPTY;
            visited++;
        }

        maze_generator(index, backtrack_x, backtrack_y,
                x_next, y_next, n, visited);
    }
}

/* print
 *    Purpose: Prints maze to standard output
 * Parameters: none
 *    Returns: none
 */
void Maze::print()
{
    for (int row = 0; row < maze_array_size; ++row) {
        for (int col = 0; col < maze_array_size; ++col) {
            cout << maze[row][col];
        }
        cout << endl;
    }
    cout << endl;
}

/*
void Maze::human_readable_maze()
{
    for (int a = 0; a < maze_array_size; a++) {
        for (int b = 0; b < maze_array_size; b++) {
            if (a == 1 and b == 1)
                maze[a][b] = 'S'; // the start location
            else if (a == maze_array_size - 2 and
                                 b == maze_array_size - 2) {
                // the finish location
                maze[a][b] = 'F';
            } else if (maze[a][b] == WALL)
                maze[a][b] = 'X';
            else
                maze[a][b] = ' ';
        }
    }
}
*/

/* is_closed
 *    Purpose: Determines whether the maze is closed
 * Parameters: int -- (x,y) position indices
 *    Returns: 1 if maze is fully closed, otherwise 0
 */
int Maze::is_closed(int x, int y)
{
    if (maze[x - 1][y] == WALL and
        maze[x][y - 1] == WALL and
        maze[x][y + 1] == WALL and
        maze[x + 1][y] == WALL) {
        return 1;
    }

    return 0;
}

/* is_same_solution_as
 *    Purpose: Determines whether two mazes have the same solution
 * Parameters: Maze -- a different Maze object
 *    Returns: False if current maze solution is different from passed in Maze,
 *             otherwise True
 */
bool Maze::is_same_solution_as(Maze another_maze)
{
    for (int row = 0; row < maze_array_size; row++) {
        for (int col = 0; col < maze_array_size; col++) {
            if (maze[row][col] != another_maze.maze[row][col]) {
                return false;
            }
        }
    }

    return true;
}
