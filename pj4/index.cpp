/*
 *  index.cpp
 *  Jack Craig, Clark Morris
 *  04/24/2025
 *
 *  CS 15 Project 4: Gerp
 *  Implementation of hash table based indexing system for Gerp.
 *  Handles case-sensitive and case-insensitive word indexing,
 *  file/line tracking, and efficient search operations.
 *  Uses separate chaining for collision resolution.
 *
 */

#include "index.h"
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <sys/mman.h>

/*
 * name:      Index constructor
 * purpose:   Initialize hash tables with prime number capacities
 * arguments: None
 * returns:   None
 * effects:   Sets up empty hash tables for case-sensitive/insensitive indexing
 *            and file/line tracking with initial sizes
 */
Index::Index() : capacity(10007), size(0)
{
    caseSensitiveTable.resize(capacity);
    caseInsensitiveTable.resize(capacity);
    fileTable.resize(1009); // Prime numbers for better distribution
    lineTable.resize(1009);
}

/*
 * name:      hashFunction
 * purpose:   Compute hash value for a given key using djb2 algorithm
 * arguments: key - string to hash, tableSize - size of target hash table
 * returns:   Computed hash value within table bounds
 * effects:   Processes each character of input string
 */
size_t Index::hashFunction(const std::string &key, size_t tableSize) const
{
    if (key.empty())
        return 0; // Add guard clause

    size_t hash = 5381;
    for (char c : key)
    {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % tableSize;
}

/*
 * name:      getFileID
 * purpose:   Get or create unique ID for a file path
 * arguments: filePath - path to file
 * returns:   Unique integer ID for the file
 * effects:   May add new entry to fileTable and filePaths
 */
int Index::getFileID(const std::string &filePath)
{
    size_t index = hashFunction(filePath, fileTable.size());
    for (const auto &entry : fileTable[index])
    {
        if (entry.path == filePath)
        {
            return entry.id;
        }
    }

    int newID = filePaths.size();
    filePaths.push_back(filePath);
    fileTable[index].push_back({filePath, newID});
    return newID;
}

/*
 * name:      getLineID
 * purpose:   Get or create unique ID for a line of text
 * arguments: lineText - text content of line
 * returns:   Unique size_t ID for the line
 * effects:   May add new entry to lineTable and lineTexts
 */
size_t Index::getLineID(const std::string &lineText)
{
    size_t index = hashFunction(lineText, lineTable.size());
    for (const auto &entry : lineTable[index])
    {
        if (entry.text == lineText)
        {
            return entry.id;
        }
    }

    size_t newID = lineTexts.size();
    lineTexts.push_back(lineText);
    lineTable[index].push_back({lineText, newID});
    return newID;
}

/*
 * name:      addLine
 * purpose:   Index all words in a line of text from a file
 * arguments: filePath - source file, lineNum - line number,
 *            lineText - content of line
 * returns:   None
 * effects:   Updates both case-sensitive and case-insensitive indices
 */
void Index::addLine(const std::string &filePath, int lineNum,
                    const std::string &lineText)
{
    const int fileID = getFileID(filePath);
    const size_t lineID = getLineID(lineText);
    const LineEntry entry{fileID, lineNum, lineID};

    std::istringstream iss(lineText);
    std::string word;

    while (iss >> word)
    {
        std::string sanitized = sanitizeWord(word);
        if (not(sanitized.empty()))
        {
            // Insert case-sensitive version (exact sanitized word)
            insertEntry(sanitized, entry, /*sensitive=*/true);

            // Insert case-insensitive version (lowercase)
            std::string lower = toLower(sanitized);
            insertEntry(lower, entry, /*sensitive=*/false);
        }
    }
}

/*
 * name:      insertEntry
 * purpose:   Add word occurrence to appropriate hash table
 * arguments: word - term to index, entry - line location info,
 *            sensitive - which table to update
 * returns:   None
 * effects:   May resize table if load factor exceeds threshold
 */
void Index::insertEntry(const std::string &word,
                        const LineEntry &entry, bool sensitive)
{
    auto &table = sensitive ? caseSensitiveTable : caseInsensitiveTable;
    size_t index = hashFunction(word, table.size());

    // Check if the word already exists in the bucket
    for (auto &node : table[index])
    {
        if (node.key == word)
        {
            // Add entry only if it's a new line (unique lineID)
            if (node.entries.empty() or
                not(node.entries.back().lineID == entry.lineID))
            {
                node.entries.push_back(entry);
            }
            return;
        }
    }

    // Add new entry
    table[index].push_front({word, {entry}});
    size++;

    // Resize if load factor exceeds threshold
    if (static_cast<double>(size) / capacity > MAX_LOAD_FACTOR)
    {
        resizeTable(table);
    }
}

/*
 * name:      resizeTable
 * purpose:   Expand hash table when load factor gets too high
 * arguments: table - reference to table needing resizing
 * returns:   None
 * effects:   Doubles capacity and rehashes all entries
 */
void Index::resizeTable(std::vector<std::list<HashNode>> &table)
{
    size_t newCapacity = capacity * 2 + 1;
    std::vector<std::list<HashNode>> newTable(newCapacity);

    for (auto &chain : table)
    {
        for (auto &node : chain)
        {
            size_t newIndex = hashFunction(node.key, newCapacity);
            newTable[newIndex].push_back(node); // Rehash all nodes
        }
    }

    table = std::move(newTable);
    capacity = newCapacity;
}

/*
 * name:      searchCaseSensitive
 * purpose:   Find exact matches for query in case-sensitive index
 * arguments: query - search term
 * returns:   Vector of matching LineEntry objects
 * effects:   Returns empty vector if no matches found
 */
std::vector<LineEntry> Index::searchCaseSensitive(const std::string &query)
    const
{
    std::string key = query; // Sanitize the query
    if (key.empty())
        return {};

    size_t index = hashFunction(key, caseSensitiveTable.size());
    for (auto &node : caseSensitiveTable[index])
    {
        if (node.key == key)
        {
            return node.entries;
        }
    }
    return {};
}

/*
 * name:      searchCaseInsensitive
 * purpose:   Find matches for query in case-insensitive index
 * arguments: query - search term
 * returns:   Vector of matching LineEntry objects
 * effects:   Converts query to lowercase before searching
 */
std::vector<LineEntry> Index::searchCaseInsensitive(const std::string &query)
    const
{
    std::string key = toLower(query);
    if (key.empty())
    {
        return {};
    }
    size_t index = hashFunction(key, caseInsensitiveTable.size());
    for (auto &node : caseInsensitiveTable[index])
    {
        if (node.key == key)
        {
            return node.entries;
        }
    }
    return {};
}

/*
 * name:      sanitizeWord
 * purpose:   Remove non-alphanumeric characters from word edges
 * arguments: word - string to sanitize
 * returns:   Sanitized word or empty string if no alphanumerics
 * effects:   Preserves apostrophes within word
 */
std::string Index::sanitizeWord(const std::string &word) const
{
    size_t first = 0, last = word.size() - 1;
    // Trim leading non-alphanumeric
    while (first <= last and
           not(std::isalnum(static_cast<unsigned char>(word[first]))))
        first++;
    // Trim trailing non-alphanumeric
    while (last >= first and
           not(std::isalnum(static_cast<unsigned char>(word[last]))))
        last--;
    return (first > last) ? "" : word.substr(first, last - first + 1);
}

/*
 * name:      toLower
 * purpose:   Convert string to lowercase
 * arguments: word - string to convert
 * returns:   Lowercase version of input string
 * effects:   Handles each character individually
 */
std::string Index::toLower(const std::string &word) const
{
    std::string lower;
    lower.reserve(word.size());
    for (char c : word)
    {
        lower += static_cast<char>(std::tolower(
            static_cast<unsigned char>(c)));
    }
    return lower;
}

/*
 * name:      getLine
 * purpose:   Retrieve original line text by ID
 * arguments: lineID - unique identifier for line
 * returns:   Reference to stored line text
 * throws:    out_of_range if invalid lineID
 */
const std::string &Index::getLine(size_t lineID) const
{
    if (lineID >= lineTexts.size())
    {
        throw std::out_of_range("Invalid line ID");
    }
    return lineTexts[lineID];
}

/*
 * name:      getFile
 * purpose:   Retrieve original file path by ID
 * arguments: fileID - unique identifier for file
 * returns:   Reference to stored file path
 * throws:    out_of_range if invalid fileID
 */
const std::string &Index::getFile(int fileID) const
{
    if (fileID < 0 or fileID >= static_cast<int>(filePaths.size()))
    {
        throw std::out_of_range("Invalid file ID");
    }
    return filePaths[fileID];
}