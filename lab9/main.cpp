/*
 * main.cpp
 * CS15 Graph Traversals Lab
 * 
 * Driver for CS15 Graph Traversals Lab to help practicing BFS and DFS.
 *
 * ChangeLog:
 *   17 Nov 2020: zgolds01
 *       main.cpp driver created
 *   12 April 2021: mchamp03
 *       Refactored for use in lab10
 *   01 April 2025: kquint02
 *       removed usage() & updated style
 */

#include <fstream>
#include <ios>
#include <iostream>
#include <string>

#include "PathFinder.h"

/* assert_file
 *   Purpose: Check if a filestream is good to be used.
 * Arguments: std::ios &file       -- opened filestream.
 *            std::string filename -- name of file opened.
 *   Returns: None
 */
void assert_file(std::ios &file, std::string filename)
{
    if (not file.good()) {
        std::cerr << filename << " cannot be opened." << std::endl;
        exit(EXIT_FAILURE);
    }
}

/* main
 *   Purpose: Populate/Initialize a PathFinder instance and run.
 * Arguments: int argc     -- number of commandline arguments.
 *            char *argv[] -- commandline arguments.
 *   Returns: int -- 0 if exit is successful; EXIT_FAILURE otherwise.
 */
int main(int argc, char *argv[])
{
    PathFinder    pf;
    std::ifstream data;

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " cityFile" << std::endl;
        exit(EXIT_FAILURE);
    }

    data.open(argv[1]);
    assert_file(data, argv[1]);
    pf.populate_graph(data);
    data.close();

    pf.run();

    return 0;
}
