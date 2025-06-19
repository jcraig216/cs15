/*
 *  Passenger.cpp
 *  Jack Craig
 *  02/12/2025
 *
 *  CS 15 Project 1: Metro Simulator
 *  Handles the passenger struct for the metro simulator project.
 *
 */

#ifndef __PASSENGER_H__
#define __PASSENGER_H__

#include <iostream>

class Passenger
{
public:
    Passenger(int id, int startingStation, int endingStation);
    int getId();
    int getStartingStation();
    int getEndingStation();
    void print(std::ostream &output);

private:
    int id;
    int startingStation;
    int endingStation;
};

#endif
