/*
 *  HuffmanCoder.cpp
 *  Jack Craig
 *  03/15/2025
 *
 *  CS 15 Project 3: Zap (Phase 2)
 *  Implements Huffman encoding/decoding logic including
 *  tree construction, bitstring generation, and error handling.
 *
 */

#include "HuffmanCoder.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <sstream>

/*
 * name:      encoder
 * purpose:   Compresses a text file using Huffman coding and saves the result.
 * arguments: inputFile - Path to the input text file.
 *            outputFile - Path to save the compressed .zap file.
 * returns:   None.
 * effects:   Prints compression status to stdout. Creates a compressed
 *            binary file.
 *            Throws runtime_error if input file cannot be opened.
 */
void HuffmanCoder::encoder(const std::string &inputFile,
                           const std::string &outputFile)
{
    // Check for empty file
    std::ifstream input(inputFile);
    if (input.peek() == std::ifstream::traits_type::eof())
    {
        std::cout << inputFile << " is empty and cannot be compressed.\n";
        return;
    }

    // Compute frequencies
    int frequencies[256] = {0};
    compute_freqs(input, frequencies);
    input.clear();
    input.seekg(0);

    // Build Huffman tree
    HuffmanTreeNode *root = build_huffman_tree(frequencies);

    // Generate codes
    std::unordered_map<char, std::string> code_map;
    generate_codes(root, "", code_map);

    // Encode text
    std::string bitstring = encode_text(input, code_map);

    // Serialize tree
    std::string serial_tree = serialize_tree(root);

    // Write to file
    writeZapFile(outputFile, serial_tree, bitstring);

    // Print bit count
    std::cout << "Success! Encoded given text using "
              << bitstring.size() << " bits.\n";

    // Cleanup
    free_tree(root);
    input.close();
}

/*
 * name:      decoder
 * purpose:   Decompresses a .zap file back to its original text form.
 * arguments: inputFile - Path to the compressed .zap file.
 *            outputFile - Path to save the decompressed text.
 * returns:   None.
 * effects:   Creates a decoded text file. Throws runtime_error for
 *            invalid/mismatched encodings.
 */
void HuffmanCoder::decoder(const std::string &inputFile,
                           const std::string &outputFile)
{
    // Read zap file
    auto [serial_tree, bitstring] = readZapFile(inputFile);

    // Deserialize tree
    HuffmanTreeNode *root = deserialize_tree(serial_tree);

    // Decode text
    std::string decoded_text = decode_text(bitstring, root);

    // Write to output file
    std::ofstream output(outputFile);
    output << decoded_text;
    output.close();

    // Cleanup
    free_tree(root);
}

/*
 * name:      build_huffman_tree
 * purpose:   Constructs a Huffman tree from character frequencies
 *            using a priority queue.
 * arguments: frequencies - Array of ASCII character counts (index = ASCII
 *            value).
 * returns:   Root node of the constructed Huffman tree.
 * effects:   Allocates memory for tree nodes. Handles single-character edge
 *            case.
 */
HuffmanTreeNode *HuffmanCoder::build_huffman_tree(int frequencies[256])
{
    std::priority_queue<HuffmanTreeNode *,
                        std::vector<HuffmanTreeNode *>, NodeComparator>
        pq;

    // Create leaf nodes
    for (int i = 0; i < 256; i++)
    {
        if (frequencies[i] > 0)
        {
            pq.push(new HuffmanTreeNode(static_cast<char>(i), frequencies[i]));
        }
    }

    // Handle single character case
    if (pq.size() == 1)
    {
        auto node = pq.top();
        pq.pop();
        auto root = new HuffmanTreeNode(node->get_freq(), node, nullptr);
        return root;
    }

    // Build tree
    while (pq.size() > 1)
    {
        auto left = pq.top();
        pq.pop();
        auto right = pq.top();
        pq.pop();

        auto parent = new HuffmanTreeNode(left->get_freq() +
                                              right->get_freq(),
                                          left, right);
        pq.push(parent);
    }

    return pq.top();
}

/*
 * name:      generate_codes
 * purpose:   Recursively generates binary codes for all characters in
 *            the Huffman tree.
 * arguments: root - Current node in recursion.
 *            code - Accumulated binary code string.
 *            code_map - Map to store character-to-code relationships.
 * returns:   None.
 * effects:   Populates code_map with Huffman codes. Uses DFS traversal.
 */
void HuffmanCoder::generate_codes(
    HuffmanTreeNode *root, const std::string &code,
    std::unordered_map<char, std::string> &code_map)
{
    if (root == nullptr)
        return;

    if (root->is_leaf())
    {
        code_map[root->get_val()] = code.empty() ? "0"
                                                 : code; // Handle single node
    }
    else
    {
        generate_codes(root->get_left(), code + "0", code_map);
        generate_codes(root->get_right(), code + "1", code_map);
    }
}

/*
 * name:      encode_text
 * purpose:   Converts input text to a compressed bitstring using
 *            generated Huffman codes.
 * arguments: input - Reference to input text stream.
 *            code_map - Precomputed character-to-code mappings.
 * returns:   Binary string of 0s and 1s representing compressed data.
 * effects:   Reads entire input stream. Requires code_map to contain
 *            all input characters.
 */
std::string HuffmanCoder::encode_text(
    std::istream &input,
    const std::unordered_map<char, std::string> &code_map)
{
    std::string bitstring;
    char c;
    while (input.get(c))
    {
        bitstring += code_map.at(c);
    }
    return bitstring;
}

/*
 * name:      decode_text
 * purpose:   Converts compressed bitstring back to original text using
 *            Huffman tree.
 * arguments: bitstring - Binary string from compressed file.
 *            root - Root of deserialized Huffman tree.
 * returns:   Original decoded text.
 * effects:   Throws runtime_error if traversal ends at internal node
 *            (invalid encoding).
 */
std::string HuffmanCoder::decode_text(const std::string &bitstring,
                                      HuffmanTreeNode *root)
{
    std::string text;
    HuffmanTreeNode *current = root;

    for (char bit : bitstring)
    {
        current = (bit == '0') ? current->get_left() : current->get_right();

        if (current->is_leaf())
        {
            text += current->get_val();
            current = root; // Reset to root
        }
    }

    if (current != root)
    {
        throw std::runtime_error("Encoding did not match Huffman tree.");
    }

    return text;
}

/*
 * name:      free_tree
 * purpose:   Recursively deallocates memory for Huffman tree nodes.
 * arguments: root - Current node in recursion.
 * returns:   None.
 * effects:   Frees all heap memory associated with the tree.
 */
void HuffmanCoder::free_tree(HuffmanTreeNode *root)
{
    if (root == nullptr)
        return;
    free_tree(root->get_left());
    free_tree(root->get_right());
    delete root;
}