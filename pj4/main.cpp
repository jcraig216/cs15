/*
 *  main.cpp
 *  Jack Craig, Clark Morris
 *  04/24/2025
 *
 *  CS 15 Project 4: Gerp
 *  Main driver program for the Gerp file indexing system.
 *  Handles command-line arguments, initializes the Gerp engine,
 *  and manages the high-level program flow including error handling.
 *  Acts as the entry point for the entire application.
 *
 */

#include "gerp.h"
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: ./gerp inputDirectory outputFile\n";
        return EXIT_FAILURE;
    }

    Gerp gerp;
    try
    {
        gerp.buildIndex(argv[1]);
        gerp.run(argv[2]);
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}