#
# Makefile for Graph Traversals Lab
# 

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -std=c++14
INCLUDES = $(shell echo *.h)

PathFinder: main.o PathFinder.o Graph.o City.o
		${CXX} -o $@ $^

%.o: %.cpp ${INCLUDES}
		${CXX} ${CXXFLAGS} -c $<

clean:
		rm -rf PathFinder *.o *.dSYM
