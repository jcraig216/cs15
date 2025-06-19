/*
 * CS15:  Heaps
 *
 * Uses a Heap to sort an array of strings.
 * 
 *      Edited by: Kathy Quintanilla, November 2024
 *                 updated function contracts and style
 */

#include <iostream>

#include "heap.h"

using namespace std;

/*
 * Name:      heapSort(string list[], int size)
 * Purpose:   Sorts a given array using a min heap
 * Arguments: string [] -- an array of strings that holds the elements to be 
 *                         sorted
 *            int       -- the size of the string array
 * Returns:   None
 */
void heapSort(string list[], int size) {
    string* temp;
    temp = new string[size];

    /* Make a heap from the original list */
    Heap h(list, size);

    /* Copy the sorted version into a temp list */
    for (int i = 0; i < size; i++) {
        temp[i] = h.removeMin();
    }

    /* 
     * Copy back into orginal list
     * Note: this is not space efficient as it uses a second array --- a third 
     * if you count the heap!
     */
    for (int j = 0; j < size; j++) {
        list[j] = temp[j];
    }

    delete[] temp;
}


/*
 * Name:      main()
 * Purpose:   Drives program to sort an array of strings using a min heap
 * Arguments: None
 * Returns:   None
 */
int main() {
    string testList[] = {
        "comparison",  "fashion", "make",     "prom,",       "beyond",
        "extravagant", "her",     "deserves", "invitation,", "rachel?",
        "for",         "night:",  "my",       "a",           "beauty"};
    int size = sizeof(testList) / sizeof(string);

    heapSort(testList, size);

    cout << " Words in the list should be in"
         << " lexicographic (dictionary) order:" << endl
         << endl;

    for (int i = 0; i < size; i++) {
        cout << testList[i] << " ";
    }
    cout << endl;

    return 0;
}
