###
### Makefile for Zap Project
###
### Author: Jack Craig

##
## Add your compiler, compiler flags variables here (e.g. CXX, CXXFLAGS).
## Use previous Makefiles as examples!
##
## At the end, you can delete this comment!
##

## 
## Add your compilation and linking rules here! You can use previous 
## Makefiles as examples, and you can refer to the "make" documentation
## on the course reference page. Note, you do NOT need rules for
## HuffmanTreeNode.o and ZapUtil.o as those (pre-compiled) 
## object files are provided to you.
##
## To start, we recommend you add rules to make executables from
## minpq_example.cpp and ZapUtilExample.cpp. First, you should compile
## these into their respective object files. Look in these files to
## identify the appropriate headers. For the minpq_example executable 
## you should link minpq_example.o and HuffmanTreeNode.o. For the
## ZapUtilExample executable you should link ZapUtilExample.o,
## ZapUtil.o, and HuffmanTreeNode.o. 
## 
## After that, you should go ahead and make the necessary rules to
## produce the zap executable. 
## 
## At the end, you can delete this comment block! 
## 

##
## Here is a special rule that removes all .o files besides the provided ones 
## (ZapUtil.o and HuffmanTreeNode.o), all temporary files 
## (ending with ~), and a.out produced by running unit_test. First, we find
## all .o files that are not provided files, then we run rm -f on each found
## file using the -exec find flag. Second, we delete the temporary files
## and a.out. @ is used to suppress stdout.
## 

#########################################################
#                   Zap Project - Phase 2               #
#########################################################

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow -I .
LDFLAGS  = -g3

# Build targets
all: zap unit_test

# Main executable
zap: main.o HuffmanCoder.o phaseOne.o HuffmanTreeNode.o ZapUtil.o
	$(CXX) $(LDFLAGS) $^ -o $@

# Unit test (Phase 1)
unit_test: unit_test_driver.o phaseOne.o HuffmanCoder.o HuffmanTreeNode.o ZapUtil.o
	$(CXX) $(LDFLAGS) $^
	
unit_test_driver.o: unit_test_driver.cpp unit_tests.h
	$(CXX) $(CXXFLAGS) -c unit_test_driver.cpp

# Object files
main.o: main.cpp HuffmanCoder.h
	$(CXX) $(CXXFLAGS) -c $<

HuffmanCoder.o: HuffmanCoder.cpp HuffmanCoder.h
	$(CXX) $(CXXFLAGS) -c $<

phaseOne.o: phaseOne.cpp phaseOne.h HuffmanTreeNode.h
	$(CXX) $(CXXFLAGS) -c $<



## You do not need to modify or further comment this rule!
##
clean:
	@find . -type f \( \
		-name '*.o' ! -name 'HuffmanTreeNode.o' \
		! -name 'ZapUtil.o' \) -exec rm -f {} \;
	@rm -f *~ a.out

