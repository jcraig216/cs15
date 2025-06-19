/*
 * FunkeyLinearTable.cpp --- compare two different hash functions. This table
 * uses linear probing to handle collisions
 *
 * Based on a previous lab by Ben Hescott, I think.
 *
 * Mark A. Sheldon, Tufts University, Spring 2017
 * Edited by Kathy Quintanilla, Novemeber 2024
 *      added function contracts + fixed style
 * Edited by Kathy Quintanilla, March 2025
 *      switched arraylist and linked list table implementations
 *      to std::vector and std::list ones + separated hash tables
 *      into different classes (inspired by Hameedah Lawal's implementation)
 */

#include <iostream>
#include <stdio.h>
#include <functional>

#include "FunkeyLinearTable.h"

using namespace std;

/*
 * Name:      FunkeyLinearTable()
 * Purpose:   Initialize the member variables of the FunkeyLinearTable class
 * Arguments: None
 * Returns:   None
 * Effects:   Constructor allocates and initializes two empty tables of the
 *            INITIAL_TABLE_SIZE
 */
FunkeyLinearTable::FunkeyLinearTable()
{
        currentTableSize = INITIAL_TABLE_SIZE;
        numItemsInTable = 0;

        /* std::vectors and std::lists start off empty,
           so resize() will allocate the necessary space */
        linearTable.resize(currentTableSize);

        for (int i = 0; i < currentTableSize; i++)
        {
                linearTable.at(i).isEmpty = true;
        }
}

/*
 * Name:      ~FunkeyLinearTable()
 * Purpose:   Recycle all memory used in class
 * Arguments: None
 * Returns:   None
 * Effects:   Recycles all memory
 */
FunkeyLinearTable::~FunkeyLinearTable()
{
}

/*
 * Name:      good_hash_function(KeyType key)
 * Purpose:   Gets the index of where to insert a value in the hash table from a
 *            given key
 * Arguments: KeyType key that the index value should be hashed from
 * Returns:   size_t of the index of where to insert
 */
static size_t good_hash_function(KeyType key)
{
        return std::hash<KeyType>{}(key);
}

/*
 * Name:      bad_hash_function(KeyType key)
 * Purpose:   Gets the index of where to insert a value in the hash table from a
 *            given key
 * Arguments: KeyType key that the index value should be hashed from
 * Returns:   size_t of the index of where to insert
 */
static size_t bad_hash_function(KeyType key)
{
        return key.length();
}

/*
 * Name:      hashValue(KeyType key, HashFunction hashFunction)
 * Purpose:   Hashes a given key with the given hash function
 * Arguments: KeyType key to be hashed and a HashFunction hashFunction that is
 *            the HashFunction we should use to hash the key
 * Returns:   size_t of the index of where to insert
 */
static size_t hashValue(KeyType key, HashFunction hashFunction)
{
        if (hashFunction == BAD_HASH_FUNCTION)
        {
                return bad_hash_function(key);
        }
        else
        {
                return good_hash_function(key);
        }
}

/*
 * Name:      insertProbing(KeyType key, ValueType value,
 *                          HashFunction hashFunction)
 * Purpose:   Insert a given value into a linear probing hash table
 * Arguments: The KeyType of the value to be hashed, the ValueType of the key
 *            to be inserted into the table, and the HashFunction to hash the
 *            key
 * Returns:   int of the number of collisions that happened before finding a
 *            spot
 */
int FunkeyLinearTable::insertProbing(KeyType key, ValueType value,
                                     HashFunction hashFunction)
{
        if (numItemsInTable >= currentTableSize / 2)
        {
                expand(hashFunction);
        }

        int attempt = 0;
        size_t index;

        while (true)
        {
                index = (hashValue(key, hashFunction) + attempt) % currentTableSize;

                if (linearTable[index].isEmpty)
                {
                        linearTable[index].key = key; // Store exact key
                        linearTable[index].value = value;
                        linearTable[index].isEmpty = false;
                        numItemsInTable++;
                        return attempt;
                }
                else if (linearTable[index].key == key)
                {
                        linearTable[index].value = value; // Update existing
                        return attempt;
                }
                attempt++;
        }
}
/*
 * Name:      expand(HashFunction hashFunction)
 * Purpose:   Expand `linearTable`
 * Arguments: The HashFunction to use to rehash the index of the values in the
 *            table
 * Returns:   None
 * Effects:   Expands `linearTable` and rehashes each value before moving the
 *            values over to the new table.
 */
void FunkeyLinearTable::expand(HashFunction hashFunction)
{
        int oldTableSize = currentTableSize;
        currentTableSize = oldTableSize * 2 + 1;

        vector<TableEntry> oldTable = linearTable;
        linearTable.clear();
        linearTable.resize(currentTableSize);

        for (int i = 0; i < currentTableSize; i++)
        {
                linearTable[i].isEmpty = true;
        }
        numItemsInTable = 0;

        for (int i = 0; i < oldTableSize; i++)
        {
                if (!oldTable[i].isEmpty)
                {
                        // Reinsert with original key
                        insertProbing(oldTable[i].key, oldTable[i].value, hashFunction);
                }
        }
}

/*
 * Name:      printTableEntry(TableEntry entry)
 * Purpose:   Prints a TableEntry's information
 * Arguments: The TableEntry to be printed
 * Returns:   None
 */
void FunkeyLinearTable::printTableEntry(TableEntry entry)
{
        if (entry.isEmpty)
        {
                cout << "empty";
        }
        else
        {
                cout << "key:  "
                     << entry.key
                     << "; value:  {"
                     << entry.value.chartPosition
                     << ", "
                     << entry.value.bpm
                     << "}";
        }
}

/*
 * Name:      print()
 * Purpose:   Prints both hash tables
 * Arguments: None
 * Returns:   None
 */
void FunkeyLinearTable::print()
{
        cout << "Linear table" << endl;

        for (int i = 0; i < currentTableSize; ++i)
        {
                cout << i << ":  ";
                printTableEntry(linearTable[i]);
                cout << endl;
        }
}