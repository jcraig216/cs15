#
# Makefile for CS15 Lab 06: Tree Traversals
#
CXX      = clang++
CXXFLAGS = -Wall -Wextra -Wconversion -Wreturn-type -g
LDFLAGS  = -g

tree_traversal: main.o BTree.o
	${CXX} ${LDFLAGS} -o tree_traversal  main.o BTree.o

main.o:    main.cpp BTree.h
BTree.o:  BTree.cpp BTree.h

clean:
	rm -rf tree_traversal *.o *~ *.dSYM

