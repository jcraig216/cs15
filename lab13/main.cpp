
/*
 * Filename: main.cpp
 * Part of: Lab assignment "Sorting" for COMP 15 Spring 2020
 *
 * Sort a list of numbers with specified algorithm and print time
 *
 * Usage:  sort -r NumValues Algorithm [-debug]
 *         sort -f DataFile  Algorithm [-debug]
 *
 *      -r means to sort a random list of integers of size NumValues
 *      -f means to sort a list of integers read from the given file
 *         A filename of - means read from standard input
 *      -h prints usage message followed by supported algorithms
 *      -debug causes the initial list to print before sorting
 *         and the sorted list to print afterwards
 *
 * Contains: command line parsing functions.
 *
 * NOTE TO STUDENTS: You should ** not ** have to modify any line in this file. 
 * For the lab, you should *only* modify things in the sorting.cpp file
 *
 * Edited: John Cha (jcha04) 4/19/2024
 *         - created the file, modified command_line_args, modularized code 
 *         - updated and made function contracts more consistent.
 *
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <tuple>
#include <chrono>
#include <climits>

#include "Sorter.h"

using namespace std;

tuple<string, bool> command_line_args (int argc, char *argv[], 
                                       vector<int> &data);

/* Helper functions associated with command_line_args() */
void      help_message          ();
void      print_algorithms      (ostream &out);
void      abort_with            (string message);
bool      got_int               (string s, int &result);
int       size_t2int            (size_t val);
void      handle_random         (vector<int> &data, string possible_num_values);
bool      handle_debug          (string arg);
string    check_valid_algorithm (string arg);
void      populate_from_file    (vector<int> &data, string filename);
ifstream &open_or_die           (ifstream &stream, string filename);


/* Helpful constants */
const int MAX_SIZE = INT_MAX;
const int RANGE    = 10000;

const string PROG_NAME = "./sort";
const string USAGE = 
    "Usage:  " + PROG_NAME + " -r NumElements Algorithm [-debug]\n"
               + "\t" + PROG_NAME + " -f FileName    Algorithm [-debug]\n"
               + "\t" + PROG_NAME + " -h\n"
               + "\twhere num_elements in [0 .. "
               + to_string(MAX_SIZE) + "]\n";

/* main
 *    Purpose: Depending on arguments, sorts a given list of ints and denotes
 *             how much time it takes. Relies on the Sorter Class.
 * Parameters: int denoting the arg count and an array of char* denoting the
 *              arguments.
 *    Returns: An integer denoting success. 
 *       Note: Aborts with help message if command line arguments do not
 *              conform with specified usage.
 */
int main(int argc, char** argv) {

    string      sort_alg;
    bool        debugging;
    vector<int> data;

    tie(sort_alg, debugging) = command_line_args(argc, argv, data);

    Sorter my_Sorter(data, sort_alg);
    if (debugging)
        my_Sorter.print_vector();
    
    chrono::duration<double> elapsed = my_Sorter.run_algorithm();
    cout << "Elapsed time: " << fixed << elapsed.count() << endl;

    cout << "Sort " << (my_Sorter.is_sorted() ? "SUCCESS" : "FAIL");
    cout << endl;

    if (debugging)
        my_Sorter.print_vector();

    return 0;

}

/* command_line_args
 *    Purpose: Processes the command line arguments, and ensures they conform 
 *             with the program's usage. Populates the parameter data with the 
 *             necessary ints, according to the specified way.
 * Parameters: argc and argv from main
 *    Returns: a tuple of a string (denoting the specified sorting algorithm)
 *             and a boolean (denoting whether or not the "debug" setting was 
 *             specified).
 *
 *       Note: Aborts with help message if specified, or if file contents are 
 *             not readable, or if a negative length of a random list is 
 *             specified.
 */
tuple<string, bool> command_line_args(int argc, char *argv[],
                                      vector<int> &data) {
    /* if wrong number of parameters, or if help is requested */
    if (argc < 4 or string(argv[1]) == "-h" or argc > 5) {
        help_message(); 
    }

    bool debugging = false;
    string sort_algorithm = "";
    
    /* we check the validity of the algorithm in our Sorter class. */ 
    sort_algorithm = argv[3];

    /* check for a valid way to generate a list of ints */
    if (string(argv[1]) == "-f") {
        populate_from_file(data, argv[2]);
    } else if (string(argv[1]) == "-r") {
        handle_random(data, argv[2]);
    } else {
        cerr << "ERROR: NO VALID LIST OF INTS GIVEN" << endl;
        exit(EXIT_FAILURE);
    }

    /* If there's a 5th argument, it better be "-debug" */
    if (argc == 5 )
        debugging = handle_debug(argv[4]);

    return make_tuple(sort_algorithm, debugging);
}



/* handle_debug
 *    Purpose: checks to see if the 5th argument on the command line is "-debug"
 *             or not.
 * Parameters: A string denoting the 5th command line argument.
 *    Returns: A bool denoting whether the debug setting will be set
 *
 *       Note: aborts with EXIT_FAILURE if the argument is not "-debug"
 */
bool handle_debug(string arg) {
    if (arg == "-debug") 
        return true;
    cerr << "ERROR: FIFTH ARGUEMENT IS NOT \"-debug\"" << endl;
    exit(EXIT_FAILURE);
    return false;
}

/* populate_randomly
 *    Purpose: generates a bunch of random numbers up to RANGE,
 *             50% chance each value will be negative.
 * Parameters: vector to fill up, desired number of values. number of values 
 *             must be >= 0
 *    Returns: void
 *
 *       Note: Aborts with EXIT_FAILURE if number of values is negative
 */
void handle_random(vector<int> &data, string possible_num_values) {
    /* take the string form of the command and convert into an int */
    int num_values;
    istringstream iss(possible_num_values);
    iss >> num_values;

    if (iss.fail() or num_values < 0) {
        help_message();
    }

    /* generate a bunch of random numbers */
    for (int i = 0; i < num_values; i++) {
        int n = rand() % RANGE;
        if (rand() % 2 == 1)
                n = -n;
        data.push_back(n);
    }
}


/* open_or_die
 *    Purpose: tries to open the ifstream with the associated filename. If there
 *             are issues with opening anything, we shall exit 
 *             with EXIT_FAILURE!
 * Parameters: an argument ifstream reference and a filename
 *    Returns: void
 *
 *       Note: Aborts with EXIT_FAILURE if stream cannot be opened.
 */
ifstream &open_or_die(ifstream &stream, string filename) {
    stream.open(filename);

    if (not stream.is_open()) {
        cerr << "Cannot open file:  " << filename << endl;
        exit(EXIT_FAILURE);
    }
    return stream;
}

/* populate_from_file
 *    Purpose: Populates given vector with given file, or with cin if given
 *             filename is "-"
 * Parameters: a vector of ints to be populated and a filename
 *    Returns: void
 *
 *       Note: Aborts with EXIT_FAILURE if stream cannot be opened.
 */
void populate_from_file(vector<int> &data, string filename) {
    ifstream from_file;

    /* This uses the ternary operator, basically just a shorthand for an 
       if-else statement. */
    istream& input = (filename == "-")
        ? cin
        : open_or_die(from_file, filename);

    /* populate our vector with the specified numbers */
    int n;
    while (not (input >> n).fail())
        data.push_back(n);

    /* ifstreams close automatically when they go out of scope */
}



/* help_message
 *    Purpose: Prints to cerr the usage of the program, supported algorithms,
 *             then exits with EXIT_FAILURE.
 * Parameters: none
 *    Returns: void
 *
 *       Note: Aborts with EXIT_FAILURE.
 */
void help_message() {
    cerr << USAGE << endl;
    cerr << "The following algorithms are supported:" << endl;
    print_algorithms(cerr);
    exit(EXIT_FAILURE);
}

/* print_algorithms
 *    Purpose: Prints to ostream the list of supported algos as specified in
 *             Sorter.h
 * Parameters: ostream
 *    Returns: void
 */
void print_algorithms(ostream &out) {
    for (size_t i = 0; i < NUM_ALGOS; i++) {
        out << "    " << supported_algos[i] << endl;
    }
}