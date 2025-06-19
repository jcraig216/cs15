/*
 *      CircularBuffer.h
 *      CS15 Lab 04: Circular Buggers
 *
 *      A class that represents an ordered sequence of elements. This
 *      one is for ElementType, which is defined in ElementType.h.
 *
 *      2016-09-16 Created by Yennie Jun
 *      2016-09-20 Modified by Mark A. Sheldon, Tufts University
 *                 Added documentation and nextIndex() function.
 *      2020-01-31 Modified by Juliana Vega
 *                 Removed "sequence" wording
 *      2022-02-09 Modified by Matt Russell
 *                 printBuffer->toString
 *      2024-02-07 Modified by Skylar Gilfeather
 *                 Updated header
 *      2024-09-26 Modified by Kathy Quintanilla
 *                 Updated header
 */

#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include "ElementType.h"

class CircularBuffer
{
public:
    CircularBuffer();
    CircularBuffer(int givenCapacity);
    ~CircularBuffer();

    void addAtBack(ElementType elem);
    void addAtFront(ElementType elem);
    int size();
    ElementType removeFromBack();
    ElementType removeFromFront();

    std::string toString() const;

private:
    static const int INIT_CAPACITY = 10;

    ElementType *array;
    int currentSize;
    int capacity;
    int front;
    int back;

    int prevIndex(int index) const;
    int nextIndex(int index) const;
    void expand();
};

#endif
