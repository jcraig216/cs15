/*
 *  DatumStack.h
 *  Jack Craig
 *  02/26/2025
 *
 *  CS 15 Project 2: CalcYouLater
 *  Manages a stack of Datum objects.
 *
 */

#ifndef DATUMSTACK_H
#define DATUMSTACK_H

#include "Datum.h"
#include <vector>
#include <stdexcept>

class DatumStack
{
private:
    std::vector<Datum> stack;

public:
    DatumStack();
    DatumStack(Datum *data, int size);

    void push(const Datum &d);

    Datum pop();

    bool isEmpty() const;

    const Datum &top() const;

    void clear();

    size_t size() const;
};

#endif