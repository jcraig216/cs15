/*
 *  phaseOne.h
 *  Jack Craig
 *  03/15/2025
 *
 *  CS 15 Project 3: Zap (Phase 1)
 *  Interface for character frequency counting and
 *  Huffman tree serialization/deserialization.
 *
 */
#ifndef __PHASEONE_H
#define __PHASEONE_H

#include <istream>
#include <string>

#include "HuffmanTreeNode.h"

void count_freqs(std::istream &text);
std::string serialize_tree(HuffmanTreeNode *root);
HuffmanTreeNode *deserialize_tree(const std::string &s);

void compute_freqs(std::istream &text, int frequencies[256]);

#endif