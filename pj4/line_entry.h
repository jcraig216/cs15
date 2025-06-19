/*
 *  line_entry.h
 *  Jack Craig, Clark Morris
 *  04/24/2025
 *
 *  CS 15 Project 4: Gerp
 *  Definition of the LineEntry struct used throughout the Gerp system.
 *  Represents a location in indexed files with file ID, line number,
 *  and unique line ID. Essential for connecting search results back
 *  to original file locations and content.
 *
 */

#ifndef LINE_ENTRY_H
#define LINE_ENTRY_H

#include <cstddef> // For size_t

struct LineEntry
{
    int fileID;    // Unique identifier for the source file
    int lineNum;   // Line number within the file (1-indexed)
    size_t lineID; // Unique identifier for the line content

    // Constructor for easy initialization
    LineEntry(int fid, int ln, size_t lid)
        : fileID(fid), lineNum(ln), lineID(lid) {}
};

#endif