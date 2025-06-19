#
########  Makefile for pokedex  ########
#

#
#  We'll first define some variables! When we define a variable with name
#  NAME, the Makefile replaces ${NAME} with the value of NAME in the
#  command that it runs.  
#

# 
#  CXX is conventionally used for the C++ compiler you want to use.  
#  We'll use clang++ in Comp 15, because it tends to have better error
#  messages than the alternative (g++).  CPP wasn't used for C++, because
#  it was already in use for something else when C++ was invented.
#

#
#  CXXFLAGS is conventionally used for the parameters (flags) you want 
#  to use whenever you compile a C++ program.  In this case, we're
#  telling the compiler to leave all the debugging information it can
#  in the resulting file (g3), to give us all the standard warnings
#  (Wall), and to give us even MORE warnings (Wextra).
#

#
#  LDFLAGS is conventionally used for the parameters (flags) you want
#  to use when you link a bunch of program components together to make
#  an executable program.  In this case, we're asking for all the
#  debugging information again.
#
CXX      = clang++
CXXFLAGS = -g3 -std=c++11 -Wall -Wextra 
LDFLAGS  = -g3

########  A Makefile Review  ########

#  
#  Recall from Lab 3 that each Makefile 'rule' is a shortcut for a command
#  that you can run in your terminal. Makefile rules have the following
#  format (COMMAND must be indendented with a tab character!):
#
#      TARGET: DEPENDENCIES
#           COMMAND
#
#  By running "make ITEM", your Makefile performs three steps in order to
#  create ITEM:
#
#  1. Jumps to the rule with the TARGET name ITEM in the Makefile. If no
#     rule with this target name exists, you'll get the following error:
#	      "make: *** No rule to make target `ITEM`. Stop."
#
#  2. Then, it checks DEPENDENCIES, a list of space-separated file names.
#     When you list files in DEPENDENCIES, you indicate to the Makefile that
#	  these files are required in order to run the COMMAND below.
#
#     For any of the files in DEPENDENCIES that don't exist, e.g. FILE.O, the
#     Makefile will try look for other rules with the target name FILE.O
#	  in order to create the file. If Makefile can't create the file,
#	  you'll get the following error:
#	      "make: *** No rule to make target `FILE.O', needed by `pokedex'. Stop."
#	  
#	  If any of the files in DEPENDENCIES have changes, your Makefile will
#	  detect it and recompile them! This is the power of Makefiles: you can
#	  recompile only the files that have changed, and wrap them into your
#	  new executable.
#	 
#  3. Finally, the Makefile will run the COMMAND in your terminal! If

#
#  Note: "-o NAME" is an option passed to the command clang++, substituted in
#  as the value for ${CXX}. It takes NAME as an argument, which sets the
#  name of the executable that you're linking together. If no "-o NAME" is
#  given, clang++ names your executable "a.out".
#
pokedex: CircularBuffer.o Stack.o Queue.o main.o 
	${CXX} ${LDFLAGS} -o pokedex CircularBuffer.o Stack.o Queue.o main.o


#  This rule defines how to create CircularBuffer.o!
CircularBuffer.o: CircularBuffer.cpp CircularBuffer.h
	${CXX} ${CXXFLAGS} -c CircularBuffer.cpp


#
#  The following rules don't have recipes. Your Makefile has lots of built-in
#  rules: if you want to build a FILE.o file, and you have a FILE.cpp file,
#  it will compile FILE.cpp into FILE.o for you, using the known variables
#  CXX and CXXFLAGS.
# 
CircularBuffer.o: CircularBuffer.cpp CircularBuffer.h
Stack.o: Stack.cpp Stack.h CircularBuffer.h
Queue.o: Queue.cpp Queue.h CircularBuffer.h
main.o: main.cpp Stack.h Queue.h CircularBuffer.h


#
#  The following is a rule that is necessary to use the unit_test framework.
#  Notice that it must always include the dependency `unit_test_driver.o`.
#  This file will be automatically created for you. It also includes
#  dependencies on all .o files that are used in the tests in unit_tests.h
#
unit_test: unit_test_driver.o CircularBuffer.o Stack.o Queue.o
	$(CXX) $(CXXFLAGS) $^


#
#  The following rules show how you can use make to automate things besides
#  building your program.
#
#  Makefiles traditionally have a "clean" target.  The purpose is to clean
#  up everything that is automatically built by make.  It's useful for when
#  you want to save disk space and also when you've messed things up and
#  just want to rebuild everything from scratch. The clean target doesn't
#  have any dependencies, because you don't need other files in order to
#  clean up!
#
#  .dSYM directories are something that gets make in the Mac
#  environment for debugging data, and so we delete them when cleaning up.
#
clean:
	rm -rf pokedex *.dSYM *.o