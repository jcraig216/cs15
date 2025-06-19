/*
 * CS15 Lab: Heaps
 *
 * Implementation of Heap class with string keys.
 *
 *      Updated 11/2/2020 by Ellis Brown
 *      Updated 3/26/2024 by Chami Lamelas
 *              updated so students' required functions are grouped and ordered
 *              as per spec.
 *      Updated 11/03/2024 by Kathy Quintanilla
 *              updated function contracts and style
 */

#include <iostream>

#include "heap.h"

using namespace std;

/*
 * Name:      Heap()
 * Purpose:   Contructs an instance of the Heap
 * Arguments: None
 * Returns:   None
 * Effects:   Initializes all member variables of the Heap class
 */
Heap::Heap()
{
    heap = new string[INIT_SIZE];
    heapSize = 0;
    maxCapacity = INIT_SIZE;
}

/*
 * Name:      Heap(string list[], int listSize)
 * Purpose:   Contructs an instance of the Heap with a given string array
 * Arguments: string [] -- an array of strings that will be the elements in
 *                         this Heap instance
 *            int       -- size of the given array
 * Returns:   None
 * Effects:   Initializes all member variables of the Heap class and ensures
 *            that the Heap invariants in the given array are established
 */
Heap::Heap(string list[], int listSize)
{
    heap = new string[listSize + 1];
    maxCapacity = listSize + 1;

    /*
     * Remember our implementation of a heap starts at 1, not zero, so we store
     * a nonce value at index 0.
     */
    heap[0] = "I'M NOT PART OF THE HEAP";

    /* Copy the unsorted list over */
    for (int i = 0; i < listSize; i++)
    {
        heap[i + 1] = list[i]; /* Notice indexing */
    }
    heapSize = listSize;

    /* Use the buildHeap() to "heapify" the unsorted array */
    buildHeap();
}

/*
 * Name:      ~Heap()
 * Purpose:   Conducts memory clean up
 * Arguments: None
 * Returns:   None
 * Effects:   Recycles any allocated memory
 */
Heap::~Heap()
{
    delete[] heap;
}

/*
 * Name:      min()
 * Purpose:   Gets the minimum element of the Heap (should be at the top)
 * Arguments: None
 * Returns:   string -- the minimum element of the Heap
 * Effects:   None
 */
string Heap::min()
{
    if (heapSize == 0)
    {
        return "";
    }
    return heap[1];
}

/*
 * Name:      downHeap(int location)
 * Purpose:   Verifies/establishes the heap invariant from given location down
 *            to Heap's leaves
 * Arguments: int -- the location of the string element in the Heap that we
 *                   want to downHeap from
 * Returns:   None
 * Effects:   If the parent is out of order with respect to children, swaps
 *            with smaller child and downHeap from updated child
 */
void Heap::downHeap(int location)
{
    int left = leftChild(location);
    int right = rightChild(location);
    int smallest = location;

    if (left <= heapSize && heap[left] < heap[smallest])
    {
        smallest = left;
    }
    if (right <= heapSize && heap[right] < heap[smallest])
    {
        smallest = right;
    }

    if (smallest != location)
    {
        swap(heap[location], heap[smallest]);
        downHeap(smallest);
    }
}

/*
 * Name:      removeMin()
 * Purpose:   Removes and return smallest element in heap
 * Arguments: None
 * Returns:   string -- the smallest element in the Heap
 * Effects:   Minimum element is removed from the Heap, so function must
 *            reestablish invariants
 */
string Heap::removeMin()
{
    if (heapSize == 0)
    {
        return "";
    }

    string min = heap[1];
    heap[1] = heap[heapSize];
    heapSize--;
    downHeap(1);
    return min;
}

/*
 * Name:      buildHeap()
 * Purpose:   Creates a min Heap out of the unsorted array
 * Arguments: None
 * Returns:   None
 * Effects:   Establishes Heap invariants in an unsorted array
 */
void Heap::buildHeap()
{
    for (int i = heapSize / 2; i >= 1; i--)
    {
        downHeap(i);
    }
}

/*
 * Name:      upHeap(int location)
 * Purpose:   Reestablishes heap invariant from given location to the root of
 *            the Heap
 * Arguments: int -- the location of the string element in the Heap that we
 *                   want to upHeap from
 * Returns:   None
 * Effects:   If child is out of order with respect to parent, swap and
 *            continue to upHeap from parent to root.
 * Other:     NOT required for this lab, but you can write it if you have time.
 */
void Heap::upHeap(int location)
{
    (void)location; /* Removes compiler warning about unused variable. */
}

/*
 * Name:      insert(string s)
 * Purpose:   Inserts a given string s into the heap
 * Arguments: string -- string to be inserted into the heap
 * Returns:   None
 * Effects:   Inserts the string into the Heap and re-establishes Heap
 *            invariants
 * Other:     Requires upHeap() to be completed; Not needed for this lab
 */
void Heap::insert(string s)
{
    /*
     * Remember: We do not use slot zero in the array!
     * Thus, the array is already of size (heapSize + 1), but we want to add
     * one more element, so we need an array of size (heapSize + 2)
     */
    ensureCapacity(heapSize + 2);

    /*
     * First, satisfy the shape invariant:
     *      Location to insert is heapSize + 1
     *      (Recall, 0th location not used)
     */
    heap[heapSize + 1] = s;
    heapSize++;

    /*
     * Next, re-establish the heap invariant:
     *      heapSize is the index with our inserted element
     */
    upHeap(heapSize);
}

/*
 * Name:      size()
 * Purpose:   Gets the size of the Heap
 * Arguments: None
 * Returns:   int -- the size of the Heap
 * Effects:   None
 */
int Heap::size()
{
    return heapSize;
}

/*
 * Name:      leftChild(int index)
 * Purpose:   Gets the index of the left child of the element at the given index
 * Arguments: int -- the index of the element that the client wants the left
 *                   child of
 * Returns:   int -- the index of the left child
 * Effects:   None
 */
int Heap::leftChild(int index)
{
    return index * 2;
}

/*
 * Name:      rightChild(int index)
 * Purpose:   Gets the index of the right child of the element at the given
 *            index
 * Arguments: int -- the index of the element that the client wants the right
 *                   child of
 * Returns:   int -- the index of the right child
 * Effects:   None
 */
int Heap::rightChild(int index)
{
    return (index * 2) + 1;
}

/*
 * Name:      parent(int index)
 * Purpose:   Gets the index of the parent of the element at the given index
 * Arguments: int -- the index of the element that the client wants the parent
 *                   of
 * Returns:   int -- the index of the parent
 * Effects:   None
 */
int Heap::parent(int index)
{
    return index / 2;
}

/*
 * Name:      ensureCapacity(int desiredCapacity)
 * Purpose:   Ensures heap array has at least the desired capacity.
 * Arguments: int -- the minimum desired capacity
 * Returns:   None
 * Effects:   Expands the heap array to be at least the given minimum desired
 *            capacity
 */
void Heap::ensureCapacity(int desiredCapacity)
{
    if (maxCapacity >= desiredCapacity)
    {
        return; /* Nothing to do: array is big enough */
    }

    /* Otherwise, expand */
    int newCapacity = max(desiredCapacity, 2 * maxCapacity + 2);
    string *newArray = new string[newCapacity];

    /* Note: elements occupy slots 1 to heapSize, inclusive */
    for (int i = 0; i < heapSize + 1; ++i)
    {
        newArray[i] = heap[i];
    }

    maxCapacity = newCapacity;
    delete[] heap;
    heap = newArray;
}
