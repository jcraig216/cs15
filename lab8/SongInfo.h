/*
 * CS15 Lab 10: Hash Tables
 * 
 * SongInfo.h
 * This struct represents the values for the hash tables in 
 * FunkeyChainingTable and FunkeyLinearTable. The song names 
 * (strings) are keys and the values are structs containing the 
 * chart position and beats per minute (bpm).
 * 
 */

/* Adding include guard for lab to avoid 
   multiple definition with both tables */
#ifndef SONG_INFO_H 
#define SONG_INFO_H

struct SongInfo {
        int chartPosition;
        int bpm;

        /* Constructors for struct */
        SongInfo() 
        {
                chartPosition = bpm = -1;
        }

        SongInfo(int position, int tempo)
        {
                chartPosition = position;
                bpm           = tempo;
        }
};

#endif    /* SONG_INFO_H */