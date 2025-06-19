/*
 *  PassengerQueues.h
 *  Jack Craig
 *  02/12/2025
 *
 *  CS 15 Project 1: Metro Simulator
 *  Handles the passenger queue for the metro simulator project.
 *
 */

#ifndef PASSENGER_QUEUE_H
#define PASSENGER_QUEUE_H

#include "Passenger.h"
#include <list>
#include <iostream>

class PassengerQueue
{
public:
    Passenger front();
    void dequeue();
    void enqueue(const Passenger &passenger);
    int size();
    void print(std::ostream &output);
    bool empty();

private:
    std::list<Passenger> passengers;
};

#endif