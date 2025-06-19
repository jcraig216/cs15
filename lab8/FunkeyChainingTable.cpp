/*
 * FunkeyChainingTable.cpp --- compare two different hash
 * functions. This table uses chaining to handle collisions
 *
 * Based on a previous lab by Ben Hescott, I think.
 *
 * Mark A. Sheldon, Tufts University, Spring 2017
 * Edited by Kathy Quintanilla, November 2024
 *      added function contracts + fixed style
 * Edited by Hameedah Lawal, November 2024
 *      switched arraylist and linked list table implementations
 *      to std::vector and std::list ones + separated hash tables
 *      into different classes
 */

#include <iostream>
#include <stdio.h>
#include <functional>

#include "FunkeyChainingTable.h"

using namespace std;

/*
 * Name:      FunkeyChainingTable()
 * Purpose:   Initialize the member variables of the FunkeyChainingTable class
 * Arguments: None
 * Returns:   None
 * Effects:   Constructor allocates and initializes two empty tables of the
 *            INITIAL_TABLE_SIZE
 */
FunkeyChainingTable::FunkeyChainingTable()
{
        currentTableSize = INITIAL_TABLE_SIZE;
        numItemsInTable = 0;

        /* std::vectors and std::lists start off empty,
        so resize() will allocate the necessary space */
        chainedTable.resize(currentTableSize);

        for (int i = 0; i < currentTableSize; i++)
        {
                /* fill each of chainedTable's inner chains with an empty list */
                std::list<ChainNode> emptyChain;
                chainedTable.at(i) = emptyChain;
        }
}

/*
 * Name:      ~FunkeyChainingTable()
 * Purpose:   Recycle all memory used in class
 * Arguments: None
 * Returns:   None
 * Effects:   Recycles all memory
 */
FunkeyChainingTable::~FunkeyChainingTable()
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
 * Name:      insertChaining(KeyType key, ValueType value,
 *                           HashFunction hashFunction)
 * Purpose:   Insert a given value into a chaining hash table
 * Arguments: The KeyType of the value to be hashed, the ValueType of the key
 *            to be inserted into the table, and the HashFunction to hash the
 *            key
 * Returns:   int of the number of items in the index before insertion
 */
int FunkeyChainingTable::insertChaining(KeyType key, ValueType value,
                                        HashFunction hashFunction)
{
        if (numItemsInTable >= currentTableSize)
        {
                expand(hashFunction);
        }

        size_t index = hashValue(key, hashFunction) % currentTableSize;
        std::list<ChainNode> &chain = chainedTable[index];
        int itemsInChain = chain.size();

        // First check if key exists
        for (auto &node : chain)
        {
                if (node.key == key)
                {
                        node.value = value; // Update existing
                        return itemsInChain;
                }
        }

        // Insert new node at front
        ChainNode newNode;
        newNode.key = key; // Store exact key
        newNode.value = value;
        chain.push_front(newNode);
        numItemsInTable++;

        return itemsInChain;
}

/*
 * Name:      expand(HashFunction hashFunction)
 * Purpose:   Expand `chainedTable`
 * Arguments: The HashFunction to use to rehash the index of the values in the
 *            table
 * Returns:   None
 * Effects:   Expands `chainedTable` and rehashes each value before moving the
 *            values over to the new table.
 */
void FunkeyChainingTable::expand(HashFunction hashFunction)
{
        int oldTableSize = currentTableSize;
        currentTableSize = oldTableSize * 2 + 1;

        vector<std::list<ChainNode>> oldTable = chainedTable;
        chainedTable.clear();
        chainedTable.resize(currentTableSize);
        numItemsInTable = 0;

        for (int i = 0; i < oldTableSize; i++)
        {
                for (auto &node : oldTable[i])
                {
                        // Reinsert with original key
                        insertChaining(node.key, node.value, hashFunction);
                }
        }
}

/*
 * Name:      printChainNode(ChainNode *node)
 * Purpose:   Prints a given ChainNode's information
 * Arguments: The ChainNode to be printed
 * Returns:   None
 */
void FunkeyChainingTable::printChainNode(ChainNode node)
{
        cout << "key:  " << node.key
             << "; value:  {" << node.value.chartPosition
             << ", " << node.value.bpm << "}";
}

/*
 * Name:      print()
 * Purpose:   Prints the hash table
 * Arguments: None
 * Returns:   None
 */
void FunkeyChainingTable::print()
{
        cout << endl
             << "Chained table" << endl;

        for (int i = 0; i < currentTableSize; ++i)
        {
                std::list<ChainNode> currChain = chainedTable.at(i);
                int currChainSize = currChain.size();
                cout << i << ":  [ ";

                /* use iterator to loop through list */
                std::list<ChainNode>::iterator currNode = currChain.begin();
                while (currNode != currChain.end())
                {
                        printChainNode(*currNode);

                        /* don't add a comma for the last node */
                        if (currChainSize > 1)
                        {
                                cout << ", ";
                        }
                        currChainSize--;
                        currNode++;
                }
                cout << "]" << endl;
        }
        cout << endl;
}