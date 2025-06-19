/*
 *  MetroSim.h
 *  Jack Craig
 *  02/12/2025
 *
 *  CS 15 Project 1: Metro Simulator
 *  Handles the general code for the metro simulator project.
 *
 */

#ifndef _METROSIM_H_
#define _METROSIM_H_

#include "Passenger.h"
#include "PassengerQueue.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

class MetroSim
{
public:
    MetroSim(const std::string &stationsFile, const std::string &outputFile);

    int getStationCount() const;
    int getCurrentStation() const;

    void readStationFile(const std::string &stationsFile);
    void moveTrain();
    void endSimulation();
    void printState();
    void processCommand(const std::string &command);
    void addPassenger(int arrival, int departure);
    void addStation(const std::string &stationName);

    void run(std::istream &commandInput);

private:
    struct Station
    {
        std::string name;
        PassengerQueue queue;
    };

    struct Train
    {
        std::vector<PassengerQueue> queues;
        int currentStation;
    };

    std::vector<Station> stations;
    Train train;

    std::ofstream outputFile;
    int passengerNumberCount;
};

#endif
