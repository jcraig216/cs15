/*
 *  gerp.h
 *  Jack Craig, Clark Morris
 *  04/24/2025
 *
 *  CS 15 Project 4: Gerp
 *  Interface for the Gerp file indexing and search system.
 *  Declares the Gerp class which handles directory traversal,
 *  file processing, query handling, and output generation.
 *  Uses FSTree for directory navigation and custom hash tables
 *  for efficient text searching.
 *
 */

#ifndef GERP_H
#define GERP_H

#include "index.h"
#include "FSTree.h"
#include <string>
#include <fstream>
#include <set>
#include <vector>

class Gerp
{
public:
    Gerp();

    // Core functionality
    void buildIndex(const std::string &directory);
    void run(const std::string &outputFile);

private:
    // Member variables
    Index index;
    std::ofstream outStream;
    std::string currentOutputFile;

    // Directory processing
    void processDirectory(DirNode *node, const std::string path);
    std::string buildDirectoryPath(DirNode *node,
                                   const std::string &currentPath);
    void processFilesInDirectory(DirNode *node, const std::string &path);
    void processSubDirectories(DirNode *node, const std::string &path);

    // File handling
    std::string constructFilePath(DirNode *node, const std::string &path,
                                  int fileIndex);
    std::string normalizePath(std::string path);
    void processFile(const std::string &filePath);

    // Query processing
    void handleQuery(const std::string &query, bool caseSensitive);
    std::vector<LineEntry> getSearchResults(const std::string &query,
                                            bool caseSensitive) const;
    bool processAndWriteResults(const std::vector<LineEntry> &results);
    bool addUniqueEntry(const LineEntry &entry,
                        std::set<std::string> &seenLines) const;
    void writeFormattedLine(const LineEntry &entry);
    void handleNotFound(const std::string &query, bool caseSensitive);

    // Output management
    void switchOutputFile(const std::string &newFile);

    // String utilities
    std::vector<std::string> splitQuery(const std::string &input);
    std::string sanitizeWord(const std::string &word) const;

    // Input processing
    bool processInput(std::string &input);
    void processTokens(const std::string &input);
    bool processSingleToken(const std::string &token,
                            std::istringstream &iss,
                            bool &nextInsensitive);
    void handleFileSwitch(std::istringstream &iss);
    void handleExit();
};

#endif