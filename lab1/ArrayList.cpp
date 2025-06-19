/*
 * ArrayList.cpp
 * Matt Russell && Matt Champlin
 * CS15 Lab 01: Unit Testing and ArrayLists
 * 01/06/2021
 * 09/12/2021 - updated for cs15 by mrussell
 *
 * Function definitions for the ArrayList class.
 *
 * TODO: fill in functions!
 */

#include "ArrayList.h"
#include <sstream>

using namespace std;

/*
 * name:      ArrayList default constructor
 * purpose:   initialize an empty ArrayList
 * arguments: none
 * returns:   none
 * effects:   numItems to 0 (also updates capacity and data array)
 */
ArrayList::ArrayList()
{
    numItems = 0;
    capacity = 0;
    data = nullptr;
}

/*
 * name:      ArrayList destructor
 * purpose:   free memory associated with the ArrayList
 * arguments: none
 * returns:   none
 * effects:   frees memory allocated by Arraylist instances
 */
ArrayList::~ArrayList()
{
    delete[] data;
}

/*
 * name:      size
 * purpose:   determine the number of items in the ArrayList
 * arguments: none
 * returns:   number of elements currently stored in the ArrayList
 * effects:   none
 */
int ArrayList::size() const
{
    return numItems; /* Placeholder (remove when you implement this!) */
}

/*
 * name:      isEmpty
 * purpose:   determines if the ArrayList is empty or not
 * arguments: none
 * returns:   true if ArrayList contains no elements, false otherwise
 * effects:   none
 */
bool ArrayList::isEmpty() const
{
    if (capacity == 0)
    {
        return true;
    }
    return false; /* Placeholder (remove when you implement this!) */
}

/*
 * name:      toString
 * purpose:   turns the array into a string and returns it
 * arguments: none
 * returns:   a string representation of the array
 * effects:   none
 */
std::string ArrayList::toString() const
{
    std::stringstream ss;
    ss << "[";
    /* TODO: Complete the rest of the print function by adding each element of
     *       the ArrayList to the stringstream. Note that you can use this
     *       stringstream object, ss, just as you would with std::cout. The
     *       rest of the operations necessary are provided for you. The format
     *       is: [1,2,3] for an ArrayList of 3 ints whose values are 1, 2 and 3
     *       We've given you the opening and closing braces.
     */
    for (int i = 0; i < size(); i++)
    {
        if (i == (size() - 1))
        {
            ss << data[i];
        }
        else
            ss << data[i] << ",";
    }

    ss << "]";
    return ss.str();
}

/*
 * name:      pushAtBack
 * purpose:   push the provided integer into the back of the ArrayList
 * arguments: an integer to add to the back of the list
 * returns:   none
 * effects:   increases num elements of ArrayList by 1,
 *            adds element to list
 */
void ArrayList::pushAtBack(int elem)
{
    if (size() == capacity)
    {
        expand();
    }
    data[size()] = elem;
    numItems++;
}

/*
 * name:      expand
 * purpose:   increase the capacity of the ArrayList
 * arguments: none
 * returns:   none
 * effects:   creates new, larger array on heap, copies over elements,
 *            and recycles the old array
 */
void ArrayList::expand()
{
    if (size() == capacity)
    {
        int newCapacity = (capacity + 1) * 2;
        int *newArray = new int[newCapacity];
        for (int i = 0; i < size(); i++)
        {
            newArray[i] = data[i];
        }
        delete[] data;
        data = newArray;
        capacity = newCapacity;
    }
}

/*
 * name:      find - JFFE
 * purpose:   determine if the provided integer is within the ArrayList
 * arguments: an integer to find
 * returns:   returns true if x is in the ArrayList, false otherwise
 * effects:   none
 */
bool ArrayList::find(int to_find) const
{
    return false; /* Placeholder (remove when you implement this!) */
}

/*
 * name:      popFromBack - JFFE
 * purpose:   remove the last item from the ArrayList
 * arguments: none
 * returns:   none
 * effects:   decreases num items of ArrayList by 1,
 *            removes the last item from the list
 */
void ArrayList::popFromBack()
{
    if (numItems > 0)
    {
        numItems--;
    }
}
