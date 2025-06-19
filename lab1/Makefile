# Makefile
# Matt Russell
# CS15 Lab 01: Unit Testing and ArrayLists

# This Makefile builds the executable used by unit_test
#
# Do not do "make unit_test" yourself.  It won't work.
# Just run "unit_test" in this directory and the unit_test script will take 
# care of everything.
#
# Why: unit_test_driver.o does not exist in the current working directory.
# The unit_test script builds this file for you, and then runs 
# 'make unit_test'.
#
# After the unit_test script runs, it removes the executable and driver
# source.
#
# If you would like to write your own main program, you may do so.
# Create a main.cpp that uses your ArrayList, and then
# run "make lab_test".

CXX      = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra -Wpedantic -Wshadow -g

unit_test: unit_test_driver.o ArrayList.o
	${CXX} unit_test_driver.o ArrayList.o

ArrayList.o: ArrayList.cpp ArrayList.h
	${CXX} ${CXXFLAGS} -c ArrayList.cpp

lab_test: main.cpp ArrayList.cpp ArrayList.h
	${CXX} main.cpp ArrayList.cpp -o lab_test

main.o: main.cpp ArrayList.h
	${CXX} ${CXXFLAGS} -c main.cpp

# --- clean destroys all the .o files
clean:
	@rm -rf *.o *~ core* a.out
