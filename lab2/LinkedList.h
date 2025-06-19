/*
 * LinkedList.h
 *
 * CS 15 Lab 02
 * by Tyler Calabrese, January 2020
 * edited by Matt R., Juliana Vegas, and Alexis Blair, 1/20/2021
 *
 * LinkedList is a class that represents a list of Planet instances. Planets
 * can be added to the front and to the back of this list
 *
 */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "Planet.h"

class LinkedList
{
public:
    LinkedList();

    /* TODO:  implement the destructor */
    ~LinkedList();

    /* TODO: implement these two functions */
    void pushAtFront(Planet p);
    void pushAtBack(Planet p);

    /* TODO (bonus JFFE): implement this function */
    void reverse();

    std::string toString() const;

private:
    struct Node
    {
        Planet info;
        Node *next;
        std::string toString() { return info.toString(); };
    };

    Node *front;
    int size;

    Node *newNode(Planet newInfo, Node *next);
};

#endif
