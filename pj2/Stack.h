#ifndef STACK_H
#define STACK_H

#include "Datum.h"
#include <vector>
#include <stdexcept>

class Stack
{
private:
    std::vector<Datum> stack;

public:
    void push(const Datum &d);

    Datum pop();

    bool isEmpty() const;

    Datum top() const;

    void clear();

    size_t size() const;
};

#endif // STACK_H