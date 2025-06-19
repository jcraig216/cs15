/*
 *      main.cpp
 *      CS15 Lab 07: AVL Trees
 *
 *      Driver file for Lab 07 that interacts with the AVLTree class to build a
 *      balanced AVL tree and print it out.
 *
 *      2024-03-4 Modified by Skylar Gilfeather
 *                Edited output
 *      2024-10-20 Modified by Kathy Quintanilla
 *                Edited starting values + updated header
 */

#include <iostream>
#include "AVLTree.h"

using namespace std;

/* main()
 *    Purpose: Creates and inserts int values into an AVL tree and prints out
 *             the resulting tree.
 * Parameters: N/A
 *    Returns: int -- 0 to signify a successful end to the program.
 * Other Info: AVLTree's balance() must be fully functioning for the AVL Tree
 *             to be printed out correctly.
 */
int main()
{
        AVLTree avl;
        int values[] = {5, 6, 7, 16, 15, 30, 1, 34, 9, 645};
        int numValues = sizeof(values) / sizeof(int);

        for (int i = 0; i < numValues; i++)
        {
                cout << "Inserting " << values[i] << "..." << endl;
                avl.insert(values[i]);
        }

        cout << "Finished AVL tree: " << endl;
        avl.print_tree();

        return 0;
}
