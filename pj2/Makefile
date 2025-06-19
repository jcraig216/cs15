#########################################################
#             PROJECT 2: CalcYouLater Makefile         #
#########################################################

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow -I .
LDFLAGS  = -g3

CalcYouLater: main.o DatumStack.o parser.o RPNCalc.o Datum.o
	$(CXX) ${LDFLAGS} $^ -o CalcYouLater

# This rule builds DatumStack.o
DatumStack.o: DatumStack.cpp DatumStack.h Datum.h 
	$(CXX) $(CXXFLAGS) -c DatumStack.cpp

# Datum.o: Datum.cpp Datum.h
# 	$(CXX) $(CXXFLAGS) -c Datum.cpp


# This rule builds parser.o
parser.o: parser.cpp parser.h
	$(CXX) $(CXXFLAGS) -c parser.cpp

# This rule builds RPNCalc
RPNCalc.o: RPNCalc.cpp RPNCalc.h DatumStack.h Datum.h parser.o
	$(CXX) $(CXXFLAGS) -c RPNCalc.cpp

# This rule builds unit_test
unit_test: unit_test_driver.o DatumStack.o Datum.o parser.o RPNCalc.o
	$(CXX) $(CXXFLAGS) $^


unit_test_driver.o: unit_test_driver.cpp unit_tests.h
	$(CXX) $(CXXFLAGS) -c unit_test_driver.cpp


## Rules for building an executable from Datum+vector_example.cpp
## This is useful in seeing the behavior of Datum::toString()
Datum+vector_example.o: Datum+vector_example.cpp Datum.h

Datum+vector_example: Datum+vector_example.o Datum.o
	${CXX} ${LDFLAGS} -o $@ $^


clean:
	@find . -type f \( \
	-name '*.o' ! -name 'Datum.o' \
	\) -exec rm -f {} \;
	@rm -f *~ a.out

##
## Here is a rule for compiling .cyl files for use in your testing
##
%.cylc:  %.cyl
	./cylc $^