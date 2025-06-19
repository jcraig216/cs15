/*
 * main.cpp
 *
 * CS15 Lab 06: Tree Traversals
 * 
 * Driver that tests the inorder, preorder, and level order traversals (as 
 * implemented by students) of a tree.
 * 
 */

#include <iostream>

#include "BTree.h"

using namespace std;

/* BTree Testing Function Declarations */
void buildTree(BTree &t, int values[], int numValues);
void testInOrder(BTree &t);
void testPreOrder(BTree &t);
void testLevelOrder(BTree &t);

/* main
 *    Purpose: Creates a BTree and prints it out inorder, preorder, and level 
 *             order!
 * Parameters: None
 *    Returns: int -- 0 for a successful exit, 1 for unsuccessful
 */
int main()
{
    BTree t;
    int testData[] = {54, 22, 17, 41, 36, 30, 74, 76, 26, 27, 45, 82};

    buildTree(t, testData, sizeof(testData) / sizeof(int));

    cout << endl;
    testInOrder(t);

    cout << endl;
    testPreOrder(t);

    cout << endl;
    testLevelOrder(t);

    return 0;
}

/* buildTree()
 *    Purpose: Builds a BTree with the given information
 * Parameters: BTree & -- address of the BTree that we want to build
 *             int []  -- values to insert into the BTree
 *             int     -- number of values to insert into the BTree
 *    Returns: None
 */
void buildTree(BTree &t, int values[], int numValues)
{
    for (int i = 0; i < numValues; ++i){
        t.insert(values[i]);
    }
}

/* testInOrder()
 *    Purpose: Test the in-order printing function from the BTree class
 * Parameters: BTree & -- address of the BTree that we want to print in-order
 *    Returns: None
 */
void testInOrder(BTree &t)
{
    cout << "Ricky to the rescue:" << endl;
    cout << "printing inorder: ";
    t.inOrder(cout);
    cout << endl;
    cout << "Answer:           17 22 26 27 30 36 41 45 54 74 76 82";
    cout << endl;
}

/* testPreOrder()
 *    Purpose: Test the pre-order printing function from the BTree class
 * Parameters: BTree & -- address of the BTree that we want to print pre-order
 *    Returns: None
 */
void testPreOrder(BTree &t)
{
    cout << "Stacey saves the day" << endl;
    cout << "printing preorder: ";
    t.preOrder(cout);
    cout << endl;
    cout << "Answer:            54 22 17 41 36 30 26 27 45 74 76 82";
    cout << endl;
}

/* testLevelOrder()
 *    Purpose: Test the level-order printing function from the BTree class
 * Parameters: BTree & -- address of the BTree that we want to print 
 *                        level-order
 *    Returns: None
 */
void testLevelOrder(BTree &t)
{
    cout << "Quiet down, Quinn's in Town" << endl;
    cout << "printing levelorder: ";
    t.levelOrder(cout);
    cout << endl;

    cout << "Answer:              54 22 74 17 41 76 36 45 82 30 26 27";
    cout << endl;
}
