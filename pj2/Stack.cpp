#include "Stack.h"

// Push a Datum onto the stack
void Stack::push(const Datum &d)
{
    stack.push_back(d);
}

// Pop a Datum from the stack
Datum Stack::pop()
{
    if (stack.empty())
    {
        throw std::runtime_error("Error: empty stack");
    }
    Datum d = stack.back();
    stack.pop_back();
    return d;
}

// Check if the stack is empty
bool Stack::isEmpty() const
{
    return stack.empty();
}

// Get the top element without popping
Datum Stack::top() const
{
    if (stack.empty())
    {
        throw std::runtime_error("Error: empty stack");
    }
    return stack.back();
}

// Clear the stack
void Stack::clear()
{
    stack.clear();
}

// Get the size of the stack
size_t Stack::size() const
{
    return stack.size();
}