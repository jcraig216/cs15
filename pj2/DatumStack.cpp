/*
 *  DatumStack.cpp
 *  Jack Craig
 *  02/26/2025
 *
 *  CS 15 Project 2: CalcYouLater
 *  Implementation of the Stack class.
 *
 */

#include "DatumStack.h"

DatumStack::DatumStack() : stack() {}

DatumStack::DatumStack(Datum *data, int size)
{
    for (int i = 0; i < size; i++)
    {
        stack.push_back(data[i]);
    }
}

/*
 * name:      push()
 * purpose:   Push a Datum onto the stack.
 * arguments: A Datum object to push.
 * returns:   None.
 * effects:   Adds the Datum to the top of the stack.
 */
void DatumStack::push(const Datum &d)
{
    stack.push_back(d);
}

/*
 * name:      pop()
 * purpose:   Pop a Datum from the stack.
 * arguments: None.
 * returns:   The Datum at the top of the stack.
 * effects:   Removes the Datum from the stack.
 */
Datum DatumStack::pop()
{
    if (stack.empty())
    {
        throw std::runtime_error("empty_stack");
    }
    Datum d = stack.back();
    stack.pop_back();
    return d;
}

/*
 * name:      isEmpty()
 * purpose:   Check if the stack is empty.
 * arguments: None.
 * returns:   True if the stack is empty, false otherwise.
 * effects:   None.
 */
bool DatumStack::isEmpty() const
{
    return stack.empty();
}

/*
 * name:      top()
 * purpose:   Get the top element without popping.
 * arguments: None.
 * returns:   The Datum at the top of the stack.
 * effects:   None.
 */
const Datum &DatumStack::top() const
{
    if (stack.empty())
    {
        throw std::runtime_error("empty_stack");
    }
    return stack.back();
}

/*
 * name:      clear()
 * purpose:   Clear the stack.
 * arguments: None.
 * returns:   None.
 * effects:   Removes all elements from the stack.
 */
void DatumStack::clear()
{
    stack.clear();
}

/*
 * name:      size()
 * purpose:   Get the size of the stack.
 * arguments: None.
 * returns:   The number of elements in the stack.
 * effects:   None.
 */
size_t DatumStack::size() const
{
    return stack.size();
}
