/*
 * Maze.h
 *
 * CS15 Lab 04: Recursion
 * 
 * Interface of Maze class that includes relevant functions such as generating 
 * and printing a maze.
 * 
 * Originally created by Chris Gregg (Feb 2014) based on maze creater at
 *                         http://azerdark.wordpress.com/2009/03/29/588/
 * Position-based approach added by Mark A. Sheldon (Feb 2017)
 *
 * Edited and updated by:
 *        Eliza Schreibman and Mark A. Sheldon (Feb 2017)
 *        Tonya Sinha and Matias Korman (Feb 2019)
 *        Elizabeth Hom (Sept 2020)
 */

#ifndef __MazeCreator__maze__H
#define __MazeCreator__maze__H

#include "Position.h"

class Maze 
{
public:
    Maze();
    void init(int size);
    void print();
    void mark_position(Position p, char marker);
    char &marker_at(Position p);
    int  num_rows();
    int  num_cols();

private:
    static const int  MAX_MAZE_SIZE  = 30;
    static const int  MAX_ARRAY_SIZE = 2 * MAX_MAZE_SIZE;
    static const int  MAX_CELLS      = MAX_MAZE_SIZE * MAX_MAZE_SIZE;

    static const char WALL   = 'X',
                      EMPTY  = ' ',
                      START  = 'S',
                      FINISH = 'F';

    char maze[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];
    int  maze_size;
    int  maze_array_size;

    /* These are for the maze infrastructure.  You can ignore them. */
    void initialize_maze     ();
    void generate_maze       ();
    void maze_generator      (int index,
                              int backtrack_x[MAX_CELLS],
                              int backtrack_y[MAX_CELLS],
                              int x, int y, int n, int visited);
    void install_start_finish();
    int  is_closed           (int x, int y);
    bool is_same_solution_as(Maze another_maze);
};

#endif /* defined(__MazeCreator__maze__H) */
