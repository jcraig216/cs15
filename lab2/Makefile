#
#  CS 15: Data Structures
#  Tufts University
#  Makefile for Lab 02
#
#  Makefile for planet-driver, LinkedList and Planet
#
# Note that planet-driver and unit_test are both linking targets
# planet-driver is used to link the driver with the LL and Planet classes
# unit_test is a target used by the unit_test unit testing framework
# If you'd like to use unit_test on your LinkedList class, you can do so
# by creating a unit_tests.h file with testing functions. Remember that you won't
# run make to use unit_test; intead, just run unit_test

CXX      = clang++
CXXFLAGS = -Wall -Wextra -Wpedantic -Wshadow -g
LDFLAGS  = -g

# linking targets
planet-driver: planet-driver.o LinkedList.o Planet.o
	$(CXX) $(LDFLAGS) -o planet-driver planet-driver.o LinkedList.o Planet.o 

unit_test: unit_test_driver.o LinkedList.o Planet.o
	$(CXX) $(CXXFLAGS) unit_test_driver.o LinkedList.o Planet.o

# Rules to compile the dependencies
planet-driver.o: planet-driver.cpp LinkedList.h Planet.h
	$(CXX) $(CXXFLAGS) -c planet-driver.cpp

LinkedList.o: LinkedList.cpp LinkedList.h Planet.h
	$(CXX) $(CXXFLAGS) -c LinkedList.cpp

Planet.o: Planet.cpp Planet.h
	$(CXX) $(CXXFLAGS) -c Planet.cpp

clean:
	@rm -f *.o core* vgcore* *# *~ planet-driver
