/*
 *  main.cpp
 *  Jack Craig
 *  02/12/2025
 *
 *  CS 15 Project 1: Metro Simulator
 *  Handles running the metro simulator project
 *
 */

#include <iostream>
#include <fstream>
#include <string>

#include "MetroSim.h"

using namespace std;

int main(int argc, char *argv[])
{
        if (argc < 3 or argc > 4)
        {
                cerr
                    << "Usage: ./MetroSim stationsFile \
                    outputFile [commandsFile]"
                    << endl;
                exit(EXIT_FAILURE);
        }
        string stationsFile(argv[1]);
        string outputFile(argv[2]);
        MetroSim metroSim(stationsFile, outputFile);

        if (argc == 4)
        {
                ifstream commandsFile(argv[3]);
                if (not commandsFile.is_open())
                {
                        cerr << "Error: could not open file " << argv[3]
                             << endl;
                        exit(EXIT_FAILURE);
                }
                metroSim.run(commandsFile);
        }
        else
        {
                metroSim.run(cin);
        }

        return 0;
}