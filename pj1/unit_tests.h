#include <cassert>
#include <sstream>
#include <stdexcept>
#include "PassengerQueue.h"
#include "MetroSim.h"
#include <iostream>
#include <fstream>

// Test MetroSim Constructor
void test_MetroSim_constructor()
{
    MetroSim sim("stations.txt", "output.txt");
    assert(sim.getStationCount() == 26);
    assert(sim.getCurrentStation() == 0);
}

// Test adding stations
void test_addStation()
{
    MetroSim sim("stations.txt", "output.txt");
    sim.addStation("Station1");
    sim.addStation("Station2");
    assert(sim.getStationCount() == 28);
}

// Test train moving between stations
void test_moveTrain()
{
    MetroSim sim("stations.txt", "output.txt");
    sim.addStation("Station1");
    sim.addStation("Station2");
    sim.addStation("Station3");

    sim.moveTrain();
    assert(sim.getCurrentStation() == 1);
    sim.moveTrain();
    assert(sim.getCurrentStation() == 2);
    sim.moveTrain();
    assert(sim.getCurrentStation() == 3);
}

// Test adding and processing passengers
void test_addPassenger()
{
    MetroSim sim("stations.txt", "output.txt");
    sim.addStation("Station1");
    sim.addStation("Station2");
    sim.addStation("Station3");

    sim.addPassenger(0, 2);
    sim.addPassenger(1, 2);
    assert(sim.getStationCount() == 29);
}

// Test moveTrain() with passengers boarding and deboarding
void test_moveTrain_withPassengers()
{
    MetroSim sim("stations.txt", "output.txt");
    sim.addStation("Station1");
    sim.addStation("Station2");
    sim.addStation("Station3");

    sim.addPassenger(0, 2);
    sim.addPassenger(1, 2);

    sim.moveTrain(); // Move from 0 to 1
    assert(sim.getCurrentStation() == 1);
    sim.moveTrain(); // Move from 1 to 2 (passengers should exit here)
    assert(sim.getCurrentStation() == 2);
}

// Test endSimulation()
void test_endSimulation()
{
    MetroSim sim("stations.txt", "output.txt");
    sim.addStation("Station1");
    sim.endSimulation();
}
