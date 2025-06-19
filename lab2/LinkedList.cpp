/*
 * LinkedList.cpp
 *
 * CS 15 Lab 02
 * by Tyler Calabrese, January 2020
 * Edited by Matt Russell, Juliana Vega, and Alexis Blair, Jan 2021
 *
 * An implementation of the LinkedList interface, the LinkedList can be used
 * to store Planets.
 *
 * NOTE: This is implemented using a singly-linked list with no back pointer.
 *
 */
#include "LinkedList.h"
#include <sstream>
#include <string>

/* Default constructor
 *    Purpose: Initializes an empty LinkedList
 * Parameters: None
 *    Returns: None
 */
LinkedList::LinkedList()
{
    front = nullptr;
    size = 0;
}

/* toString
 *    Purpose: Report the state of the list as a string
 * Parameters: None
 *    Returns: A string with the state of the list
 */
std::string LinkedList::toString() const
{
    std::stringstream ss;
    ss << "LinkedList of size " << this->size << "\n";
    ss << "---------------------\n";

    Node *curr = this->front;
    while (curr != nullptr)
    {
        ss << curr->toString() << "\n";
        curr = curr->next;
    }

    return ss.str();
}

/* ******************************************
 * TODO: implement the LinkedList destructor
 * ******************************************
 * Destructor
 *    Purpose: Free heap-allocated memory of 'this' LinkedList
 * Parameters: None
 *    Returns: None
 */
LinkedList::~LinkedList()
{
    delete front;
}

LinkedList::Node *LinkedList::newNode(Planet newInfo, Node *next)
{
    Node *new_node = new Node;
    new_node->next = next;
    new_node->info = newInfo;
    return new_node;
}

/* ******************************************
 * TODO: implement the pushAtFront function
 * ******************************************
 * pushAtFront
 *    Purpose: Adds a Planet to the front of the list
 * Parameters: The Planet to be added to the list
 *    Returns: None
 */
void LinkedList::pushAtFront(Planet p)
{
    front = newNode(p, front);
    size++;
}

/*
 * ******************************************
 * TODO: implement the pushAtBack function
 * ******************************************
 * pushAtBack
 *    Purpose: Adds a Planet to the back of the list
 * Parameters: The Planet to be added to the list
 *    Returns: None
 */
void LinkedList::pushAtBack(Planet p)
{
    if (front == nullptr)
    {
        front = newNode(p, nullptr);
        return;
    }
    size++;

    Node *curr_node = front;
    while (curr_node->next != nullptr)
    {
        curr_node = curr_node->next;
    }
    curr_node->next = newNode(p, nullptr);
}

/* ****************************************
 * TODO (Bonus JFFE): implement the reverse function
 * ****************************************
 * reverse
 *    Purpose: Reverses the list
 * Parameters: None
 *    Returns: None
 */
void LinkedList::reverse() {}
