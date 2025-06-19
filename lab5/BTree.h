/*
 * BTree.h
 *
 * CS15 Lab 06: Tree Traversals
 * 
 * The BTree class is a simple class that represents a Binary Tree of integer 
 * values. Clients can insert integers and print different order traversals to a
 * given output!
 * 
 */

#ifndef BTREE_H
#define BTREE_H

#include <iostream>

class BTree {
    public:
        BTree();
        ~BTree();

        void insert(int v);

        void inOrder(std::ostream &out)    const;
        void preOrder(std::ostream &out)   const;
        void levelOrder(std::ostream &out) const;

        void postOrderDelete();

    private:
        struct BTNode {
            int      value;
            BTNode *left;
            BTNode *right;
        };

        BTNode *root;

        BTNode *newBTNode(int v);
        BTNode *newBTNode(int v, BTNode *left, BTNode *right);

        bool     isEmpty(BTNode *curr) const;
        BTNode  *insert(BTNode *curr, int v);
        void     inOrder(BTNode *curr, std::ostream &out) const;
        void     preOrder(BTNode *curr, std::ostream &out) const;
        void     levelOrder(BTNode *curr, std::ostream &out) const;
        void     postOrderDelete(BTNode *curr);
};

#endif
