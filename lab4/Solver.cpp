/*
 * Solver.cpp
 *
 * CS15 Lab 4
 *
 * Implementation of a solver class that creates recursive functions for 
 * solving a given maze.
 *
 * TODO: Student must complete the implementation of solve() and determine
 *       the length of the completion paths.
 */

#include "Solver.h"

/* Constructor
 *    Purpose: Construct an instance of a Solver
 * Parameters: Maze -- desired maze to solve
 *    Returns: None
 */
Solver::Solver(Maze* maze_to_solve)
{
    maze = maze_to_solve;
}

/* solve
 *    Purpose: Public solve function that drives solving of maze
 * Parameters: None
 *    Returns: None
 */
void Solver::solve()
{
    solve(Position(1, 1));
    maze->mark_position(Position(1,1), START); // Necessary to reset start 
                                              // position to START because
                                              // private solve() sets to '.'
}

/* solve
 *    Purpose: Solves the maze using Position object.
 * Parameters: Position -- position to solve from
 *    Returns: boolean -- True if maze can be solved, false if no solution
 */
bool Solver::solve(Position p)
{
    // TODO: YOUR CODE HERE
    // This is a stub -- remove entire body, then implement
    (void) p;

    return false;    
}

/* path_length
 *    Purpose: Determines length of path from start to finish
 * Parameters: None
 *    Returns: int -- total path length
 */
int Solver::path_length()
{
    return num_dots_by_rows(1) + 1;
}

/* num_dots_by_rows
 *    Purpose: Determines number of dots in the maze starting at a given row
 *             by recursing on row index
 * Parameters: int -- row to start counting dots
 *    Returns: int -- number of dots in maze path
 */
int Solver::num_dots_by_rows(int row)
{
    // TODO: YOUR CODE HERE
    // This is a stub -- remove entire body, then implement
    (void) row;

    return NOT_FOUND;
}

/* num_dots_in_row
 *    Purpose: Determines number of dots in a given row starting at a given
 *             column by recursing on column index
 * Parameters: int -- Row/col position
 *    Returns: int -- umber of dots in a given row starting at given column
 */
int Solver::num_dots_in_row(int row, int col)
{
    // TODO: YOUR CODE HERE
    // This is a stub -- remove entire body, then implement
    (void) row;
    (void) col;

    return NOT_FOUND;
}

/* solve_and_count
 *    Purpose: Assumes the maze is not solved and recursively solves the maze
 *             AND counts final path length.
 * Parameters: None
 *    Returns: int -- length of final path, i.e. the number of '.'s + 1
 */
int Solver::solve_and_count()
{
    int distance;

    distance = solve_and_count(Position(1, 1));

    maze->mark_position(Position(1,1), START);
    return distance;
}

/* solve_and_count
 *    Purpose: Solves the maze and returns path starting at given position
 * Parameters: Position -- position to solve and count from 
 *    Returns: int -- length of path starting at the given position
 */
int Solver::solve_and_count(Position p)
{
    // TODO: YOUR CODE HERE
    // This is a stub -- remove entire body, then implement
    (void) p;

    return NOT_FOUND;
}

/* is_valid_dist
 *    Purpose: Determines whether a given distance is valid
 * Parameters: int -- distance traveled
 *    Returns: bool -- true if the distance is valid (!= -1), otherwise false
 */
bool Solver::is_valid_dist(int distance)
{
    return distance != NOT_FOUND;
}