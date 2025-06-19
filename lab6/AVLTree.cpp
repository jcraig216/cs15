/*
 *      AVLTree.cpp
 *      CS15 Lab 07: AVL Trees
 *
 *      Implementation of AVLTree.h. Student must complete TODOs in this file.
 *
 *      2024-03-4 Modified by Skylar Gilfeather
 *                Rewrote documentation
 *                Added ASCII AVL Trees to leftRotate() and rightRotate()
 *                Added and renamed local variables in leftRotate() and
 *                    rightRotate() to provide a template to students.
 *                Moved increment of node's height out of leftRotate() and
 *                    rightRotate() and into insert(), so that remove()
 *                    can properly update height with these rotation methods.
 *      2024-10-20 Modified by Kathy Quintanilla
 *                 Updated header + removed remove() functions because unused.
 */

#include <iostream>
#include "AVLTree.h"

using namespace std;

/*
 * The following 3 functions are specific to the Node struct.
 */

/* newNode()
 *    Purpose: Creates a new AVL Tree Node on the heap.
 * Parameters: int data    - integer data stored in the Node
 *             int height  - height of the Node, i.e. max number of edges to a
 *                           leaf
 *             Node *left  - left child Node of the Node, or nullptr
 *             Node *right - right child Node of the Node, or nullptr
 *    Returns: Node *      - a new Node on the heap.
 */
static Node *newNode(int data, int height, Node *left, Node *right)
{
        Node *np = new Node();

        np->data = data;
        np->height = height;
        np->left = left;
        np->right = right;

        return np;
}

/* newNode()
 *    Purpose: Creates a new AVL Tree Node on the heap. Creates a 'leaf' Node
 *             with a height of 0 and no children.
 * Parameters: int data - integer data stored in the Node
 *    Returns: Node *   - a new Node on the heap.
 */
static Node *newNode(int data)
{
        return newNode(data, 0, nullptr, nullptr);
}

/* deleteNode()
 *    Purpose: Deletes an AVL Tree Node on the heap.
 * Parameters: Node *node - Node on the heap to delete
 *    Returns: None
 */
static void deleteNode(Node *node)
{
        node->height = -1; /* something that couldn't be in a real node */
        node->data = -1;   /* arbitrary value */
        node->left = nullptr;
        node->right = nullptr;
        delete node;
}

/* Constructor
 *    Purpose: Creates a new, empty AVLTree
 * Parameters: None
 *    Returns: N/A
 */
AVLTree::AVLTree()
{
        root = nullptr;
}

/* Destructor
 *    Purpose: Free any allocated memory from this AVL Tree
 * Parameters: None
 *    Returns: N/A
 */
AVLTree::~AVLTree()
{
        /* Walk tree in post-order traversal and delete */
        postOrderDelete(root);
        root = nullptr; /* Not really necessary, since the tree is going
                         * away, but might want to guard against someone
                         * using a pointer after deleting
                         */
}

/* postOrderDelete()
 *    Purpose: Delete the subtree rooted at node using a post-order traversal
 * Parameters: Node *node - Node at the root of the subtree to delete
 *    Returns: None
 *
 * Note: Delete the left subtree, right subtree, and then the node itself
 */
void AVLTree::postOrderDelete(Node *node)
{
        if (node != nullptr)
        {
                postOrderDelete(node->left);
                postOrderDelete(node->right);
                deleteNode(node);
        }
}

/* insert()
 *    Purpose: Insert the value into the AVL Tree
 * Parameters: int value - interger value to insert into the tree
 *    Returns: None
 *       Note: calls a recursive insert()
 */
void AVLTree::insert(int value)
{
        root = insert(root, value);
}

/* insert()
 *    Purpose: Insert the value into the subtree rooted at node.
 * Parameters: Node *node   - currently visited Node
 *             int value    - interger value to insert into the tree
 *    Returns: Node *       - The Node now in the position of node in the AVL
 *                            tree: node, if no rotations were performed, or
 *                            one of node's children, if a rotation was
 *                            performed.
 *
 * Note: Recursively traverse the AVL tree to the leaf position where value
 *       should be inserted, and inserts it as a new Node.
 *       Balance the subtree rooted at node, if necessary, and return the Node
 *       now in node's position.
 */
Node *AVLTree::insert(Node *node, int value)
{
        /* node is an empty position, a child of a leaf node: insert here! */
        if (node == nullptr)
        {
                return newNode(value);
        }
        /* if value already exists in the AVL Tree, do not insert */
        else if (value == node->data)
        {
                return node;
        }
        /* traverse to and insert value somewhere in node's left subtree */
        else if (value < node->data)
        {
                node->left = insert(node->left, value);
        }
        /* traverse to and insert value somewhere in node's right subtree */
        else if (value > node->data)
        {
                node->right = insert(node->right, value);
        }

        /* AVL Tree rebalancing starts */
        node->height = 1 + max(nodeHeight(node->left),
                               nodeHeight(node->right));

        Node *newNode = balance(node);
        /* AVL Tree rebalancing ends */

        return newNode;
}

/* balance()
 *    Purpose: Balance the AVL Tree to AVL standards
 * Parameters: Node *node - node at the root of the subtree to rebalance
 *    Returns: Node *     - The Node now in the position of node in the AVL
 *                          tree: node, if no rotations were performed, or one
 *                          of node's children, if a rotation was performed.
 *
 * Note: Check if the subtree rooted at node is out of balance. Then, rebalance
 *       the subtree rooted at node if necessary, by calling leftRotate() and
 *       rightRotate() to perform rotations.
 */
Node *AVLTree::balance(Node *node)
{
        int balanceFactor = heightDiff(node);

        /* TODO: evaluate the balance factor to see if node is balanced.
         *       If not, handle the case: LL, LR, RR, or RL!
         */
        if (node == nullptr)
        {
                return nullptr;
        }
        if (balanceFactor > 1)
        {
                if (heightDiff(node->left) >= 0)
                {
                        return rightRotate(node);
                }
                else
                {
                        node->left = leftRotate(node->left);
                        return rightRotate(node);
                }
        }
        else if (balanceFactor < -1)
        {
                if (heightDiff(node->right) <= 0)
                {
                        return leftRotate(node);
                }
                else
                {
                        node->right = rightRotate(node->right);
                        return leftRotate(node);
                }
        }

        return node;
}

/* rightRotate()
 *    Purpose: Perform a single right rotation on the subtree rooted at node
 * Parameters: Node *node - Node at the root of the subtree to rebalance
 *    Returns: Node *     - The Node now in the position of node in the AVL
 *                          tree: node, if no rotations were performed, or one
 *                          of node's children, if a rotation was performed.
 *
 * Visual: A single right rotation should convert this subtree:
 *
 *              [ node ]
 *              /       \
 *        [ leftChild ] [ rightChild ]
 *         /         \
 *   [ llTree ] [ lrTree ]
 *
 * into this subtree:
 *
 *               [ leftChild ]
 *                /          \
 *         [ llTree ]      [ node ]
 *                         /      \
 *                  [ lrTree ] [ rightChild ]
 */
Node *AVLTree::rightRotate(Node *node)
{
        Node *leftChild = node->left;
        Node *lrTree = node->left->right;

        /* TODO: perform a single right rotation on node! */
        leftChild->right = node;
        node->left = lrTree;

        /* TODO: update heights of nodes that have moved! */
        node->height = 1 + max(nodeHeight(node->left),
                               nodeHeight(node->right));
        leftChild->height = 1 + max(nodeHeight(leftChild->left),
                                    nodeHeight(leftChild->right));

        /* TODO: return the Node that has replaced node! */
        return leftChild;
}

/* leftRotate()
 *    Purpose: Perform a left rotation on the subtree rooted at node
 * Parameters: Node *node - Node at the root of the subtree to rebalance
 *    Returns: Node *     - The Node now in the position of node in the AVL
 *                          tree: node, if no rotations were performed, or one
 *                          of node's children, if a rotation was performed.
 *
 * Visual: A single left rotation should convert this subtree:
 *
 *              [ node ]
 *              /       \
 *        [ leftChild ] [ rightChild ]
 *                        /         \
 *                  [ rlTree ] [ rrTree ]
 *
 * into this subtree:
 *
 *              [ rightChild ]
 *                /       \
 *           [ node ]   [ rrTree ]
 *          /       \
 *   [ leftChild ]  [ rlTree ]
 */
Node *AVLTree::leftRotate(Node *node)
{
        Node *rightChild = node->right;
        Node *rlTree = node->right->left;

        /* TODO: perform a single left rotation on node! */
        rightChild->left = node;
        node->right = rlTree;

        /* TODO: update heights of nodes that have moved! */
        node->height = 1 + max(nodeHeight(node->left),
                               nodeHeight(node->right));
        rightChild->height = 1 + max(nodeHeight(rightChild->left),
                                     nodeHeight(rightChild->right));

        /* TODO: return the Node that has replaced node! */
        return rightChild;
}

/* heightDiff()
 *    Purpose: Calculate the difference between the height of node's left child
 *             and the height of node's right child
 * Parameters: Node *node - Node to calculate the height difference for its
 *                          children
 *    Returns: int        - The integer height difference: greater than 0, if
 *                          node's left subtree is heavier, and less than 0, if
 *                          node's right subtree is heavier.
 */
int AVLTree::heightDiff(Node *node)
{
        int leftHeight = nodeHeight(node->left);
        int rightHeight = nodeHeight(node->right);
        return leftHeight - rightHeight;
}

/* nodeHeight()
 *    Purpose: Returns the height of the node, or -1 if the node doesn't exist
 * Parameters: Node *node - Node to retrieve the height of
 *    Returns: int        - The node's set height, or -1 is the node doesn't
 *                          exist
 */
int AVLTree::nodeHeight(Node *node)
{
        if (node == nullptr)
        {
                return -1;
        }
        return node->height;
}

/* print_tree()
 *    Purpose: Prints the AVL tree prettily
 * Parameters: None
 *    Returns: None
 *
 * Note: calls helper function in pretty_print.cpp
 */
void AVLTree::print_tree() const
{
        printPretty(root, 1, 0, std::cout);
}
