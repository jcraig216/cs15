/*
 * ArrayList.h
 * Matt Russell && Matt Champlin - Edited by Kathy Quintanilla (formatting)
 * CS15 Lab 01: Unit Testing and ArrayLists
 * 01/06/2021
 *
 * This is a class declaration for an ArrayList for Lab 01.
 *
 * TODO: complete the file!
 */
#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <string>

class ArrayList
{
public:
    /* TODO: Implement the constructor, destructor, pushAtBack, isEmpty,
     *        size, toString, and expand functions.
     */
    ArrayList();
    ~ArrayList();

    void pushAtBack(int elem);

    bool isEmpty() const;
    int size() const;
    std::string toString() const;

    /* Just For Fun Exercise!
     * Write a find function that returns true if a given integer is in the
     * ArrayList, and false if not.
     */
    bool find(int to_find) const;

    /* Just For Fun Exercise!
     * Write a popFromBack function that removes the last element of the
     * ArrayList.
     */
    void popFromBack();

private:
    int numItems;
    int capacity;

    /* TODO: what is the private member variable that *hint* points to the
     *       elements of the list? Add it here!
     */
    int *data;
    /* TODO: expand() helper function for changing the capacity of the
     *       ArrayList
     */
    void expand();
};

#endif
