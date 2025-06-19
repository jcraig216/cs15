/*
 *      AVLTree.h
 *      CS15 Lab 07: AVL Trees
 *
 *      AVLTree is a class that begins as an empty AVL Tree representation and 
 *      allows for the insertion of int values. Clients can also print a visual 
 *      representation of the AVL Tree. 
 * 
 *      Note: Balancing functions must be implemented by students to get an 
 *            accurate AVL tree representation.
 *
 *      2024-03-04 Modified by Skylar Gilfeather
 *                 Edited documentation 
 *      2024-10-20 Modified by Kathy Quintanilla
 *                 Edited header to comply with style guide + removed remove() 
 *                 functions because they are not used.
 */

#ifndef AVLTREE_H_
#define AVLTREE_H_

#include <iostream>


/*
 * Purpose:  AVL Tree Node
 * Members:
 *      data - integer data value 
 *      height - height of the Node: maximum number of edges from the Node
 *               to a leaf Node.
 *      left - left child Node of the Node
 *      right - right child Node of the Node
 * Note: Defined outside of the AVLTree class so that the code in
 *       pretty_print.cpp can work with Node. This is not good abstraction–
 *       don't do this in your code!
 */
struct Node {
        int   data;
        int   height;
        Node *left;
        Node *right;
};


/* defined in pretty_print.cpp */
void printPretty(Node *root, int level, int indentSpace, std::ostream &out);


class AVLTree {
public:
        /* constructor */
        AVLTree();

        /* destructor */
        ~AVLTree();

        /*
         * insert() inserts a value into the AVL Tree and balances the
         * tree with each insertion.
         * If the value is already in the tree, insert() doesn't add it.
         */
        void insert(int value);
        
        /* print the tree (written for you) */
        void print_tree() const;

private:
        /* the root of the tree (starts as nullptr) */
        Node *root;

        /*
         * the following seven functions are private helper functions
         * for the public functions. We do not want to expose the
         * internals of the tree publicly, so we pass the root (and
         * other information in some cases) to the functions below
         * from the public functions.
         */

        /* recursively traverses the tree to find the location */
        Node *insert(Node *node, int value);

        /* TODOs */
        Node *balance(Node *node);
        Node *rightRotate(Node *node);
        Node *leftRotate(Node *node); 

        /* Calculates the difference between node->left's height and
           node->right's height (written for you) 
         */
        int heightDiff(Node *node); 
        /* Returns the height of node (written for you) */
        int nodeHeight(Node *node);

        /* used by the destructor to delete nodes recursively */
        void postOrderDelete(Node *node);
};


#endif