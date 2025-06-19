/*
 * Solver.h
 *
 * CS15 Lab 04: Recursion
 * 
 * Interface of Solver class that includes relevant functions such as 
 * solving and counting the solved path of a maze.
 * 
 * Edited and updated by:
 *        Hameedah Lawal (Feb 2025) - moved solve functions from Maze to Solver
 */

#ifndef _SOLVER_H_
#define _SOLVER_H_

#include "Position.h"
#include "Maze.h"

class Solver 
{
public:
    Solver(Maze* maze_to_solve);
    void solve();
    int  solve_and_count();
    int  path_length();

private:
    Maze* maze;
    static const char WALL   = 'X',
                      EMPTY  = ' ',
                      START  = 'S',
                      FINISH = 'F',
                      PATH   = '.',
                      REJECT = 'b';

    static const int  NOT_FOUND = -1;

    bool solve          (Position p);
    int  solve_and_count(Position p);
    int  num_dots_by_rows(int row);
    int  num_dots_in_row (int row, int col);
    bool is_valid_dist(int distance);
};

#endif
