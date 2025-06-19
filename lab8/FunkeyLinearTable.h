/*
 * CS15 Lab 10: Hash Tables
 * 
 * FunkeyLinearTable.h
 * This hash table maps song titles (strings) to information about
 * that song:  the rank of the song on the pop charts and the tempo of
 * the song in beats per minute (bpm).  
 *
 * For the hash table, the song titles (strings) are keys and the
 * values are structs containing the chart position and the tempo.
 *
 * In a proper polymorphic (templated) hash table, this struct would 
 * be the value type and would be defined by the client independently
 * of the table. The key type would be string.
 * 
 * Based on a previous hash table lab I think created by Ben Hescott.
 *
 * (c) Mark A. Sheldon, Tufts University, Spring 2017
 */


#ifndef FUNKEY_LINEAR_TABLE_H
#define FUNKEY_LINEAR_TABLE_H

#include <string>
#include <vector>
#include "SongInfo.h"
#include "HashFunction.h"

/*
 * The following type definitions allow us to abstract the FunkeyTable
 * class over the details of the key and value type.
 * In the implementation, the only code that depends on knowing the
 * types is the print function, which could be removed after
 * debugging. Then we could make this a template!
 */
typedef std::string   KeyType;
typedef SongInfo      ValueType;

class FunkeyLinearTable
{
public:
	FunkeyLinearTable();
	~FunkeyLinearTable();

	int insertProbing (KeyType key, ValueType value,
                           HashFunction hashFunction);
	void print();

private:
        /*
         * Used by the table for linear probing
         */
        struct TableEntry {
                bool      isEmpty;
                KeyType   key;
                ValueType value;
        };

        /*
        * Here is the table.
        * It's an std::vector initialized with a size = 0.
        * A linear probing table is a vector of TableEntries.
        */ 
       static const int INITIAL_TABLE_SIZE = 23;
       int currentTableSize;
       int numItemsInTable;

       std::vector<TableEntry> linearTable;

        /*
         * Private helper functions definitions
         */
	void  expand(HashFunction hashFunction);
        void  printTableEntry(TableEntry entry);
};
#endif	/* FUNKEY_LINEAR_TABLE_H */
