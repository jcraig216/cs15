/*
 *      Queue.h
 *      CS15 Lab 04: Circular Buggers
 *
 *      2016-09-16 Created by Yennie Jun
 *      2016-09-20 Modified by Mark A. Sheldon
 *                 Added documentation, include guards
 *                 Removed unnecessary includes
 *      2020-01-31 Modified by Juliana Vega
 *                 Removed "sequence" wording
 *      2024-02-07 Modified by Skylar Gilfeather
 *                 Renamed CircularBuffer to buffer
 *                 Updated header
 * 
 *      A class that represents a queue of elements.
 *      The type ElementType is presumed to be defined before this
 *      file is included.
 *
 */

#ifndef QUEUE_H
#define QUEUE_H

#include "CircularBuffer.h"
#include "ElementType.h"
#include <string>

class Queue {
public:
    Queue();
    ~Queue();

    ElementType dequeue();
    void        enqueue(ElementType element);

    std::string toString() const;

private:
    CircularBuffer buffer;
};

#endif
