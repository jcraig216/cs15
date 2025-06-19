#
# Makefile
# CS15 Lab07: AVL Trees
#		
# Makefile for Lab 7 on AVL Trees, which creates the executable 'avl_trees'. 
#
#	2024-03-4 Modified by Skylar Gilfeather
#		  Changed executable name from 'lab' to 'avl_trees'
#

CXX      = clang++
CXXFLAGS = -g -Wall -Wextra
LDFLAGS  = -g

avl_trees: main.o AVLTree.o pretty_print.o
	${CXX} ${LDFLAGS} -o avl_trees main.o AVLTree.o pretty_print.o

main.o:          main.cpp AVLTree.h 
AVLTree.o:       AVLTree.cpp AVLTree.h
pretty_print.o:  pretty_print.cpp AVLTree.h

clean:
	rm -rf avl_trees *.o *.dSYM
