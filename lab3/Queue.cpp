/*
 *      Queue.cpp
 *      CS15 Lab 04: Circular Buggers
 *
 *      2016-09-16 Created by Yennie Jun
 *      2016-09-20 Modified by Mark A. Sheldon
 *                 Added documentation
 *      2020-01-31 Modified by Juliana Vega
 *                 Removed "sequence" wording
 *      2024-02-07 Modified by Skylar Gilfeather
 *                 Renamed CircularBuffer to buffer
 *                 Updated function contracts, comments, and header
 *      2024-09-25 Modified by Kathy Quintanilla
 *                 Updated initial capacity constructor
 *                 Updated function contracts and header
 * 
 *      This file contains an implementation of the Queue class.
 */

#include "Queue.h"
#include <iostream>
#include <string>

using namespace std;

/*  Default constructor
 *  Purpose:    Construct an instance of a Queue.
 *  Parameters: None
 *  Return:     None
 *  Notes:      Nothing necessary. Data member construction runs automatically.
 */
Queue::Queue() 
{
    /* nothing to do: the buffer default constructor is called automatically */
}

/*  Destructor
 *  Purpose:    Deallocate all allocated memory for Queue class.
 *  Parameters: None
 *  Return:     None
 */
Queue::~Queue() 
{
    /* nothing to do: the buffer destructor is called automatically */
}

/*  dequeue()
 *  Purpose:    Remove the first element in the queue and return it.
 *  Parameters: None
 *  Return:     None
 *  Notes:      ElementType is defined in .h file.
 */
ElementType Queue::dequeue()
{
    /* TODO */
}

/*  enqueue()
 *  Purpose:    Add a new element to the back of the queue.
 *  Parameters: element - the element to add.
 *  Return:     None
 *  Notes:      ElementType is defined in .h file.
 */
void Queue::enqueue(ElementType element)
{
    /* TODO */
}

/*  toString()
 *  Purpose:    Return the contents of the queue as a string.
 *  Parameters: None
 *  Return:     None
 */
std::string Queue::toString() const {
    return buffer.toString();
}
