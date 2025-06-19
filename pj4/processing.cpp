/*
 *  processing.cpp
 *  Jack Craig, Clark Morris
 *  04/14/2025
 *
 *  CS 15 Project 4: Gerp (Phase 1)
 *  Implements directory traversal via FSTree and string sanitization logic.
 *  Uses helper functions to construct full file paths and process directories.
 *
 */

#include "processing.h"
#include "FSTree.h"
#include "DirNode.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <cctype>

using namespace std;

/*
 * name:      buildPath
 * purpose:   Constructs full filesystem path from DirNode to root
 * arguments: node - Current directory node in FSTree
 * returns:   Complete path as string (e.g., "root/subdir/file.txt")
 * effects:   Traverses parent pointers recursively. Allocates vector for path
 *            components
 */
string buildPath(DirNode *node)
{
    vector<string> pathComponents;
    DirNode *current = node;
    while (not(current == nullptr))
    {
        pathComponents.push_back(current->getName());
        current = current->getParent();
    }
    reverse(pathComponents.begin(), pathComponents.end());

    string fullPath;
    for (size_t i = 0; i < pathComponents.size(); ++i)
    {
        if (not(i == 0))
            fullPath += "/";
        fullPath += pathComponents[i];
    }
    std::cerr << "[PATH] Built path: " << fullPath << "\n";
    return fullPath;
}

/*
 * name:      processDirectory
 * purpose:   Recursively traverses FSTree nodes to print file paths
 * arguments: node - Current node being processed
 * returns:   None
 * effects:   Modifies stdout. Recursively calls itself for subdirectories
 */
void processDirectory(DirNode *node)
{
    string dirPath = buildPath(node);
    // Print files in current directory
    for (int i = 0; i < node->numFiles(); ++i)
    {
        cout << dirPath << "/" << node->getFile(i) << endl;
    }
    // Recurse into subdirectories
    for (int i = 0; i < node->numSubDirs(); ++i)
    {
        processDirectory(node->getSubDir(i));
    }
}

/*
 * name:      traverseDirectory
 * purpose:   Main entry point for directory traversal
 * arguments: directory - Path to root directory
 * returns:   None
 * effects:   Constructs FSTree object. Propagates exceptions from FSTree
 *            constructor on invalid directories
 */
void traverseDirectory(string directory)
{
    FSTree tree(directory);
    processDirectory(tree.getRoot());
}

/*
 * name:      stripNonAlphaNum
 * purpose:   Removes non-alphanumeric characters from string boundaries
 * arguments: input - Raw string to sanitize
 * returns:   Core string containing valid characters
 * effects:   Preserves internal non-alphanumerics. Uses cctype's isalnum()
 *            for character validation
 */
string stripNonAlphaNum(string input)
{
    if (input.empty())
        return "";

    // Find first alphanumeric character
    size_t start = 0;
    while (start < input.size() and not(isalnum(input[start])))
    {
        start++;
    }

    // Find last alphanumeric character
    size_t end = input.size() - 1;
    while (end > start and not(isalnum(input[end])))
    {
        end--;
    }

    return (start > end) ? "" : input.substr(start, end - start + 1);
}