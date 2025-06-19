/*
 * Filename: sorting.cpp
 * Part of: Lab assignment "Sorting" for COMP 15 Spring 2020
 *
 * Sort a list of numbers with specified algorithm and print time
 *
 * Usage:  sort -r NumValues Algorithm [-debug]
 *         sort -f DataFile  Algorithm [-debug]
 *         sort -h
 *
 *      -r means to sort a random list of integers of size NumValues
 *      -f means to sort a list of integers read from the given file
 *         A filename of - means read from standard input
 *      -h prints usage message followed by supported algorithms
 *      -debug causes the initial list to print before sorting
 *         and the sorted list to print afterwards
 *
 * Contains: various sorting algorithm implementations:
 *           insertion sort, selection sort,
 *           selection sort in place, mergesort,
 *           quicksort
 *
 * Sort functions are at the end of the file.  Search for SORTING FUNCTIONS
 *
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <tuple>
#include <limits>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <climits>

using namespace std;

//
// Sorting function prototypes
//
void insertionAux(vector<int> &data);
void insertionPlace(vector<int> &data);
void insertFrom(vector<int> &data, int idx);

void selectionAux(vector<int> &data);
void selectionPlace(vector<int> &data);

void mergesort(vector<int> &data);
void mergesortHelper(vector<int> &data, int left, int right);
void merge(vector<int> &data, int left, int right, int split);

void quicksort(vector<int> &data);
void quicksortHelper(vector<int> &data, int left, int right);
int partition(vector<int> &data, int left, int right);

//
// Helper functions
//
template <typename T>
void print_vector(vector<T> v);
template <typename T>
bool is_sorted(vector<T> data);

tuple<string, bool> command_line_args(int argc, char *argv[],
                                      vector<int> &data);
chrono::duration<double> run_algorithm(string algorithm, vector<int> &data);
void print_algorithms(ostream &out);
string usage(string progname);
void abort_with(string message);
bool got_int(string s, int &result);
int size_t2int(size_t val);
void populate_randomly(vector<int> &data, int num_values);
void populate_from_file(vector<int> &data, string filename);
ifstream &open_or_die(ifstream &stream, string filename);

const int MAX_SIZE = INT_MAX;
const int RANGE = 10000;

/*
 * A global table that maps algorithm names to pointers to corresponding
 * functions.
 *
 * To add new functions, just define those functions and make entries
 * to this table before the sentinal (last) line.
 */

static const string NO_NAME = "";
static void (*const NO_FUNC)(vector<int> &data) = nullptr;

static const struct
{
        string function_name;
        void (*function)(vector<int> &data);
} algorithm_table[] = {
    {"insertionAux", insertionAux},
    {"insertionPlace", insertionPlace},
    {"selectionAux", selectionAux},
    {"selectionPlace", selectionPlace},
    {"mergesort", mergesort},
    {"quicksort", quicksort},
    {NO_NAME, NO_FUNC}};

int main(int argc, char *argv[])
{
        string sort_alg;
        bool debugging;
        vector<int> data;

        tie(sort_alg, debugging) = command_line_args(argc, argv, data);

        if (debugging)
                print_vector(data);

        chrono::duration<double> elapsed = run_algorithm(sort_alg, data);
        cout << "Elapsed time: " << fixed << elapsed.count() << endl;

        cout << "Sort " << (is_sorted(data) ? "SUCCESS" : "FAIL")
             << endl;

        if (debugging)
                print_vector(data);

        return 0;
}

//
// process the command line arguments
//
// Returns:  Tuple with algorithm name
//           and a boolean indicated whether debug mode is on or off
// Effects:  Populates the data vector with either random integers or
//           integers from
// Aborts with usage message if command line arguments are not valid
// Aborts with message if file contents are not readable
//
// NEEDSWORK:  This function is too long
//
tuple<string, bool> command_line_args(int argc, char *argv[],
                                      vector<int> &data)
{
        string program_name = argv[0];
        bool debugging = false;
        ;
        string sort_algorithm;

        if (argc > 1 and string(argv[1]) == "-h")
        {
                cerr << usage(program_name) << endl
                     << "The following algorithms are supported:" << endl;
                print_algorithms(cerr);
                exit(EXIT_SUCCESS);
        }
        if (argc < 4 or argc > 5)
                abort_with(usage(program_name));
        sort_algorithm = argv[3];

        if (argc == 5)
        {
                if (string(argv[4]) == string("-debug"))
                        debugging = true;
                else
                        abort_with(usage(program_name));
        }
        if (string(argv[1]) == string("-r"))
        {
                int num_vals;
                if (got_int(argv[2], num_vals) and num_vals >= 0)
                        populate_randomly(data, num_vals);
                else
                        abort_with(usage(program_name));
        }
        else if (string(argv[1]) == string("-f"))
        {
                populate_from_file(data, argv[2]);
        }
        return make_tuple(sort_algorithm, debugging);
}

//
// Function:  populate_ramdonmly
// Args:      vector to fill up, desired number of values
//            number of values must be >= 0
// Returns:   void
// Purpose:   generates a bunch of random numbers up to RANGE,
//            50% chance each value will be negative
//
void populate_randomly(vector<int> &data, int num_values)
{
        for (; num_values > 0; --num_values)
        {
                int n = rand() % RANGE;
                if (rand() % 2 == 1)
                        n = -n;
                data.push_back(n);
        }
}

//
// Try to open stream with filename
// Exit program with message on failure
//
ifstream &open_or_die(ifstream &stream, string filename)
{
        stream.open(filename);

        if (not stream.is_open())
                abort_with("Cannot open file:  " + filename);

        return stream;
}

//
// File data with (white space separated) integers read from filename
// A filename of "-" means to read from standard input (cin)
//
void populate_from_file(vector<int> &data, string filename)
{
        ifstream from_file;

        istream &input =
            (filename == "-") ? cin
                              : open_or_die(from_file, filename);
        int n;
        while (not(input >> n).fail())
                data.push_back(n);

        // ifstreams close automatically when they go out of scope
}

//
// Return a usage message with embedded program name
//
string usage(string progname)
{
        return "Usage:  " + progname + " -r NumElements Algorithm [-debug]\n" + "        " + progname + " -f FileName    Algorithm [-debug]\n" + "        " + progname + " -h\n" + "     where num_elements in [0 .. " + to_string(MAX_SIZE) + "]\n";
}

//
// Abort the program after printing message to standard error
//
void abort_with(string message)
{
        cerr << message << endl;
        exit(EXIT_FAILURE);
}

//
// Attempt to parse an integer from the s
// If successful, store resutl and return true
// Otherwise return false and leave result unchanged
//
bool got_int(string s, int &result)
{
        istringstream iss(s);

        iss >> result;

        return not iss.fail();
}

//
// Convert a size_t value to an equivalent int
// Aborts the program with an error message if the int
// would overflow
//
int size_t2int(size_t val)
{
        if (val > numeric_limits<int>::max())
                abort_with("size_t not representable in an int:  " + to_string(val));
        return static_cast<int>(val);
}

//
// Function:  is_sorted
// Input:     vector of comparable values
// Returns:   true if array is sorted, false otherwise
// Notes:     iterates through the array, comparing each number
//            to the number after it, ensuring the values are
//            monotonically increasing. Returns true if sorted
//
template <typename T>
bool is_sorted(vector<T> data)
{
        size_t size = data.size();

        if (size < 2)
                return true;

        for (size_t i = 0; i < size - 1; i++)
        {
                if (data[i] > data[i + 1])
                        return false;
        }
        return true;
}

//
// Print the size and contents of a vector on standard output (cout)
//
template <typename T>
void print_vector(vector<T> v)
{
        size_t size = v.size();

        cout << "Vector of " << size << " elements:" << endl
             << "[";

        for (size_t i = 0; i < size; ++i)
        {
                cout << v[i];
                if (i != size - 1)
                        cout << ", ";
        }
        cout << "]" << endl;
}

//
// Runs the given algorithm and returns the elapsed wall-clock time
// Aborts program with an error message if the algorithm is not found
//
chrono::duration<double> run_algorithm(string algorithm, vector<int> &data)
{
        // Search for the algorithm in the table
        int i;
        for (i = 0; algorithm_table[i].function_name != NO_NAME and algorithm_table[i].function_name != algorithm; ++i)
                ;

        // If we found the command, run it, otherwise, complain
        if (algorithm_table[i].function == NO_FUNC)
                abort_with("Unknown sorting algorithm: " + algorithm);

        auto start = chrono::system_clock::now();
        algorithm_table[i].function(data);
        auto end = chrono::system_clock::now();
        return end - start;
}

//
// Print out the supported algorithms from the algorithms table
//
void print_algorithms(ostream &out)
{
        for (int i = 0; algorithm_table[i].function_name != NO_NAME; ++i)
                out << "    " << algorithm_table[i].function_name << endl;
}

/*************************************************************************/
/***                         SORTING FUNCTIONS                         ***/
/***             Sort algorithms appear below this point               ***/
/***         You should not need to edit functions above this.         ***/
/*************************************************************************/

//
// Function:  insertFrom
// Purpose:   insert the element at idx-th position into the
//            sorted list in positions [0..idx)
// Args:      vector of integers, index of element to insert
//            Requires idx >= 0
//
void insertFrom(vector<int> &data, int idx)
{
        // TODO (optional, but recommended)
}

//
// Function:  insertion sort, in place
// Input:     vector of ints to be sorted
// Returns:   void
//
// Does:  Repeatedly chooses the next element
//        and places it into its correct position
//
void insertionPlace(vector<int> &data)
{
        // TODO
}

//
// Return index in the smallest value in values at indices in [from, to)
// Assumes interval is non-empty, i. e., to - from >= 1
//
size_t indexOfMin(vector<int> &values, size_t from, size_t to)
{
        size_t result = from;

        for (size_t i = from + 1; i < to; ++i)
                if (values[i] < values[result])
                        result = i;
        return result;
}

//
// Function: selection sort, in place
// Input: vector of ints
// Returns: void
// Does:  Leaves values array sorted
// Notes: Elements left of current index are sorted, to the right are unsorted
//        For each slot in values, find smallest remaining element to right
//        and swap that element into the slot
//
void selectionPlace(vector<int> &values)
{
        size_t size = values.size();

        for (size_t i = 0; i < size; ++i)
                swap(values[i],
                     values[indexOfMin(values, i, size)]);
}

// Calls mergesort helper function
void mergesort(vector<int> &data)
{
        // lists of size 0 and 1 are already sorted
        if (data.size() > 1)
                mergesortHelper(data, 0, size_t2int(data.size()) - 1);
}

//
// Function:  mergesort
// Input:     vector of ints, left is the start current subarray,
//            and right value which is end of current subarray
// Returns:   void
//
// Does: Cuts the array in half at the midpoint
//       recursively sorts left and right subarrays
//       merges the results back together
//
void mergesortHelper(vector<int> &data, int left, int right)
{
        if (left < right)
        {
                int splitIndex = (left + right) / 2;

                // Recurse on left subarray, and then the right subarray
                mergesortHelper(data, left, splitIndex);
                mergesortHelper(data, splitIndex + 1, right);
                merge(data, left, right, splitIndex);
        }
}

//
// Function: merge
// Helper function for mergesort
// Merges two already-sorted lists
//
void merge(vector<int> &data, int left, int right, int split)
{
        // TODO
}

// Calls quicksort helper function
void quicksort(vector<int> &data)
{
        // TODO
}

// Function: partition
// Input: array of ints, left value which is the starting
//        of a current subarray, and right value which is
//        the ending index of our currect subarray
// Returns: an integer that represents the pivot of the array
// Does: Takes the last element as the pivot and partitions
//       all elements smaller than it to the left, and all
//       elements greater than it to the right, then returns
//       the final position of the pivot
int partition(vector<int> &data, int left, int right)
{
        // TODO
}

//
// Function: insertion sort with auxiliary array
// Args:     vector of ints to be sorted
// Returns:  void
//
// Does: Repeatedly finds the next smallest element
//       and places it into its correct position in
//       the aux array
//
void insertionAux(vector<int> &data)
{
        // TODO
}

//
// Function:  selection sort, auxiliary list
// Input:     vector of ints to sort
// Returns:   void
//
// Does:  Finds next largest element from unsorted array
//        to put in sorted output array
//
// Can you refactor this?
//
void selectionAux(vector<int> &data)
{
        size_t size = data.size();
        vector<int> sortedData(size);

        for (size_t i = 0; i < size; i++)
        {
                // Declare variables to track what the
                // current largest value is
                int largest = data[i];
                size_t largest_index = i;

                for (size_t j = 0; j < size; j++)
                {
                        // Find the current largest and store index
                        if (data[j] > largest)
                        {
                                largest = data[j];
                                largest_index = j;
                        }
                }
                // Place largest into sortedData array from the end
                // and continue inserting to the left until we get
                // to the smallest value
                sortedData[(size - i) - 1] = data[largest_index];
                data[largest_index] = -99999;
        }

        // Copy over contents back to data array
        for (size_t i = 0; i < size; i++)
                data[i] = sortedData[i];
}
