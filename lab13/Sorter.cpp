/*
 * Sorter.cpp
 *
 * Implementation of the sorter class
 *
 * Edited: John Cha (jcha04) 4/21/2024
 *         - created file
 *         - update function contracts and rearranged file to be more intuitive
 *
 */

#include "Sorter.h"

using namespace std;

/* default constructor
 *    Purpose: default constructor for the Sorter class
 * Parameters: none
 *    Returns: None (constructor)
 */
Sorter::Sorter()
{
    /* This is needed, as otherwise my compiler gets mad :( */
    /* By default, private member variables resort to their own default
       constructors. */
}

/* Parameterized constructor
 *    Purpose: initializes member variable data to input data, and which_algo
 *             to the appropriate sorting algorithm.
 * Parameters: Data vector of ints and a string denoting what sorting algorithm
 *             to use.
 *    Returns: None (constructor)
 *
 *       Note: Aborts with EXIT_FAILURE if specified sorting algorithm is not
 *             supported.
 */
Sorter::Sorter(std::vector<int> input_data, std::string sort_algo)
{
    data = input_data;
    for (size_t i = 0; i < NUM_ALGOS; i++)
    {
        if (sort_algo == supported_algos[i])
        {
            which_algo = sort_algo;
            return;
        }
    }
    /* If, for some reason, a non-supported algorithm is tossed at us, exit
        with an appropriate error message */
    cerr << "ERROR: PROVIDED ALGORITHM IS NOT SUPPORTED" << endl;
    exit(EXIT_FAILURE);
}

/* destructor
 *    Purpose: Destroys any heap-allocated memory (there is none)
 * Parameters: None
 *    Returns: None (destructor)
 */
Sorter::~Sorter()
{
    /* Nothing to do heree.... */
}

/*************************************************************************/
/***                         SORTING FUNCTIONS                         ***/
/***             Sorting algorithms appear below this point            ***/
/***         You should not need to edit functions above this.         ***/
/*************************************************************************/

/* insertionPlace
 *    Purpose: Sorts member variable data by repeatedly inserting successive
 *             elements of data into the already sorted first part of the list.
 *             In place.
 * Parameters: none
 *    Returns: none
 */
void Sorter::insertionPlace()
{
    for (size_t i = 1; i < data.size(); ++i)
    {
        int key = data[i];
        int j = i - 1;
        while (j >= 0 && data[j] > key)
        {
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = key;
    }
}

/* quicksort
 *    Purpose: Sorts member variable data by quicksort. Partitions data around
 *             a pivot value, and recurses down until all sublists are sorted.
 * Parameters: none
 *    Returns: none
 */
void Sorter::quicksort()
{
    int size = data.size();

    /* lists of size 0 and 1 are already sorted, so we only sort if
       we're bigger */
    if (size > 1)
        quicksortHelper(0, size - 1);
}

/* quicksortHelper
 *    Purpose: Recursive helper of quicksort that actually partitions and
 *             recurses on sublists.
 * Parameters: left value which is the starting
 *             of a current subarray, and right value which is
 *             the ending index of our current subarray
 *    Returns: void
 */
void Sorter::quicksortHelper(int left, int right)
{
    if (left < right)
    {
        int pivotIndex = partition(left, right);
        quicksortHelper(left, pivotIndex - 1);
        quicksortHelper(pivotIndex + 1, right);
    }
}

/* partition
 *    Purpose: Partitions range of data[left, right] around a pivot such that
 *             all elements to the left of the pivot index will be less than
 *             the pivot value, and all elems to the right will be greater
 *             than the pivot value.
 * Parameters: left value which is the starting
 *             of a current subarray, and right value which is
 *             the ending index of our currect subarray
 *    Returns: the index of the pivot.
 */
int Sorter::partition(int left, int right)
{
    int pivot = data[left];
    int storeIndex = left + 1;
    for (int j = left + 1; j <= right; j++)
    {
        if (data[j] < pivot)
        {
            swap(data[j], data[storeIndex]);
            storeIndex++;
        }
    }
    swap(data[left], data[storeIndex - 1]);
    return storeIndex - 1;
}

/* selectionAux
 *    Purpose: Uses selection sort to sort member variable data. Repeatedly
 *             selects (get it?) the next largest element and appends it to
 *             an auxillary list.
 * Parameters: None
 *    Returns: void
 */
void Sorter::selectionAux()
{
    size_t size = data.size();
    vector<int> sortedData(size);

    for (size_t i = 0; i < size; i++)
    {
        /* Declare variables to track what the
           current largest value is */
        int largest = data[i];
        size_t largest_index = i;

        for (size_t j = 0; j < size; j++)
        {
            /* Find the current largest and store index */
            if (data[j] > largest)
            {
                largest = data[j];
                largest_index = j;
            }
        }
        /* Place largest into sortedData array from the end
          and continue inserting to the left until we get
          to the smallest value */
        sortedData[(size - i) - 1] = data[largest_index];
        data[largest_index] = -99999;
    }

    /* deep copy FTW */
    data = sortedData;
}

/* selectionPlace
 *    Purpose: Uses in place selection sort to sort member variable data.
 *             Repeatedly selects (get it?) the next smallest element and
 *             adds it to its proper place.
 * Parameters: None
 *    Returns: void
 */
void Sorter::selectionPlace()
{
    size_t size = data.size();

    for (size_t i = 0; i < size; i++)
    {
        swap(data[i], data[indexOfMin(i, size)]);
    }
}

/* indexOfMin
 *    Purpose: finds minimum value in data[from, to] and returns its index
 * Parameters: 2 size_t's, one denoting the starting range of data and
 *             the other the ending index of that range.
 *    Returns: size_t denoting the index of min in the range.
 */
size_t Sorter::indexOfMin(size_t from, size_t to)
{
    size_t result = from;

    for (size_t i = from + 1; i < to; ++i)
    {
        if (data[i] < data[result])
            result = i;
    }

    return result;
}

/*************************************************************************/
/***                                                                   ***/
/***                       JUST FOR FUN EXERCISES                      ***/
/***                                                                   ***/
/*************************************************************************/

/* insertionAux
 *    Purpose: Sorts member variable data by repeatedly inserting successive
 *             elements of data into an already sorted auxillary list.
 * Parameters: none
 *    Returns: none
 */
void Sorter::insertionAux()
{
    std::vector<int> sorted;

    for (int val : data)
    {
        auto it = sorted.begin();
        while (it != sorted.end() && *it < val)
        {
            ++it;
        }
        sorted.insert(it, val);
    }

    data = sorted;
}

/* mergesort
 *    Purpose: Sorts data by cutting the array in half at the midpoint
 *             recursively sorts left and right subarrays
 *             merges the results back together. Calls Merge Sort helper
 * Parameters: none
 *    Returns: none
 */
void Sorter::mergesort()
{

    /* lists of size 0 and 1 are already sorted */
    if (data.size() > 1)
        mergesortHelper(0, data.size() - 1);
}

/* mergesortHelper
 *    Purpose: Helper function for merge sort which appropriately recurses
 *             on subarrays and merges sub lists.
 * Parameters: int left denoting left of current sublist, int right denoting
 *             right bound of current sublist.
 *    Returns: none
 */
void Sorter::mergesortHelper(int left, int right)
{
    if (left < right)
    {
        int splitIndex = (left + right) / 2;
        /* Recurse on left subarray, and then the right subarray */
        mergesortHelper(left, splitIndex);
        mergesortHelper(splitIndex + 1, right);
        merge(left, right, splitIndex);
    }
}

/* merge
 *    Purpose: Merges sorted sublists of data[left, split] and
 *             data[right, split] and stores the result in data[left, right]
 * Parameters: ints denoting the left range of sublist, split, and right
 *    Returns: none
 */
void Sorter::merge(int left, int right, int split)
{
    std::vector<int> merged;
    int i = left;
    int j = split + 1;

    while (i <= split && j <= right)
    {
        if (data[i] <= data[j])
        {
            merged.push_back(data[i]);
            ++i;
        }
        else
        {
            merged.push_back(data[j]);
            ++j;
        }
    }

    while (i <= split)
    {
        merged.push_back(data[i]);
        ++i;
    }

    while (j <= right)
    {
        merged.push_back(data[j]);
        ++j;
    }

    for (int k = 0; k < static_cast<int>(merged.size()); ++k)
    {
        data[left + k] = merged[k];
    }
}

/*************************************************************************/
/***                                                                   ***/
/***                          HELPER FUNCTIONS                         ***/
/***         You should not need to edit functions below this.         ***/
/*************************************************************************/

/* run_algorithm
 *    Purpose: runs the associated algorithm as specified by the which_algo
 *             member variable. Sorts member variable data
 * Parameters: None.
 *    Returns: chrono::duration<double> denoting how much time the
 *             sorting algorithm took.
 *
 *       Note: Aborts with exit failure and appropriate error message if
 *             which_algo is not one of the supported ones.
 */
chrono::duration<double> Sorter::run_algorithm()
{
    chrono::time_point<chrono::system_clock> start = chrono::system_clock::now();

    if (which_algo == "insertionAux")
    {
        insertionAux();
    }
    else if (which_algo == "insertionPlace")
    {
        insertionPlace();
    }
    else if (which_algo == "selectionAux")
    {
        selectionAux();
    }
    else if (which_algo == "selectionPlace")
    {
        selectionPlace();
    }
    else if (which_algo == "mergesort")
    {
        mergesort();
    }
    else if (which_algo == "quicksort")
    {
        quicksort();
    }
    else
    {
        cerr << "ERROR: Running non-supported algorithm" << endl;
        exit(EXIT_FAILURE);
    }

    chrono::time_point<chrono::system_clock> end = chrono::system_clock::now();
    return end - start;
}

/* is_sorted
 *    Purpose: checks if member variable data is sorted, i.e., in ascending
 *             (or, technically, non-descending) order.
 * Parameters: None.
 *    Returns: bool denoting sortedness.
 */
bool Sorter::is_sorted()
{
    size_t size = data.size();

    /* lists of size 1 or 0 are already sorted. */
    if (size < 2)
        return true;

    for (size_t i = 0; i < size - 1; i++)
    {
        if (data[i] > data[i + 1])
            return false;
    }
    return true;
}

/* print_vector
 *    Purpose: Prints out the contents of member variable data to cout.
 * Parameters: None.
 *    Returns: void
 */
void Sorter::print_vector()
{
    size_t size = data.size();

    cout << "Vector of " << size << " elements:" << endl
         << "[";

    for (size_t i = 0; i < size; ++i)
    {
        cout << data[i];
        if (i != size - 1)
            cout << ", ";
    }
    cout << "]" << endl;
};