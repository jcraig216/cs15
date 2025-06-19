/*
 *  index.h
 *  Jack Craig, Clark Morris
 *  04/24/2025
 *
 *  CS 15 Project 4: Gerp
 *  Interface for the Index class which implements the core
 *  indexing and search functionality. Contains hash table
 *  implementations for both case-sensitive and case-insensitive
 *  word indexing, along with file and line tracking systems.
 *  Uses separate chaining for collision resolution.
 *
 */

#ifndef INDEX_H
#define INDEX_H

#include "line_entry.h"
#include <vector>
#include <list>
#include <string>
#include <cctype>

class Index
{
public:
    Index();
    ~Index() = default;

    // Core functionality
    void addLine(const std::string &filePath, int lineNum,
                 const std::string &lineText);
    std::vector<LineEntry> searchCaseSensitive(
        const std::string &query) const;
    std::vector<LineEntry> searchCaseInsensitive(
        const std::string &query) const;

    // Data retrieval
    const std::string &getLine(size_t lineID) const;
    const std::string &getFile(int fileID) const;

private:
    // Hash node structure for word entries
    struct HashNode
    {
        std::string key;
        std::vector<LineEntry> entries;
    };

    // File tracking structure
    struct FileEntry
    {
        std::string path;
        int id;
    };

    // Line tracking structure
    struct LineEntryText
    {
        std::string text;
        size_t id;
    };

    // Hash tables
    std::vector<std::list<HashNode>> caseSensitiveTable;
    std::vector<std::list<HashNode>> caseInsensitiveTable;

    // ID management
    std::vector<std::list<FileEntry>> fileTable;
    std::vector<std::string> filePaths;
    std::vector<std::list<LineEntryText>> lineTable;
    std::vector<std::string> lineTexts;

    // Table properties
    size_t capacity;
    size_t size;
    static constexpr double MAX_LOAD_FACTOR = 0.7;

    // Hash table operations
    size_t hashFunction(const std::string &key,
                        size_t tableSize) const;
    void insertEntry(const std::string &word,
                     const LineEntry &entry, bool sensitive);
    void resizeTable(std::vector<std::list<HashNode>> &table);

    // ID management
    int getFileID(const std::string &filePath);
    size_t getLineID(const std::string &lineText);

    // String processing
    std::string sanitizeWord(const std::string &word) const;
    std::string toLower(const std::string &word) const;
};

#endif