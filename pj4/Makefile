###
### Makefile for Gerp Project
###
### Author:  Jack Craig, Clark Morris

## 
## Build up your Makefile in a similar manner as for Zap. Feel free 
## to use that Makefile to guide you! Note, you do NOT need rules for
## FSTree.o and DirNode.o as those (pre-compiled) object files are 
## provided to you.
## 
## At the end, you can delete this comment!
## 

##
## Here is a special rule that removes all .o files besides the provided ones 
## (DirNode.o and FSTree.o), all temporary files (ending with ~), and 
## a.out produced by running unit_test. First, we find all .o files 
## that are not provided files, then we run rm -f on each found file 
## using the -exec find flag. Second, we delete the temporary files
## and a.out. @ is used to suppress stdout.
## 
## You do not need to modify or further comment this rule!
##

###
### Makefile for Gerp Project
###
### Authors: Jack Craig, Clark Morris

CXX      = clang++
# CXXFLAGS = -g3 -std=c++11 -Wall -Wextra -Wpedantic -Wshadow -I.
# LDFLAGS  = -g3
CXXFLAGS = -g3 -std=c++11 -Wall -Wextra -Wpedantic -Wshadow -I. -pthread
LDFLAGS = -pthread

# Build targets
all: gerp unit_test

# gerp: main.o gerp.o index.o processing.o FSTree.o DirNode.o
# 	$(CXX) $(LDFLAGS) $^ -o $@
gerp: main.o gerp.o index.o processing.o FSTree.o DirNode.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

# Object file rules
main.o: main.cpp gerp.h
	$(CXX) $(CXXFLAGS) -c $<

gerp.o: gerp.cpp gerp.h index.h
	$(CXX) $(CXXFLAGS) -c $<

index.o: index.cpp index.h line_entry.h
	$(CXX) $(CXXFLAGS) -c $<

processing.o: processing.cpp processing.h FSTree.h DirNode.h
	$(CXX) $(CXXFLAGS) -c $<

# Unit test executable
# unit_test: unit_test_driver.o processing.o FSTree.o DirNode.o gerp.o index.o 
# 	$(CXX) $(LDFLAGS) $^
unit_test: unit_test_driver.o processing.o FSTree.o DirNode.o gerp.o index.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^

# Unit test driver
unit_test_driver.o: unit_test_driver.cpp unit_tests.h
	$(CXX) $(CXXFLAGS) -c $<


# Clean rule (preserves FSTree.o and DirNode.o)
clean:
	@find . -type f \( \
		-name '*.o' ! -name 'FSTree.o' ! -name 'DirNode.o' \
		\) -exec rm -f {} \;
	@rm -f *~ a.out

