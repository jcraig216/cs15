/*
 *  CharLinkedList.cpp
 *  Jack Craig jcraig05
 *  01/28/2025
 *
 *  CS 15 HW 2 Cheshire ConCATenation - Time to get linked up in Fur
 *
 *  Create and use a linkedlist ADT implementation.
 *
 */

#include "CharLinkedList.h"

#include <string>
#include <sstream>

using namespace std;
/*
 * name:      CharLinkedList default constructor
 * purpose:   initialize an empty CharLinkedList
 * arguments: none
 * returns:   none
 * effects:   numItems to 0 (also updates capacity and data array)
 */
CharLinkedList::CharLinkedList()
{
    front = nullptr;
    numItems = 0;
}
/*
 * name:      CharLinkedList character constructor
 * purpose:   initialize an CharLinkedList with a single character
 * arguments: character c
 * returns:   none
 * effects:   numItems to 1, and the lsit contains one node with the char c.
 */
CharLinkedList::CharLinkedList(char c)
{
    front = newNode(c, nullptr);
    numItems = 1;
}
/*
 * name:      CharLinkedList default constructor
 * purpose:   initialize an empty CharLinkedList
 * arguments: character array arr & integer size
 * returns:   none
 * effects:   numItems to integer size (also updates capacity and data array)
 */
CharLinkedList::CharLinkedList(char arr[], int size)
{
    front = nullptr;
    numItems = 0;

    if (size > 0)
    {
        front = newNode(arr[0], nullptr);

        Node *curr = front;
        numItems++;

        for (int i = 1; i < size; i++)
        {
            curr->next = newNode(arr[i], nullptr);
            curr = curr->next;
            numItems++;
        }
    }
}
/*
 * name:      CharLinkedList copy constructor
 * purpose:   initialize a CharLinkedList as a deep copy of another list
 * arguments: constant CharLinkedList struct &other
 * returns:   none
 * effects:   numItems to numItems of other list, and deep copy of nodes is
 * made
 */
CharLinkedList::CharLinkedList(const CharLinkedList &other)
{
    numItems = other.numItems;
    front = nullptr;

    if (other.front != nullptr)
    {
        front = newNode(other.front->data, nullptr);

        Node *curr = front;
        Node *other_curr = other.front->next;

        while (other_curr != nullptr)
        {
            curr->next = newNode(other_curr->data, nullptr);
            curr = curr->next;
            other_curr = other_curr->next;
        }
    }
}
/*
 * name:      CharLinkedList default destructor
 * purpose:   deletes a CharLinkedList
 * arguments: none
 * returns:   none
 * effects:   deletes a CharLinkedList
 */
CharLinkedList::~CharLinkedList()
{
    clear();
}
/*
 * name:      CharLinkedList assingment operator=
 * purpose:   make a deep copy of another CharLinkedList
 * arguments: constant CharLinkedList struct &other
 * returns:   pointer to the current list
 * effects:   clears the current list and makes a deep copy of the other list
 */
CharLinkedList &CharLinkedList::operator=(const CharLinkedList &other)
{
    if (this == &other)
    {
        return *this;
    }
    // Clears the current list to avoid leaks
    clear();

    if (other.front != nullptr)
    {
        front = newNode(other.front->data, nullptr);
        Node *curr = front;
        Node *other_curr = other.front->next;

        while (other_curr != nullptr)
        {
            curr->next = newNode(other_curr->data, nullptr);
            curr = curr->next;
            other_curr = other_curr->next;
        }
    }
    else
    {
        front = nullptr;
    }

    numItems = other.numItems;
    return *this;
}
/*
 * name:      newNode
 * purpose:   creates and adds a new node to the list with given data and
 * pointer
 * arguments: char data containing the letter, Node *next pointing to the next
 * node in the list.
 * returns:   a pointer to the new node
 * effects:   Adds a node to the linked list.
 */
CharLinkedList::Node *CharLinkedList::newNode(char data, Node *next)
{
    Node *new_node = new Node;
    new_node->next = next;
    new_node->data = data;
    return new_node;
}
/*
 * name:      isEmpty
 * purpose:   checks to see if the linked list is empty
 * arguments: none
 * returns:   a boolean value if the struct is empty or not.
 * effects:   none
 */
bool CharLinkedList::isEmpty() const
{
    if (numItems == 0)
    {
        return true;
    }
    return false;
}
/*
 * name:      clear
 * purpose:   restarts and clears a list
 * arguments: none
 * returns:   none
 * effects:   clears a list.
 */
void CharLinkedList::clear()
{
    while (!isEmpty())
    {
        popFromFront();
    }
}
/*
 * name:      size
 * purpose:   checks the number of items in the list
 * arguments: none
 * returns:   the number of items (the size)
 * effects:   none
 */
int CharLinkedList::size() const
{
    return numItems;
}
/*
 * name:      first
 * purpose:   Gets the first element from the list.
 * arguments: none
 * returns:   The first element from the list.
 * effects:   none
 */
char CharLinkedList::first() const
{
    if (isEmpty())
    {
        std::stringstream ss;
        ss << "cannot get first of empty LinkedList";
        throw std::runtime_error(ss.str());
    }
    return front->data;
}
/*
 * name:      Last
 * purpose:   Gets the last element from the list.
 * arguments: none
 * returns:   The last element from the list.
 * effects:   none
 */
char CharLinkedList::last() const
{
    if (isEmpty())
    {
        std::stringstream ss;
        ss << "cannot get last of empty LinkedList";
        throw std::runtime_error(ss.str());
    }

    Node *curr = front;

    while (curr->next != nullptr)
    {
        curr = curr->next;
    }
    return curr->data;
}
/*
 * name:      elementAt
 * purpose:   Get the element at a certain index
 * arguments: Integer index
 * returns:   An element from a certain index
 * effects:   none
 */
char CharLinkedList::elementAt(int index) const
{
    if (index < 0 or index >= size())
    {
        std::stringstream ss;
        ss << "index (" << index << ") not in range of [0.." << size()
           << ")";
        throw std::range_error(ss.str());
    }

    Node *curr = front;
    for (int i = 0; i < index; i++)
    {
        curr = curr->next;
    }
    return curr->data;
}
/*
 * name:      toReverseStringHelper
 * purpose:   Recursively reverses the character order from the linked list
 * into a string
 * arguments: string stream address to edit the message and the pointer to the
 * node.
 * returns:   none
 * effects:   Prints the reverse order of the list.
 */
void CharLinkedList::toReverseStringHelper(std::stringstream &ss,
                                           Node *curr) const
{
    if (curr == nullptr)
        return;

    toReverseStringHelper(ss, curr->next);
    ss << curr->data;
}
/*
 * name:      toString
 * purpose:   Turns the list into a readable string
 * arguments: none
 * returns:   stringstream ss, containing the list in string form.
 * effects:   none
 */
std::string CharLinkedList::toString() const
{
    std::stringstream ss;
    ss << "[CharLinkedList of size " << size() << " <<";
    Node *curr = front;
    while (curr != nullptr)
    {
        ss << curr->data;
        curr = curr->next;
    }
    ss << ">>]";

    return ss.str();
}
/*
 * name:      toReverseString
 * purpose:   Converts the linked list into a readable string in reverse order
 * arguments: none
 * returns:   stringstream ss, containing the reverse string.
 * effects:   none
 */
std::string CharLinkedList::toReverseString() const
{
    std::stringstream ss;
    ss << "[CharLinkedList of size " << size() << " <<";
    toReverseStringHelper(ss, front);
    ss << ">>]";

    return ss.str();
}
/*
 * name:      pushAtBack
 * purpose:   Pushes a character onto the end of a list.
 * arguments: character c
 * returns:   nothing
 * effects:   adds an elemet to the back of a list, also increases numItems.
 */
void CharLinkedList::pushAtBack(char c)
{
    if (front == nullptr)
    {
        front = newNode(c, nullptr);
    }
    else
    {
        Node *curr = front;

        while (curr->next != nullptr)
        {
            curr = curr->next;
        }
        curr->next = newNode(c, nullptr);
    }
    numItems++;
}
/*
 * name:      pushAtFront
 * purpose:   Pushes a character onto the front of the list.
 * arguments: character c
 * returns:   none
 * effects:   Adds an element to the front of the list and increases numItems.
 */
void CharLinkedList::pushAtFront(char c)
{
    front = newNode(c, front);
    numItems++;
}
/*
 * name:      InsertAt
 * purpose:   Inserts and element at a specific index
 * arguments: character c and integer index
 * returns:   none
 * effects:   Inserts an element at specific index, increases numItems.
 */
void CharLinkedList::insertAt(char c, int index)
{
    if (index < 0 or index > size())
    {
        std::stringstream ss;
        ss << "index (" << index << ") not in range [0.." << size() << "]";
        throw std::range_error(ss.str());
    }

    if (index == 0)
    {
        pushAtFront(c);
        return;
    }

    Node *curr = front;

    for (int i = 0; i < index - 1; i++)
    {
        curr = curr->next;
    }
    curr->next = newNode(c, curr->next);
    numItems++;
}
/*
 * name:      insertInOrder
 * purpose:   Insert an element in the correct unicode order
 * arguments: character c
 * returns:   none
 * effects:   adds element at the unicode ordered spot, then increases numItems
 */
void CharLinkedList::insertInOrder(char c)
{
    if (front == nullptr or c < front->data)
    {
        pushAtFront(c);
        return;
    }
    Node *curr = front;
    // using a while loop to check each letter until landing on the best spot
    while (curr->next != nullptr and curr->next->data < c)
    {
        curr = curr->next;
    }
    // Moving everything over in order to allow the new element to be added
    curr->next = newNode(c, curr->next);
    numItems++;
}
/*
 * name:      popFromFront
 * purpose:   Removes the first element
 * arguments: none
 * returns:   none
 * effects:   Removes the first element.
 */
void CharLinkedList::popFromFront()
{
    if (isEmpty())
    {
        std::stringstream ss;
        ss << "cannot pop from empty LinkedList";
        throw std::runtime_error(ss.str());
    }

    Node *to_delete = front;
    front = front->next;
    delete to_delete;

    numItems--;
}
/*
 * name:      popFromBack
 * purpose:   Removes the last element in the list
 * arguments: none
 * returns:   none
 * effects:   Removes the last element in the list
 */
void CharLinkedList::popFromBack()
{
    if (isEmpty())
    {
        std::stringstream ss;
        ss << "cannot pop from empty LinkedList";
        throw std::runtime_error(ss.str());
    }
    if (front->next == nullptr)
    {
        delete front;
        front = nullptr;
    }
    else
    {
        Node *curr = front;
        // Trying to find the second to last node in order to delete
        //  the last node
        while (curr->next->next != nullptr)
        {
            curr = curr->next;
        }
        delete curr->next;
        curr->next = nullptr;
    }
    numItems--;
}
/*
 * name:      removeAt
 * purpose:   Removes an element at a certain index
 * arguments: Integer index
 * returns:   none
 * effects:   Removes an element at an index
 */
void CharLinkedList::removeAt(int index)
{
    if (index < 0 or index > size())
    {
        std::stringstream ss;
        ss << "index (" << index << ") not in range [0.." << size() << "]";
        throw std::range_error(ss.str());
    }

    if (index == 0)
    {
        Node *temp = front;
        front = front->next;
        delete temp;
        numItems--;
        return;
    }

    Node *curr = front;
    for (int i = 0; i < index - 1; i++)
    {
        curr = curr->next;
    }

    Node *to_remove = curr->next;
    curr->next = to_remove->next;
    delete to_remove;
    numItems--;
}
/*
 * name:      replaceAtHelper
 * purpose:   Replaces an element at an index
 * arguments: character c containing the letter, and integer index of the spot
 * we want to insert the letter, then a pointer to the current node.
 * returns:   none
 * effects:   Replaces an element at an index
 */
void CharLinkedList::replaceAtHelper(Node *curr, char c, int index)
{
    if (index == 0)
    {
        curr->data = c;
        return;
    }

    replaceAtHelper(curr->next, c, index - 1);
}
/*
 * name:      replaceAt
 * purpose:   Replaces an element at an index
 * arguments: character c containing the letter, and integer index of the spot
 * we want to insert the letter.
 * returns:   none
 * effects:   Replaces an element at an index
 */
void CharLinkedList::replaceAt(char c, int index)
{
    if (index < 0 or index > size())
    {
        std::stringstream ss;
        ss << "index (" << index << ") not in range [0.." << size() << "]";
        throw std::range_error(ss.str());
    }

    replaceAtHelper(front, c, index);
}
/*
 * name:      Concatenate
 * purpose:   Adds the end of one list to another
 * arguments: CharLinkedList list
 * returns:   none
 * effects:   Adds the end of one list to another
 */
void CharLinkedList::concatenate(CharLinkedList *other)
{
    if (other == nullptr or other->front == nullptr)
    {
        return;
    }
    if (front == nullptr)
    {
        Node *other_curr = other->front;
        while (other_curr != nullptr)
        {
            pushAtBack(other_curr->data);
            other_curr = other_curr->next;
        }
        return;
    }

    Node *curr = front;
    while (curr->next != nullptr)
    {
        curr = curr->next;
    }

    Node *other_curr = other->front;
    while (other_curr != nullptr)
    {
        curr->next = newNode(other_curr->data, nullptr);
        curr = curr->next;
        other_curr = other_curr->next;
    }

    numItems += other->numItems;
}
