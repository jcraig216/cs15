/*
 *      Stack.h
 *      CS15 Lab 04: Circular Buggers
 *
 *      2016-09-16 Created by Yennie Jun
 *      2016-09-20 Modified by Mark A. Sheldon
 *                 Added documentation and include guards
 *      2020-01-31 Modified by Juliana Vega
 *                 Removed "sequence" wording
 *      2024-02-07 Modified by Skylar Gileather
 *                 Renamed CircularBuffer to buffer
 *                 Updated header
 *      2024-09-25 Modified by Kathy Quintanilla
 *                 Updated header
 * 
 *      A class that represents a stack of elements.
 *      The type ElementType is presumed to be defined before this
 *      file is included.
 * 
 */
#ifndef STACK_H
#define STACK_H

#include "CircularBuffer.h"
#include "ElementType.h"

class Stack {
public:
    Stack();
    ~Stack();

    ElementType pop();
    void        push(ElementType element);

    std::string toString() const;

private:
    CircularBuffer buffer;
};

#endif
