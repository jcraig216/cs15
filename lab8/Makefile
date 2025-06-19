#
# Makefile for Hashing Lab
#
CXX      = clang++
CXXFLAGS = -g -Wall -Wextra -std=c++11
LDFLAGS  = -g

## If you want to learn more about Makefiles:
##
## A makefile rule has a TARGET, a colon, and a list of PREREQUISITES
## on the first line.  That is followed by 0 or more TAB-indented
## lines that form the RECIPE for building the target from the
## prerequesites. 
##
## make has some built-in variables for very common items.  $@ means
## the name of the target (funkey in the rule below).  $^ means the
## whole prerequisite list, (main.o FunkeyTable.o in the rule below).
## $< means the first prerequisite (it's not used here).
##

funkey: main.o FunkeyChainingTable.o FunkeyLinearTable.o
	${CXX} ${CXXFLAGS} -o $@ $^

main.o: main.cpp FunkeyChainingTable.h FunkeyLinearTable.h

FunkeyChainingTable.o: FunkeyChainingTable.cpp FunkeyChainingTable.h

FunkeyLinearTable.o: FunkeyLinearTable.cpp FunkeyLinearTable.h

clean:
	rm -rf funkey *.o *.dSYM *~

