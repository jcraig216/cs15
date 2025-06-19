/*
 *  PassengerQueues.cpp
 *  Jack Craig
 *  02/12/2025
 *
 *  CS 15 Project 1: Metro Simulator
 *  Handles the passenger queue for the metro simulator project.
 *
 */

#include "PassengerQueue.h"

/*
 * name:      front( )
 * purpose:   This is the function that formats the output the front of the
 *            queue.
 * arguments: none.
 * returns:   Returns the front passenger object.
 * effects:   none
 */
Passenger PassengerQueue::front()
{
    if (passengers.empty())
    {
        throw std::runtime_error("PassengerQueue is empty");
    }
    return passengers.front();
}

/*
 * name:      enqueue( )
 * purpose:   This is the function that adds a passenger to the queue.
 * arguments: The address of the passenger object.
 * returns:   none
 * effects:   Adds an element to the back of the list.
 */
void PassengerQueue::enqueue(const Passenger &passenger)
{
    passengers.push_back(passenger);
}

/*
 * name:      dequeue( )
 * purpose:   This function pops off the front passenger object from the
 *            queue.
 * arguments: none.
 * returns:   none
 * effects:   removes the first element of the list.
 */
void PassengerQueue::dequeue()
{
    if (passengers.empty())
    {
        throw std::runtime_error("PassengerQueue is empty");
    }
    passengers.pop_front();
}
/*
 * name:      size( )
 * purpose:   This function outputs the size of the list / the number of
 *            passengers in the list.
 * arguments: none.
 * returns:   number of passengers as a int.
 * effects:   none.
 */
int PassengerQueue::size()
{
    return passengers.size();
}
/*
 * name:      print( )
 * purpose:   This function prompts the print function of each passenger
 *            object in the list in order.
 * arguments: none.
 * returns:   none
 * effects:   removes the first element of the list.
 */
void PassengerQueue::print(std::ostream &output)
{
    // need to use a for each loop to do this.
    // example and code inspiration taken from w3schools.com for in range loop
    // notes
    for (Passenger &p : passengers)
    {
        p.print(output);
    }
}

bool PassengerQueue::empty()
{
    if (size() == 0)
    {
        return true;
    }
    return false;
}
