/*
 *      Stack.cpp
 *      CS15 Lab 04: Circular Buggers
 *
 *      2016-09-16 Created by Yennie Jun
 *      2016-09-20 Modified by Mark A. Sheldon
 *                 Added documentation
 *      2020-01-31 Modified by Juliana Vega
 *                 Removed "sequence" wording
 *      2024-02-07 Modified by Skylar Gilfeather
 *                 Removed more "sequence" wording
 *                 Renamed CircularBuffer to buffer
 *                 Updated function contracts, comments, and header
 *      2024-09-25 Modified by Kathy Quintanilla
 *                 Updated initial capacity constructor
 *                 Updated function contracts and header
 *
 *      This file contains an implementation of the Stack class.
 *
 */

#include "Stack.h"
#include <iostream>

using namespace std;

/*  Default constructor
 *  Purpose:    Construct an instance of a Stack.
 *  Parameters: None
 *  Return:     None
 *  Notes:      Nothing necessary. Data member construction runs automatically.
 */
Stack::Stack()
{
    /* nothing to do: the buffer default constructor is called automatically */
}

/*  Destructor
 *  Purpose:    Deallocate all allocated memory for Stack class.
 *  Parameters: None
 *  Return:     None
 */
Stack::~Stack()
{
    /* nothing to do: the buffer destructor is called automatically */
}

/*  pop()
 *  Purpose:    Remove top element from the stack and return it.
 *  Parameters: None
 *  Return:     None
 */
ElementType Stack::pop()
{
    /* TODO */
    return buffer.removeFromFront();
}

/*  push()
 *  Purpose:    Add given element to the top of the stack.
 *  Parameters: element - the element to add.
 *  Return:     None
 *  Notes:      ElementType is defined in .h file.
 */
void Stack::push(ElementType element)
{
    /* TODO */
    buffer.addAtFront(element);
}

/*  toString()
 *  Purpose:    Return the contents of the stack as a string.
 *  Parameters: None
 *  Return:     None
 */
std::string Stack::toString() const
{
    return buffer.toString();
}
