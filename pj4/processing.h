/*
 *  processing.h
 *  Jack Craig, Clark Morris
 *  04/14/2025
 *
 *  CS 15 Project 4: Gerp (Phase 1)
 *  Declares functions for directory traversal and string sanitization.
 *  Implements core functionality for building file paths and stripping
 *  non-alphanumeric characters.
 *
 */
#ifndef __PROCESSING_H
#define __PROCESSING_H

#include <string>
using namespace std;

string stripNonAlphaNum(string input);
void traverseDirectory(string directory);

#endif