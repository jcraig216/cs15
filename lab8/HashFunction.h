/*
 * CS15 Lab 10: Hash Tables
 * 
 * HashFunction.h
 * This enum allows us to use variables of type HashFunction, whose values 
 * are either GOOD_HASH_FUNCTION or BAD_HASH_FUNCTION. This is simply a 
 * convenience to make our code more readable.
 * 
 * Would be better to keep the enum within the hash 
 * table classes, but we are only separating it for the lab
*/

#ifndef HASH_FUNCTION_H 
#define HASH_FUNCTION_H

enum HashFunction {BAD_HASH_FUNCTION, GOOD_HASH_FUNCTION};

#endif    /* HASH_FUNCTION_H */