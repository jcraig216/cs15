/*
 *  CharArrayList.cpp
 *  Jack Craig
 *  01/23/2025
 *
 *  COMP 15 HW 1 Cheshire ConCATenation
 *
 *  ArrayList Homework 1
 *
 */
#include "CharArrayList.h"

#include <sstream>

using namespace std;

/*
 * name:      CharArrayList default constructor
 * purpose:   initialize an empty CharArrayList
 * arguments: none
 * returns:   none
 * effects:   numItems to 0 (also updates capacity and data array)
 */
CharArrayList::CharArrayList()
{
    numItems = 0;
    capacity = 1;
    data = new char[capacity];
}

/*
 * name:      CharArrayList character constructor
 * purpose:   initialize an empty ArrayList
 * arguments: character c
 * returns:   none
 * effects:   numItems to 1 (also updates capacity and data array)
 */
CharArrayList::CharArrayList(char c)
{
    numItems = 1;
    capacity = 1;
    data = new char[1];
    data[0] = c;
}
/*
 * name:      CharArrayList default constructor
 * purpose:   initialize an empty CharArrayList
 * arguments: character array arr & integer size
 * returns:   none
 * effects:   numItems to integer size (also updates capacity and data array)
 */
CharArrayList::CharArrayList(char arr[], int size)
{
    numItems = size;
    capacity = size;
    data = new char[size];
    for (int i = 0; i < size; i++)
    {
        data[i] = arr[i];
    }
}
/*
 * name:      CharArrayList default constructor
 * purpose:   initialize an empty CharArrayList
 * arguments: constant CharArrayList struct &other
 * returns:   none
 * effects:   numItems to numItems of other struct
 *            (also updates capacity and data array)
 */
CharArrayList::CharArrayList(const CharArrayList &other)
{
    numItems = other.numItems;
    capacity = other.capacity;
    data = new char[other.capacity];
    for (int i = 0; i < other.numItems; i++)
    {
        data[i] = other.data[i];
    }
}
/*
 * name:      CharArrayList default destructor
 * purpose:   deletes a CharArrayList
 * arguments: none
 * returns:   none
 * effects:   deletes a CharArrayList
 */
CharArrayList::~CharArrayList()
{
    // Checks if data is already empty
    if (data != nullptr)
    {
        // if not delete
        delete[] data;
    }
    // then make empty
    data = nullptr;
}
/*
 * name:      CharArrayList operator=
 * purpose:   make a deep copy of other structs
 * arguments: constant CharArrayList struct &other
 * returns:   none
 * effects:   changes how structs are copied
 */
CharArrayList &CharArrayList::operator=(const CharArrayList &other)
{
    if (this == &other)
    {
        return *this;
    }
    delete[] data;
    // makes the data empty and deletes it to ensure its empty
    data = nullptr;
    // creates new data array
    data = new char[other.capacity];
    // fills said array
    for (int i = 0; i < other.numItems; i++)
    {
        data[i] = other.data[i];
    }
    // then finished setting up the deep copy
    numItems = other.numItems;
    capacity = other.capacity;
    return *this;
}
/*
 * name:      isEmpty
 * purpose:   checks to see if the CharArrayList is empty
 * arguments: none
 * returns:   a boolean value if the struct is empty or not.
 * effects:   none
 */
bool CharArrayList::isEmpty() const
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
void CharArrayList::clear()
{
    delete[] data;
    numItems = 0;
    capacity = 0;
    data = nullptr;
}
/*
 * name:      size
 * purpose:   checks the number of items in the list
 * arguments: none
 * returns:   the number of items (the size)
 * effects:   none
 */
int CharArrayList::size() const
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
char CharArrayList::first() const
{

    if (isEmpty())
    {
        std::stringstream ss;
        ss << "cannot get first of empty ArrayList";
        throw std::runtime_error(ss.str());
    }
    return data[0];
}
/*
 * name:      Last
 * purpose:   Gets the last element from the list.
 * arguments: none
 * returns:   The last element from the list.
 * effects:   none
 */
char CharArrayList::last() const
{
    if (isEmpty())
    {
        std::stringstream ss;
        ss << "cannot get last of empty ArrayList";
        throw std::runtime_error(ss.str());
    }

    return data[size() - 1];
}
/*
 * name:      elementAt
 * purpose:   Get the element at a certain index
 * arguments: Integer index
 * returns:   An element from a certain index
 * effects:   none
 */
char CharArrayList::elementAt(int index) const
{
    if (index < 0 || index >= size())
    {
        std::stringstream ss;
        ss << "index ()" << index << ") not in range of [0.." << size() << ")";
        throw std::range_error(ss.str());
    }

    return data[index];
}
/*
 * name:      toString
 * purpose:   Turns the list into a readable string
 * arguments: none
 * returns:   stringstream ss, containing the list in string form.
 * effects:   none
 */
std::string CharArrayList::toString() const
{
    std::stringstream ss;
    ss << "[CharArrayList of size " << size() << " <<";
    for (int i = 0; i < size(); i++)
    {
        ss << data[i];
    }
    ss << ">>]";

    return ss.str();
}
/*
 * name:      toReverseString
 * purpose:   Turns the list into string form but backwards
 * arguments: none
 * returns:   stringstream ss, containing the reverse string.
 * effects:   none
 */
std::string CharArrayList::toReverseString() const
{
    std::stringstream ss;
    ss << "[CharArrayList of size " << size() << " <<";
    for (int i = size() - 1; i >= 0; i--)
    {
        ss << data[i];
    }
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
void CharArrayList::pushAtBack(char c)
{
    // Chdcking if the list needs to be expanded
    if (size() >= capacity || isEmpty())
    {
        expand();
    }
    data[size()] = c;
    numItems++;
}
/*
 * name:      pushAtFront
 * purpose:   Pushes a character onto the front of the list.
 * arguments: character c
 * returns:   none
 * effects:   Adds an element to the front of the list and increases numItems.
 */
void CharArrayList::pushAtFront(char c)
{
    // Checking if the list needs to be expanded
    if (size() == capacity || isEmpty())
    {
        expand();
    }
    // moving everything in the list back one
    for (int i = size(); i > 0; i--)
    {
        data[i] = data[i - 1];
    }
    data[0] = c;
    numItems++;
}
/*
 * name:      InsertAt
 * purpose:   Inserts and element at a specific index
 * arguments: character c and integer index
 * returns:   none
 * effects:   Inserts an element at specific index, increases numItems.
 */
void CharArrayList::insertAt(char c, int index)
{
    // Checking if the list needs to be expanded
    if (size() >= capacity || isEmpty())
    {
        expand();
    }
    // Making sure correct input
    if (index < 0 || index > size())
    {
        std::stringstream ss;
        ss << "index (" << index << ") not in range [0.." << size() << "]";
        throw std::range_error(ss.str());
    }
    // Moving everything in the list over from where the new element is
    // inserted
    for (int i = size(); i > index; i--)
    {
        data[i] = data[i - 1];
    }
    data[index] = c;
    numItems++;
}
/*
 * name:      insertInOrder
 * purpose:   Insert an element in the correct unicode order
 * arguments: character c
 * returns:   none
 * effects:   adds element at the unicode ordered spot, then increases numItems
 */
void CharArrayList::insertInOrder(char c)
{
    // Checking if list needs to be expanded
    if (size() >= capacity || isEmpty())
    {
        expand();
    }
    // creating temporary integer to find the correct spot
    int index = 0;
    // using a while loop to check each letter until landing on the best spot
    while (index < size() && data[index] < c)
    {
        index++;
    }
    // Moving everything over in order to allow the new element to be added
    for (int i = size(); i > index; i--)
    {
        data[i] = data[i - 1];
    }
    data[index] = c;
    numItems++;
}
/*
 * name:      popFromFront
 * purpose:   Removes the first element
 * arguments: none
 * returns:   none
 * effects:   Removes the first element.
 */
void CharArrayList::popFromFront()
{
    // Checking if the list is already empty
    if (isEmpty())
    {
        std::stringstream ss;
        ss << "cannot pop from empty ArrayList";
        throw std::runtime_error(ss.str());
    }
    // Moves everything back down one
    for (int i = 0; i < size() - 1; i++)
    {
        data[i] = data[i + 1];
    }
    // Removes from the number of items.
    numItems--;
}
/*
 * name:      popFromBack
 * purpose:   Removes the last element in the list
 * arguments: none
 * returns:   none
 * effects:   Removes the last element in the list
 */
void CharArrayList::popFromBack()
{
    // Checks if the list is empty or has something to remove
    if (isEmpty())
    {
        std::stringstream ss;
        ss << "cannot pop from empty ArrayList";
        throw std::runtime_error(ss.str());
    }
    // No need to move anything over, so just lower the number of items.
    numItems--;
}
/*
 * name:      removeAt
 * purpose:   Removes an element at a certain index
 * arguments: Integer index
 * returns:   none
 * effects:   Removes an element at an index
 */
void CharArrayList::removeAt(int index)
{
    // Checks for input validation
    if (index < 0 || index >= size())
    {
        std::stringstream ss;
        ss << "index ()" << index << ") not in range of [0.." << size() << ")";
        throw std::range_error(ss.str());
    }
    // Skips if the index is at the back since this is basically
    // just popping off the back
    if (index == size() - 1)
    {
    }
    else
    {
        // Moves everything over to fill in the empty spot
        for (int i = index; i < size() - 1; i++)
        {
            data[i] = data[i + 1];
        }
    }
    numItems--;
}
/*
 * name:      replaceAt
 * purpose:   Replaces an element at an index
 * arguments: character c and integer index
 * returns:   none
 * effects:   Replaces an element at an index
 */
void CharArrayList::replaceAt(char c, int index)
{
    // Input validation
    if (index < 0 || index >= size())
    {
        std::stringstream ss;
        ss << "index ()" << index << ") not in range of [0.." << size() << ")";
        throw std::range_error(ss.str());
    }
    // Replaces the element at the index
    data[index] = c;
}
/*
 * name:      Concatenate
 * purpose:   Adds the end of one list to another
 * arguments: CharArrayList list
 * returns:   none
 * effects:   Adds the end of one list to another
 */
void CharArrayList::concatenate(CharArrayList *other)
{
    if (other->size() == 0)
    {
        return;
    }

    int neededSize = size() + other->size();
    while (neededSize >= capacity)
    {
        expand();
    }

    for (int i = 0; i < other->size(); i++)
    {
        data[size() + i] = other->data[i];
    }

    numItems += other->size();
}
/*
 * name:      Expand
 * purpose:   Expands the size of the list
 * arguments: none
 * returns:   none
 * effects:   Takes more memory in order to let in more
 */
void CharArrayList::expand()
{

    int newCapacity = (capacity + 1) * 2;
    char *newArray = new char[newCapacity];
    for (int i = 0; i < size(); i++)
    {
        newArray[i] = data[i];
    }
    delete[] data;
    data = newArray;
    capacity = newCapacity;
}