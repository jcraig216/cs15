/* CS15 Lab: Heaps
 *
 * A class that organizes a collection of strings into a min-heap.
 * 
 * Heap Time Complexity with below implementation:
 *      O(n log n) construction (can be O(n) if you use algorithm from class)!
 *      O(log n)   insertion
 *      O(1)       to access minimum element
 *      O(log n)   to remove minimum element.
 * 
 *      Edited by: Kathy Quintanilla, November 2024
 *                 updated comments and style
 */

#include <string>

using std::string;

class Heap {
public:
    Heap();
    ~Heap();

    /* Build a heap from array list with size listSize */
    Heap(string list[], int listSize);

    /* Insert s into heap; not used for this lab */
    void insert(string s);

    /* Return minimum element; not used for this lab */
    string min();

    /* Remove and return smallest element in heap */
    string removeMin();

    /* Return size of heap */
    int size();

private:
    /* Heap is implemented as an array list */
    static const int INIT_SIZE = 100;

    string* heap;        /* Pointer to array with Heap data */
    int     heapSize;    /* # of elements currently in Heap */
    int     maxCapacity; /* current max capacity */

    /*
     * downHeap is recursive and works with the location of the element in the 
     * tree. heap[location] stores the value being inserted.
     */
    void downHeap(int location);

    /*
     * upHeap bubbles an inserted element up to the proper spot (fixes heap 
     * invariant).
     *
     * This function is needed because element is originally inserted into 
     * first open spot in tree, which is the first available slot in array 
     * (satisfies shape invariant), so upHeap is needed to fix the heap 
     * invariant
     *
     * upHeap is used in insert()
     */
    void upHeap(int location);

    /*
     * buildHeap is used by the constructor that takes in an array and turns 
     * the array into a min heap (aka "heapifies" the given array)
     */
    void buildHeap();

    /*
     * Functions below abstract away calculations for child/parent relationships
     */
    int leftChild(int index);
    int rightChild(int index);
    int parent(int index);

    /*
     * ensureCapacity makes sure that the heap array has at least the desired 
     * capacity
     */
    void ensureCapacity(int desiredCapacity);
};
