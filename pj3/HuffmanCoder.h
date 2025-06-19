/*
 *  HuffmanCoder.h
 *  Jack Craig
 *  03/15/2025
 *
 *  CS 15 Project 3: Zap (Phase 2)
 *  Defines encoder/decoder for Huffman compression
 *  and decompression workflows.
 *
 */

#ifndef _HUFFMAN_CODER
#define _HUFFMAN_CODER

#include <string>
#include <unordered_map>
#include <queue>
#include "HuffmanTreeNode.h"
#include "phaseOne.h"
#include "ZapUtil.h"

class HuffmanCoder
{
public:
    void encoder(const std::string &inputFile, const std::string &outputFile);
    void decoder(const std::string &inputFile, const std::string &outputFile);

private:
    // Helper functions
    HuffmanTreeNode *build_huffman_tree(int frequencies[256]);
    void generate_codes(HuffmanTreeNode *root, const std::string &code,
                        std::unordered_map<char, std::string> &code_map);
    std::string encode_text(
        std::istream &input,
        const std::unordered_map<char, std::string> &code_map);
    std::string decode_text(const std::string &bitstring,
                            HuffmanTreeNode *root);
    void free_tree(HuffmanTreeNode *root);
};

#endif