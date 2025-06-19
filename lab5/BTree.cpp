/*
 * BTree.cpp
 *
 * CS15 Lab 06: Tree Traversals
 *
 * Implementation of BTree (Binary Tree) class with integer keys.
 *
 */

#include <cstdlib>
#include <iostream>
#include <queue>
#include <stack>

#include "BTree.h"

using namespace std;

/* constructor
 *    Purpose: Initialize an empty BTree
 * Parameters: None
 *    Returns: None
 */
BTree::BTree()
{
    root = nullptr;
}

/* destructor
 *    Purpose: Deallocate all allocated memory for BTreeNodes
 * Parameters: None
 *    Returns: None
 *       NOTE: Students must complete postOrderDelete() to work.
 */
BTree::~BTree()
{
    postOrderDelete();
}

/* isEmpty()
 *    Purpose: Check if a BTree is empty or not
 * Parameters: BTNode * -- the root of the tree that we want to check
 *    Returns: bool -- true if tree is empty and false otherwise
 */
bool BTree::isEmpty(BTNode *curr) const
{
    return curr == nullptr;
}

/* insert()
 *    Purpose: Insert a given value into the BTree
 * Parameters: int -- value to insert into BTree
 *    Returns: None
 */
void BTree::insert(int v)
{
    root = insert(root, v);
}

/* insert()
 *    Purpose: Insert a given value into the BTree
 * Parameters: BTNode *  -- current node
 *             int       -- value to insert into BTree
 *    Returns: BTNode *  -- the root of current tree with the value inserted
 *       Note: ALWAYS adds a leaf.
 *
 * Implementation notes:
 *        - When the base case is reached, we are inserting the value
 *          into an empty tree, i. e., r is nullptr.
 *          In this case, we create a new leaf node with the given data
 *          value and return a pointer to that.  If the caller had a
 *          non-empty tree node, then they will set the corresponding
 *          subtree in their node to the result.
 *          DRAW THIS OUT!
 *        - Duplicate keys will go into right branch here, i. e., the
 *          left subtree contains values < node's key, right subtree
 *          contains values >= node's key.
 */
BTree::BTNode *BTree::insert(BTNode *curr, int v)
{
    if (isEmpty(curr))
    {
        return newBTNode(v);
    }
    else if (v < curr->value)
    {
        curr->left = insert(curr->left, v);
        return curr;
    }
    else
    {
        curr->right = insert(curr->right, v);
        return curr;
    }
}

/****************** inorder *****************/

/* inOrder()
 *    Purpose: Perform a in-order print of this BTree
 * Parameters: ostream & -- output stream to output the in-ordered tree to
 *    Returns: None
 */
void BTree::inOrder(std::ostream &out) const
{
    inOrder(root, out);
}

/* inOrder()
 *    Purpose: Perform am in-order print of the subtree rooted at given node.
 * Parameters: BTNode *  -- root of the subtree to perform the in-order print
 *                          on
 *             ostream & -- output stream to output the in-ordered tree to
 *    Returns: None
 */
void BTree::inOrder(BTNode *curr, std::ostream &out) const
{
    if (curr != nullptr)
    {
        inOrder(curr->left, out);
        out << curr->value << " ";
        inOrder(curr->right, out);
    }
}

/****************** preorder *****************/

/* preOrder()
 *    Purpose: Perform a pre-order print of this BTree
 * Parameters: ostream & -- output stream to output the pre-ordered tree to
 *    Returns: None
 *
 * Question to ponder: Can we do this without a helper function?
 */
void BTree::preOrder(std::ostream &out) const
{
    preOrder(root, out);
}

/* preOrder()
 *    Purpose: Perform a pre-order print of the subtree rooted at given node.
 * Parameters: BTNode *  -- root of the subtree to perform the pre-order print
 *                          on
 *             ostream & -- output stream to output the pre-ordered tree to
 *    Returns: None
 *       Note: Uses a stack from the STL rather than the C++ run time stack.
 */
void BTree::preOrder(BTNode *curr, std::ostream &out) const
{
    /* TODO: Use a stack, declare it here */

    if (curr == nullptr)
    {
        return;
    }

    std::stack<BTNode *> s;
    s.push(curr);

    while (!s.empty())
    {
        BTNode *node = s.top();
        s.pop();

        out << node->value << " ";

        if (node->right)
        {
            s.push(node->right);
        }
        if (node->left)
        {
            s.push(node->left);
        }
    }

    /* TODO: your code here */
}

/****************** level-order *****************/

/* levelOrder()
 *    Purpose: Perform a level-order print of this BTree
 * Parameters: ostream & -- output stream to output the level-ordered tree to
 *    Returns: None
 */
void BTree::levelOrder(std::ostream &out) const
{
    levelOrder(root, out);
}

/* levelOrder()
 *    Purpose: Perform a level-order print of the subtree rooted at the given
 *             node.
 * Parameters: BTNode *  -- root of the subtree to perform the level-order
 *                          print on
 *             ostream & -- output stream to output the level-ordered tree to
 *    Returns: None
 *       Note: Must be implemented using an std::queue
 */
void BTree::levelOrder(BTNode *curr, std::ostream &out) const
{
    /* TODO: Use a queue, declare it here */
    std::queue<BTNode *> q;

    /* TODO: your code here */

    if (curr == nullptr)
    {
        return;
    }
    q.push(curr);

    while (!q.empty())
    {
        BTNode *node = q.front();
        out << node->value << " ";
        q.pop();

        if (node->left)
        {
            q.push(node->left);
        }
        if (node->right)
        {
            q.push(node->right);
        }
    }
}

/****************** postorder *****************/

/* postOrderDelete()
 *    Purpose: Perform post-order traversal to delete the entire tree
 * Parameters: None
 *    Returns: None
 */
void BTree::postOrderDelete()
{
    postOrderDelete(root);
}

/* postOrderDelete()
 *    Purpose: Perform post-order traversal to delete tree rooted at given node
 * Parameters: BTNode *  -- root of the tree to perform the post-order delete
 *                          on
 *    Returns: None
 *
 * Question to ponder: Could we use another traversal to delete the tree?
 */
void BTree::postOrderDelete(BTNode *curr)
{
    /* TODO: your code here */
}

/*****************************************************************************
 * A couple handy functions for creating new, initialized nodes.             *
 * We could make constructors for the struct, but let's keep things simple.  *
 *****************************************************************************/

/* newBTNode()
 *    Purpose: Create a new BTNode with given values
 * Parameters: int      -- value that the new BTNode should have
 *             BTNode * -- a left BTNode * to be the new BTNode's left child
 *                         and a right BTNode * to be the new BTNode's right
 *                         child
 *    Returns: BTNode * -- pointer to a BTNode with the given values
 */
BTree::BTNode *BTree::newBTNode(int v, BTNode *left, BTNode *right)
{
    BTNode *newNode = new BTNode;
    newNode->value = v;
    newNode->left = left;
    newNode->right = right;

    return newNode;
}

/* newBTNode()
 *    Purpose: Create a new BTNode
 * Parameters: int -- value that the new BTNode should have
 *    Returns: BTNode * -- pointer to a BTNode with value v and no children
 */
BTree::BTNode *BTree::newBTNode(int v)
{
    return newBTNode(v, nullptr, nullptr);
}