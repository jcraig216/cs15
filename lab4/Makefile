###
### Makefile for CS15 Lab 04: Recursion
###

LABNUM   = 5
CXX      = clang++
CXXFLAGS = -g -Wall -Wextra -std=c++11

mazeSolver: main.o Maze.o Solver.o Position.o
	${CXX} ${CXXFLAGS} -o mazeSolver main.o Maze.o Solver.o Position.o

# Because of our general "how to make a .o file" rule below, 
# we can just list the dependencies here.
# Notice what depends on what.
main.o:     main.cpp Maze.h Position.h
Position.o: Position.cpp Position.h
Maze.o:     Maze.cpp Maze.h Position.h
Solver.o:   Solver.cpp Solver.h Maze.h Position.h

# The following rule is very general:
# it means "if you need a .o file (%.o) and you have a .cpp file 
# with the same base name (%.cpp), then you make the .o file by
# compiling with that .cpp file with the flags defined above."  
# $@ means "the target you're trying to make"
# $< means "the first prerequisite"
%.o:  %.cpp
	${CXX} ${CXXFLAGS} -c -o $@ $<

clean:
	rm -f mazeSolver *.o