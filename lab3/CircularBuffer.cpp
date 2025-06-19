/*
 *      CircularBuffer.cpp
 *      CS15 Lab 04: Circular Buggers
 *
 *      2016-09-16 Created by Yennie Jun
 *      2016-09-20 Documentation added by Mark A. Sheldon, Tufts University
 *      2019-08-01 Modified by Alice Dempsey
 *      2020-01-31 Modified by Juliana Vega
 *                 Removed "sequence" wording
 *      2020-09-21 Modified by Matt Champlin
 *                 Added prevIndex function that wraps around.
 *                 Note: "front" always points to first element. "back" always
 *                       points to the next available empty slot.
 *      2022-02-09 Modified by Matt Russell
 *                 printBuffer->toString
 *      2024-02-07 Modified by Skylar Gilfeather
 *                 Updated CircularBuffer implementation for debugging focus
 *                 Updated header
 *      2024-02-11 Modified by Skylar Gilfeather, Luke Ito, Amelia Cook
 *                 Adding bugs!
 *
 *      This file contains an implementation of the CircularBuffer class.
 */

#include "CircularBuffer.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace std;

/*  CircularBuffer()
 *  Purpose:    Default constructor
 *  Parameters: None
 *  Returns:    None
 *  Notes:      INIT_CAPACITY is set to 5 in .h file
 */
CircularBuffer::CircularBuffer()
{
    capacity = INIT_CAPACITY;
    array = new ElementType[capacity];
    currentSize = 0;
    front = 0;
    back = 0;
}

/*  CircularBuffer(int initialCapacity)
 *  Purpose:    Overloaded Constructor for a buffer with a hint for an initial
 *              capacity.
 *  Parameters: initialCapacity - Capacity user wants buffer to be
 *  Returns:    None
 */
CircularBuffer::CircularBuffer(int initialCapacity)
{
    capacity = initialCapacity;
    array = new ElementType[capacity];
    currentSize = 0;
    front = 0;
    back = 0;
}

/*  Destructor
 *  Purpose:    Recycles the dynamically allocated array containing
 *              the data.
 *  Parameters: None
 *  Returns:    None
 */
CircularBuffer::~CircularBuffer()
{
    delete[] array;
}

/*  nextIndex()
 *  Purpose:    Gets the next index in the buffer
 *  Parameters: int - the index to increment.
 *  Returns:    int - the index of the next element in the buffer.
 *  Notes:      Wraps around!
 */
int CircularBuffer::nextIndex(int index) const
{
    return (index + 1) % capacity;
}

/*  prevIndex()
 *  Purpose:    Gets the previous index in the buffer.
 *  Parameters: int - the index to decrement.
 *  Returns:    int - the index of the previous element in the buffer.
 *  Notes:      Wraps around!
 */
int CircularBuffer::prevIndex(int index) const
{
    /* the prev index before 0 should be the last index in the buffer */
    if (index - 1 < 0)
    {
        return capacity - 1;
    }
    else
    {
        return (index - 1) % capacity;
    }
}

/*  addAtBack()
 *  Purpose:    Add given element to the back of the buffer
 *  Parameters: elem - object to add to the buffer
 *  Return:     None
 *  Notes:      ElementType is defined in ElementType.h
 */
void CircularBuffer::addAtBack(ElementType elem)
{
    if (currentSize == capacity)
    {
        expand();
    }

    array[back] = elem;
    currentSize++;
    back = nextIndex(back);
}

/*  addAtFront()
 *  Purpose:    Add given element to the front of the list
 *  Parameters: elem - object to add to the buffer
 *  Return:     None
 *  Notes:      ElementType is defined in ElementType.h
 */
void CircularBuffer::addAtFront(ElementType elem)
{
    if (currentSize == capacity)
    {
        expand();
    }
    front = prevIndex(front);
    array[front] = elem;
    currentSize++;
}

/*  removeFromBack()
 *  Purpose:    Remove the element at the back of the list and return it.
 *  Parameters: None
 *  Return:     ElementType - the element at the back of the list.
 */
ElementType CircularBuffer::removeFromBack()
{
    ElementType prevBackElem = array[back];
    if (currentSize == 1)
    {
        front = back = 0;
    }
    else
    {
        back = prevIndex(back);
    }
    currentSize--;
    return prevBackElem;
}

/*  removeFromFront()
 *  Purpose:    Remove the element at the front of the list and return it.
 *  Parameters: None
 *  Returns:    ElementType - the element at the front of the list.
 */
ElementType CircularBuffer::removeFromFront()
{
    ElementType prevFrontElem = array[front];
    front = nextIndex(front);
    currentSize--;
    return prevFrontElem;
}

/*  expand()
 *  Purpose:    Expand the capacity of the array by a factor of 2 + 2.
 *  Parameters: None
 *  Return:     None
 *  Notes:      This one is tricky! It will be different than the expand you
 *              are used to writing. Think about how to handle wrapping. Also
 *              think about how you are going to ensure that "front" and "back"
 *              maintain their meaning once you've copied the items over.
 */
void CircularBuffer::expand()
{
    int currIndex = front;
    capacity = (capacity * 2) + 2;
    ElementType *new_array = new ElementType[capacity];

    /* copy elements from array into new_array, letting front = 0 */
    for (int i = 0; i < currentSize; i++)
    {
        new_array[i] = array[currIndex];
        currIndex = nextIndex(currIndex);
    }

    delete[] array;
    array = new_array;

    front = 0;
    back = currentSize;
}

/*  size()
 *  Purpose:    Returns the current size of the buffer.
 *  Parameters: None
 *  Return:     int - the current size of the list.
 */
int CircularBuffer::size()
{
    return currentSize;
}

/*  toString()
 *  Purpose:    Returns contents of the buffer as a string.
 *  Parameters: None
 *  Return:     string - a string representation of the buffer.
 */
std::string CircularBuffer::toString() const
{
    std::stringstream ss;
    int currIndex = front;

    ss << "[ ";
    for (int i = 0; i < currentSize; i++)
    {
        ss << "'" << array[currIndex];
        if (i == currentSize - 1)
        {
            ss << "' ";
        }
        else
        {
            ss << "', ";
        }
        currIndex = nextIndex(currIndex);
    }
    ss << "]";
    return ss.str();
}