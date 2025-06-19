/*
 *  phaseOne.cpp
 *  Jack Craig
 *  03/15/2025
 *
 *  CS 15 Project 3: Zap (Phase 1)
 *  Implements frequency analysis and tree serialization
 *  for Huffman coding compression.
 *
 */

#include "phaseOne.h"
#include "HuffmanTreeNode.h"
#include <iostream>

/*
 * name:      count_freqs()
 * purpose:   Count the frequency of each ASCII character in the input stream.
 * arguments: A reference to an input stream (text).
 * returns:   None.
 * effects:   Prints character frequencies to standard output in the format
 *            "CHAR: COUNT".
 */
void count_freqs(std::istream &text)
{
    int counts[256] = {0};
    char c;
    while (text.get(c))
    {
        counts[static_cast<unsigned char>(c)]++;
    }
    for (int i = 0; i < 256; ++i)
    {
        if (counts[i] > 0)
        {
            std::cout << static_cast<char>(i)
                      << ": " << counts[i] << std::endl;
        }
    }
}

/*
 * name:      serialize_tree()
 * purpose:   Convert a Huffman tree into a serialized string using
 *  preorder traversal.
 * arguments: A pointer to the root of the Huffman tree.
 * returns:   A string representing the serialized tree.
 * effects:   None (does not modify the tree).
 */
std::string serialize_tree(HuffmanTreeNode *root)
{
    if (root == nullptr)
        return "";
    if (root->is_leaf())
    {
        return "L" + std::string(1, root->get_val());
    }
    else
    {
        return "I" + serialize_tree(root->get_left()) +
               serialize_tree(root->get_right());
    }
}

/*
 * name:      deserialize_helper()
 * purpose:   Recursively reconstruct a Huffman tree from a serialized string.
 * arguments: The serialized string (s) and current position index (pos).
 * returns:   A pointer to the root of the reconstructed subtree.
 * effects:   Allocates memory for new HuffmanTreeNodes.
 */
HuffmanTreeNode *deserialize_helper(const std::string &s, size_t &pos)
{
    if (pos >= s.size())
        return nullptr;
    char type = s[pos++];
    if (type == 'L')
    {
        if (pos >= s.size())
            throw std::runtime_error("Invalid serialized tree");
        char c = s[pos++];
        return new HuffmanTreeNode(c, 0);
    }
    else if (type == 'I')
    {
        HuffmanTreeNode *left = deserialize_helper(s, pos);
        HuffmanTreeNode *right = deserialize_helper(s, pos);
        return new HuffmanTreeNode(0, left, right);
    }
    else
    {
        throw std::runtime_error("Invalid serialized tree");
    }
}

/*
 * name:      deserialize_tree()
 * purpose:   Deserialize a Huffman tree from a string.
 * arguments: The serialized string (s).
 * returns:   A pointer to the root of the reconstructed Huffman tree.
 * effects:   Allocates memory for the entire tree.
 */
HuffmanTreeNode *deserialize_tree(const std::string &s)
{
    size_t pos = 0;
    return deserialize_helper(s, pos);
}

void compute_freqs(std::istream &text, int frequencies[256])
{
    char c;
    while (text.get(c))
    {
        frequencies[static_cast<unsigned char>(c)]++;
    }
}