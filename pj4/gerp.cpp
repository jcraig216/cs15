/*
 *  gerp.cpp
 *  Jack Craig, Clark Morris
 *  04/24/2025
 *
 *  CS 15 Project 4: Gerp
 *  Main implementation file for Gerp file indexing and search system.
 *  Handles directory traversal, file processing, query handling, and output.
 *  Uses FSTree for directory structure and custom hash tables for indexing.
 *
 */

#include "gerp.h"
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <unistd.h>
#include <sys/mman.h>

/*
 * name:      Gerp constructor
 * purpose:   Initialize Gerp object with empty output stream
 * arguments: None
 * returns:   None
 * effects:   Initializes outStream member
 */
Gerp::Gerp() : outStream()
{
    if (outStream.is_open())
    {
        outStream.close();
    }
}

/*
 * name:      buildIndex
 * purpose:   Build search index from directory structure
 * arguments: directory - root directory to index
 * returns:   None
 * effects:   Creates FSTree and populates index with file contents
 */
void Gerp::buildIndex(const std::string &directory)
{
    FSTree tree(directory);
    processDirectory(tree.getRoot(), "");
}

/*
 * name:      processDirectory
 * purpose:   Process all files and subdirectories in current directory node
 * arguments: node - current directory node, path - accumulated path string
 * returns:   None
 * effects:   Recursively processes entire directory tree
 */
void Gerp::processDirectory(DirNode *node, std::string path)
{
    path = buildDirectoryPath(node, path);
    processFilesInDirectory(node, path);
    processSubDirectories(node, path);
}

/*
 * name:      buildDirectoryPath
 * purpose:   Construct path string for current directory node
 * arguments: node - current directory node, currentPath - accumulated path
 * returns:   Complete path string for current node
 * effects:   Concatenates node name to existing path with separator
 */
std::string Gerp::buildDirectoryPath(DirNode *node,
                                     const std::string &currentPath)
{
    return currentPath.empty() ? node->getName()
                               : currentPath + "/" + node->getName();
}

/*
 * name:      processFilesInDirectory
 * purpose:   Process all files in current directory node
 * arguments: node - current directory node, path - complete path to directory
 * returns:   None
 * effects:   Processes each file through constructFilePath and processFile
 */
void Gerp::processFilesInDirectory(DirNode *node, const std::string &path)
{
    for (int i = 0; i < node->numFiles(); ++i)
    {
        std::string filePath = constructFilePath(node, path, i);
        processFile(normalizePath(filePath));
    }
}

/*
 * name:      constructFilePath
 * purpose:   Create complete path to file from directory and filename
 * arguments: node - directory node, path - directory path, fileIndex - file
 * idx
 * returns:   Complete file path string
 * effects:   Combines directory path with filename
 */
std::string Gerp::constructFilePath(DirNode *node, const std::string &path,
                                    int fileIndex)
{
    return path + "/" + node->getFile(fileIndex);
}

/*
 * name:      normalizePath
 * purpose:   Remove duplicate slashes from file paths
 * arguments: path - path string to normalize
 * returns:   Path with duplicate slashes removed
 * effects:   Modifies input string in place
 */
std::string Gerp::normalizePath(std::string path)
{
    size_t dblSlash;
    while (not((dblSlash = path.find("//")) == std::string::npos))
    {
        path.replace(dblSlash, 2, "/");
    }
    return path;
}

/*
 * name:      processSubDirectories
 * purpose:   Recursively process all subdirectories of current node
 * arguments: node - current directory node, path - path to current directory
 * returns:   None
 * effects:   Calls processDirectory on each valid subdirectory
 */
void Gerp::processSubDirectories(DirNode *node, const std::string &path)
{
    for (int i = 0; i < node->numSubDirs(); ++i)
    {
        DirNode *subdir = node->getSubDir(i);
        if (subdir)
        {
            processDirectory(subdir, path);
        }
    }
}

/*
 * name:      processFile
 * purpose:   Read file contents and add to search index
 * arguments: filePath - complete path to file to process
 * returns:   None
 * effects:   Opens file, reads lines, and adds to index with line numbers
 */
void Gerp::processFile(const std::string &filePath)
{
    std::ifstream file(filePath);
    std::string line;
    int lineNum = 1;

    while (std::getline(file, line))
    {
        // Trim trailing CR (for CRLF files)
        // if (not(line.empty()) and line.back() == '\r')
        // {
        //     line.pop_back();
        // }
        index.addLine(filePath, lineNum++, line);
    }
    file.close();
}

/*
 * name:      handleQuery
 * purpose:   Process search query with case sensitivity option
 * arguments: query - search term, caseSensitive - search mode flag
 * returns:   None
 * effects:   Writes results to output or not found message
 */
void Gerp::handleQuery(const std::string &query, bool caseSensitive)
{
    std::string sanitized = sanitizeWord(query);
    if (sanitized.empty())
    {
        handleNotFound(sanitized, caseSensitive);
        return;
    }
    auto results = getSearchResults(sanitized, caseSensitive);
    bool found = processAndWriteResults(results);
    if (not(found))
    {
        handleNotFound(sanitized, caseSensitive);
    }
}

/*
 * name:      getSearchResults
 * purpose:   Retrieve search results from index based on search mode
 * arguments: query - sanitized search term, caseSensitive - search mode flag
 * returns:   Vector of LineEntry results matching query
 * effects:   Calls appropriate index search function
 */
std::vector<LineEntry> Gerp::getSearchResults(const std::string &query,
                                              bool caseSensitive) const
{
    return caseSensitive ? index.searchCaseSensitive(query)
                         : index.searchCaseInsensitive(query);
}

/*
 * name:      processAndWriteResults
 * purpose:   Filter duplicates and write formatted results to output
 * arguments: results - vector of LineEntry search results
 * returns:   True if results were found, false otherwise
 * effects:   Writes to output stream and maintains set of seen entries
 */
bool Gerp::processAndWriteResults(const std::vector<LineEntry> &results)
{
    std::set<std::string> seenLines;
    bool found = false;

    for (const auto &entry : results)
    {
        if (addUniqueEntry(entry, seenLines))
        {
            writeFormattedLine(entry);
            found = true;
        }
    }

    return found;
}

/*
 * name:      addUniqueEntry
 * purpose:   Check if entry has been seen before
 * arguments: entry - LineEntry to check, seenLines - set of seen entries
 * returns:   True if entry is new, false if duplicate
 * effects:   Modifies seenLines set if entry is new
 */
bool Gerp::addUniqueEntry(const LineEntry &entry,
                          std::set<std::string> &seenLines) const
{
    const std::string &filePath = index.getFile(entry.fileID);
    std::string key = filePath + ":" + std::to_string(entry.lineNum);
    return seenLines.insert(key).second;
}

/*
 * name:      writeFormattedLine
 * purpose:   Write search result in standardized format
 * arguments: entry - LineEntry to format and output
 * returns:   None
 * effects:   Writes to output stream in "path:line: text" format
 */
void Gerp::writeFormattedLine(const LineEntry &entry)
{
    const std::string &filePath = index.getFile(entry.fileID);
    const std::string &lineText = index.getLine(entry.lineID);
    outStream << filePath << ":" << entry.lineNum << ": "
              << lineText << "\n"; // \r
}

/*
 * name:      handleNotFound
 * purpose:   Write appropriate "not found" message to output
 * arguments: query - original search term, caseSensitive - search mode flag
 * returns:   None
 * effects:   Writes to output stream with suggestion if case-sensitive
 */
void Gerp::handleNotFound(const std::string &query, bool caseSensitive)
{
    outStream << query << " Not Found."
              << (caseSensitive ? " Try with @insensitive or @i." : "")
              << "\n"; //\r not needed
}

/*
 * name:      switchOutputFile
 * purpose:   Close current output file and open new one
 * arguments: newFile - path to new output file
 * returns:   None
 * effects:   Modifies outStream and currentOutputFile members
 * throws:    runtime_error if file cannot be opened
 */
void Gerp::switchOutputFile(const std::string &newFile)
{
    if (outStream.is_open())
    {
        outStream.close();
    }
    // Open in binary mode to prevent CRLF conversion on Windows
    outStream.open(newFile, std::ios::binary);
    if (not(outStream))
    {
        throw std::runtime_error("Failed to open output file: " + newFile);
    }
    currentOutputFile = newFile;
}

/*
 * name:      splitQuery
 * purpose:   Split input string into whitespace-separated tokens
 * arguments: input - string to split
 * returns:   Vector of string tokens
 * effects:   Uses string stream to split on whitespace
 */
std::vector<std::string> Gerp::splitQuery(const std::string &input)
{
    std::istringstream iss(input);
    std::vector<std::string> words;
    std::string word;
    while (iss >> word)
    {
        words.push_back(word);
    }
    return words;
}

/*
 * name:      sanitizeWord
 * purpose:   Remove non-alphanumeric characters from word edges
 * arguments: word - string to sanitize
 * returns:   Sanitized word or empty string if no alphanumerics
 * effects:   Preserves apostrophes within word
 */
std::string Gerp::sanitizeWord(const std::string &word) const
{
    size_t first = 0, last = word.size() - 1;
    // Skip leading non-alphanumeric (excluding apostrophes)
    while (first <= last and not(std::isalnum)(
                                 static_cast<unsigned char>(word[first])))
        first++;
    // Skip trailing non-alphanumeric (excluding apostrophes)
    while (last >= first and not(std::isalnum)(
                                 static_cast<unsigned char>(word[last])))
        last--;
    return (first > last) ? "" : word.substr(first, last - first + 1);
}

/*
 * name:      run
 * purpose:   Main execution loop for Gerp program
 * arguments: outputFile - initial output file path
 * returns:   None
 * effects:   Processes user input until quit command
 */
void Gerp::run(const std::string &outputFile)
{
    switchOutputFile(outputFile);
    std::string input;
    while (processInput(input))
    {
        processTokens(input);
    }
}

/*
 * name:      processInput
 * purpose:   Read and process user input line
 * arguments: input - reference to store input string
 * returns:   True if input was read, false on EOF/quit
 * effects:   Reads from cin and handles EOF condition
 */
bool Gerp::processInput(std::string &input)
{
    if (not(std::getline(std::cin, input)))
    {
        handleExit();
        return false;
    }
    return true;
}

/*
 * name:      processTokens
 * purpose:   Process tokens from input line
 * arguments: input - line of user input
 * returns:   None
 * effects:   Handles commands and queries from tokenized input
 */
void Gerp::processTokens(const std::string &input)
{
    std::istringstream iss(input);
    std::string token;
    bool nextInsensitive = false;
    while (iss >> token)
    {
        if (not(token == "@i" or token == "@insensitive"))
        {
            std::cout << "Query? ";
        }
        else
        {
            nextInsensitive = true;
        }
        if (not(processSingleToken(token, iss, nextInsensitive)))
        {
            return;
        }
    }
}

/*
 * name:      processSingleToken
 * purpose:   Process individual input token
 * arguments: token - current token, iss - input stream, nextInsensitive - flag
 * returns:   False if quit command encountered, true otherwise
 * effects:   Handles commands or passes queries to handleQuery
 */
bool Gerp::processSingleToken(const std::string &token,
                              std::istringstream &iss,
                              bool &nextInsensitive)
{
    if (token == "@q" or token == "@quit")
    {
        return false;
    }
    if (token == "@i" or token == "@insensitive")
    {
        nextInsensitive = true;
        return true;
    }
    if (token == "@f")
    {
        handleFileSwitch(iss);
        return true;
    }
    handleQuery(token, not(nextInsensitive));
    nextInsensitive = false;
    return true;
}

/*
 * name:      handleFileSwitch
 * purpose:   Process output file change command
 * arguments: iss - input stream containing filename
 * returns:   None
 * effects:   Attempts to switch output file, handles errors
 */
void Gerp::handleFileSwitch(std::istringstream &iss)
{
    std::string newFile;
    if (iss >> newFile)
    {
        try
        {
            switchOutputFile(newFile);
        }
        catch (const std::runtime_error &e)
        {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }
    else
    {
        std::cerr << "Error: @f requires a filename argument\n";
    }
}

/*
 * name:      handleExit
 * purpose:   Handle program termination
 * arguments: None
 * returns:   None
 * effects:   Prints goodbye message
 */
void Gerp::handleExit()
{
    std::cout << "Goodbye! Thank you and have a nice day.\n";
}

// eof