/*
 *  MetroSim.cpp
 *  Jack Craig
 *  02/12/2025
 *
 *  CS 15 Project 1: Metro Simulator
 *  Handles the general code for the metro simulator project.
 *
 */

#include "MetroSim.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace std;

/*
 * name:      MetroSim( )
 * purpose:   Is the constructor for the MetroSim program, it reads the station
 *            data and sets up the system.
 * arguments: a constant string to the file of the station names, and a
 *            constant string to the name of the output file.
 * returns:   none
 * effects:   Reads station data and makes train queues
 */
MetroSim::MetroSim(const std::string &stationsFile,
                   const std::string &outputFileName)
{
    // string &stationsFile, string &outputFile
    passengerNumberCount = 1;
    readStationFile(stationsFile);
    outputFile.open(outputFileName);
}

/*
 * name:      readStationFile( )
 * purpose:   Reads station names from the file and creates the station data
 * arguments: Constant string to the station file name
 * returns:   none
 * effects:   Creates a list of stations in the program.
 */
void MetroSim::readStationFile(const string &stationsFile)
{
    ifstream stationsInput(stationsFile);
    if (not(stationsInput.is_open()))
    {
        throw std::runtime_error("Error: could not open file " + stationsFile);
    }

    string stationName;
    while (getline(stationsInput, stationName))
    {
        addStation(stationName);
    }

    train.currentStation = 0;
    train.queues.resize(stations.size());
}

/*
 * name:      addStation( )
 * purpose:   Adds a station to the program
 * arguments: a constant string of the name of the station
 * returns:   none
 * effects:   Adds a new station to the list of stations.
 */
void MetroSim::addStation(const string &stationName)
{
    stations.push_back({stationName, PassengerQueue()});
    train.queues.push_back(PassengerQueue());
}

/*
 * name:      run( )
 * purpose:   Runs the simulation, starts the commands.
 * arguments: Input stream commandInput to recieve commands
 * returns:   none
 * effects:   Processes user input and updates the program
 */
void MetroSim::run(istream &commandInput)
{
    std::string command;
    bool running = true;
    while (running)
    {
        printState();
        std::cout << "Command? ";
        if (not std::getline(commandInput, command))
        {
            running = false;
        }
        processCommand(command);
        if (command == "m f")
        {
            running = false;
        }
    }
}

/*
 * name:      printState( )
 * purpose:   Prints the current state of the train and stations.
 * arguments: none.
 * returns:   none
 * effects:   Outputs the train and stations to the console.
 */
void MetroSim::printState()
{
    cout << "Passengers on the train: {";
    for (PassengerQueue &p : train.queues)
    {
        p.print(cout);
    }
    cout << "}" << endl;

    for (size_t i = 0; i < stations.size(); i++)
    {
        if (int(i) == train.currentStation)
        {
            cout << "TRAIN: ";
        }
        else
        {
            cout << "       ";
        }
        cout << "[" << i << "] " << stations[i].name << " {";
        stations[i].queue.print(cout);
        cout << "}" << endl;
    }
}

/*
 * name:      processCommand( )
 * purpose:   Deals with a user command and does the correct thing, (moves
 *            train if m m, ends program if m f, etc)
 * arguments: A constant string command
 * returns:   none
 * effects:   Changes the train and station based on commands
 */
void MetroSim::processCommand(const string &command)
{
    istringstream iss(command);
    string cmd;
    iss >> cmd;

    if (cmd == "p")
    {
        int arrival, departure;
        iss >> arrival >> departure;
        addPassenger(arrival, departure);
    }
    else if (cmd == "m")
    {
        string cmdtwo;
        iss >> cmdtwo;
        if (cmdtwo == "m")
        {
            moveTrain();
        }
        else if (cmdtwo == "f")
        {
            endSimulation();
        }
        else
        {
            cout << "Unknown command:  m " << command << endl;
        }
    }
    else
    {
        cerr << "Invalid command: " << command << endl;
    }
}

/*
 * name:      addPassenger( )
 * purpose:   Adds a passenger to the program, and places the in the correct
 *            station.
 * arguments: Integer arrival and departure for the passenger
 * returns:   none
 * effects:   Adds a new passenger to the correct station.
 */
void MetroSim::addPassenger(int arrival, int departure)
{
    if (arrival < 0 or arrival >= int(stations.size()) or
        departure < 0 or departure >= int(stations.size()))
    {
        throw runtime_error("Invalid station index");
    }
    Passenger passenger(passengerNumberCount++, arrival, departure);
    stations[arrival].queue.enqueue(passenger);
}

/*
 * name:      moveTrain( )
 * purpose:   Moves the train to the next station, and boards and unloads
 *            passengers
 * arguments: none
 * returns:   none
 * effects:   Moves the train and transfers passengers.
 */
void MetroSim::moveTrain()
{
    while (not stations[train.currentStation].queue.empty())
    {
        Passenger passenger = stations[train.currentStation].queue.front();
        stations[train.currentStation].queue.dequeue();
        train.queues[passenger.getEndingStation()].enqueue(passenger);
    }

    train.currentStation = (train.currentStation + 1) % stations.size();

    while (not train.queues[train.currentStation].empty())
    {
        Passenger passenger = train.queues[train.currentStation].front();
        train.queues[train.currentStation].dequeue();
        if (outputFile.is_open())
        {
            outputFile << "Passenger " << passenger.getId()
                       << " left train at station "
                       << stations[train.currentStation].name << std::endl;
        }
    }
}

/*
 * name:      endSimulation( )
 * purpose:   Ends the MetroSim program and prints a closing message
 * arguments: none.
 * returns:   none
 * effects:   Outputs a closing message and stops program.
 */
void MetroSim::endSimulation()
{
    cout << "Thanks for playing MetroSim. Have a nice day!" << endl;
    if (outputFile.is_open())
    {
        outputFile.close();
    }
}

/*
 * name:      getStationCount( )
 * purpose:   Used for unit testing to ensure funcitonal program
 * arguments: none.
 * returns:   Number of stations
 * effects:   none
 */
int MetroSim::getStationCount() const
{
    return stations.size();
}

/*
 * name:      getCurrentStation( )
 * purpose:   Purely needed for unit testing, to ensure proper functionality
 * arguments: none
 * returns:   The current station the train is at.
 * effects:   none.
 */
int MetroSim::getCurrentStation() const
{
    return train.currentStation;
}
