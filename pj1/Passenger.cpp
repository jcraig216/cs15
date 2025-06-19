/*
 *  Passenger.cpp
 *  Jack Craig
 *  02/12/2025
 *
 *  CS 15 Project 1: Metro Simulator
 *  Handles the passenger struct for the metro simulator project.
 *
 */

#include "Passenger.h"

#include <iostream>
#include <string>

/*
 * name:      Passenger( )
 * purpose:   This is the constructor for Passenger that initializes
 *            a Passenger object with an ID, starting station, and
 *            ending station.
 * arguments: An integer passenger ID, an integer starting station,
 *            and an integer ending station.
 * returns:   none
 * effects:   Constructs a Passenger with the provided information.
 * note:      Students do not have to modify this function.
 */
Passenger::Passenger(int id, int startingStation, int endingStation)
{
    this->id = id;
    this->startingStation = startingStation;
    this->endingStation = endingStation;
}

/*
 * name:      getId( )
 * purpose:   This is the getter (aka accessor) function that provides
 *            access to the Passenger's ID.
 * arguments: none
 * returns:   The Passenger's ID.
 * effects:   none
 * note:      Students do not have to modify this function.
 */
int Passenger::getId() { return id; }

/*
 * name:      getStartingStation( )
 * purpose:   This is the getter (aka accessor) function that provides
 *            access to the Passenger's starting station.
 * arguments: none
 * returns:   The Passenger's starting station.
 * effects:   none
 * note:      Students do not have to modify this function.
 */
int Passenger::getStartingStation() { return startingStation; }

/*
 * name:      getEndingStation( )
 * purpose:   This is the getter (aka accessor) function that provides
 *            access to the Passenger's ending station.
 * arguments: none
 * returns:   The Passenger's ending station.
 * effects:   none
 * note:      Students do not have to modify this function.
 */
int Passenger::getEndingStation() { return endingStation; }

/*
 * name:      print( )
 * purpose:   This is the function that formats the output of each passenger's
 *            information.
 * arguments: ostream address of output.
 * returns:   none
 * effects:   none
 */
void Passenger::print(std::ostream &output)
{
    output << "[" << getId() << ", " << getStartingStation() << "->"
           << getEndingStation() << "]";
}
