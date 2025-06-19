#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#include "HuffmanCoder.h"
#include "phaseOne.h"
#include <cassert>
#include <sstream>
#include <fstream>
#include <iostream>

// Test 1: Empty input for count_freqs
void test_count_freqs_empty()
{
    std::istringstream input("");
    std::streambuf *orig = std::cout.rdbuf();
    std::ostringstream capture;
    std::cout.rdbuf(capture.rdbuf());

    count_freqs(input);
    assert(capture.str().empty());

    std::cout.rdbuf(orig);
}

// Test 2: Single character frequency count
void test_count_freqs_single_char()
{
    std::istringstream input("a");
    std::streambuf *orig = std::cout.rdbuf();
    std::ostringstream capture;
    std::cout.rdbuf(capture.rdbuf());

    count_freqs(input);
    assert(capture.str() == "a: 1\n");

    std::cout.rdbuf(orig);
}

// Test 3: Multiple characters with whitespace
void test_count_freqs_whitespace()
{
    std::istringstream input("a a\n");
    std::streambuf *orig = std::cout.rdbuf();
    std::ostringstream capture;
    std::cout.rdbuf(capture.rdbuf());

    count_freqs(input);
    std::string output = capture.str();
    assert(not(output.find("a: 2") == std::string::npos));
    assert(not(output.find(" : 1") == std::string::npos));  // Space
    assert(not(output.find("\n: 1") == std::string::npos)); // Newline

    std::cout.rdbuf(orig);
}

// Test 4: Serialize single node tree
void test_serialize_single_node()
{
    HuffmanTreeNode *root = new HuffmanTreeNode('a', 1);
    assert(serialize_tree(root) == "La");
    delete root;
}

// Test 5: Serialize simple tree
void test_serialize_simple_tree()
{
    HuffmanTreeNode *left = new HuffmanTreeNode('a', 1);
    HuffmanTreeNode *right = new HuffmanTreeNode('b', 1);
    HuffmanTreeNode *root = new HuffmanTreeNode(2, left, right);
    assert(serialize_tree(root) == "ILaLb");
    delete root;
}

// Test 6: Deserialize single node
void test_deserialize_single_node()
{
    std::string serial = "La";
    HuffmanTreeNode *root = deserialize_tree(serial);
    assert(root->is_leaf());
    assert(root->get_val() == 'a');
    delete root;
}

// Test 7: Deserialize nested tree
void test_deserialize_nested_tree()
{
    std::string serial = "IILaLbLc";
    HuffmanTreeNode *root = deserialize_tree(serial);

    // Root is internal node (I)
    assert(not root->is_leaf());

    // Root's left child is internal node (I)
    HuffmanTreeNode *leftChild = root->get_left();
    assert(not(leftChild == nullptr));
    assert(not leftChild->is_leaf());

    // Left child's left is leaf 'a'
    assert(leftChild->get_left()->is_leaf());
    assert(leftChild->get_left()->get_val() == 'a');

    // Left child's right is leaf 'b'
    assert(leftChild->get_right()->is_leaf());
    assert(leftChild->get_right()->get_val() == 'b');

    // Root's right child is leaf 'c'
    assert(root->get_right()->is_leaf());
    assert(root->get_right()->get_val() == 'c');

    delete root;
}

// Test 8: Round-trip serialization/deserialization
// void test_round_trip()
// {
//     HuffmanTreeNode *left = new HuffmanTreeNode('x', 5);
//     HuffmanTreeNode *right = new HuffmanTreeNode('y', 10);
//     HuffmanTreeNode *root = new HuffmanTreeNode(left, right);

//     std::string serial = serialize_tree(root);
//     HuffmanTreeNode *new_root = deserialize_tree(serial);

//     assert(treeEquals(root, new_root, false, false));
//     delete root;
//     delete new_root;
// }

// Test 9: Invalid deserialization format
void test_deserialize_invalid()
{
    try
    {
        deserialize_tree("X");
        assert(false);
    }
    catch (const std::runtime_error &e)
    {
        assert(std::string(e.what()) == "Invalid serialized tree");
    }
}
// Test 11: Encode/Decode Round Trip (Basic)
void test_round_trip_basic()
{
    HuffmanCoder coder;

    // Create test file
    std::ofstream out("test_roundtrip.txt");
    out << "abracadabra";
    out.close();

    // Encode
    coder.encoder("test_roundtrip.txt", "test_roundtrip.zap");

    // Decode
    coder.decoder("test_roundtrip.zap", "test_roundtrip_out.txt");

    // Verify
    std::ifstream original("test_roundtrip.txt");
    std::ifstream decoded("test_roundtrip_out.txt");
    assert(std::equal(std::istreambuf_iterator<char>(original),
                      std::istreambuf_iterator<char>(),
                      std::istreambuf_iterator<char>(decoded)));

    // Cleanup
    remove("test_roundtrip.txt");
    remove("test_roundtrip.zap");
    remove("test_roundtrip_out.txt");
}

// Test 12: Empty File Handling
void test_empty_file()
{
    HuffmanCoder coder;

    // Create empty file
    std::ofstream out("empty.txt");
    out.close();

    // Capture cout output
    std::stringstream buffer;
    std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());

    coder.encoder("empty.txt", "empty.zap");

    std::cout.rdbuf(old);
    assert(not(buffer.str().find("cannot be compressed") == std::string::npos));

    // Cleanup
    remove("empty.txt");
}

// Test 13: Single Character File
void test_single_character()
{
    HuffmanCoder coder;

    // Create test file
    std::ofstream out("single.txt");
    out << "aaaaa";
    out.close();

    // Encode/decode
    coder.encoder("single.txt", "single.zap");
    coder.decoder("single.zap", "single_out.txt");

    // Verify
    std::ifstream decoded("single_out.txt");
    std::string content((std::istreambuf_iterator<char>(decoded)),
                        (std::istreambuf_iterator<char>()));
    assert(content == "aaaaa");

    // Cleanup
    remove("single.txt");
    remove("single.zap");
    remove("single_out.txt");
}

// Test 14: Invalid zap File Handling
void test_invalid_zap_file()
{
    HuffmanCoder coder;
    try
    {
        coder.decoder("corrupt.zap", "corrupt_out.txt");
        assert(false);
    }
    catch (const std::runtime_error &e)
    {
        assert(not(std::string(e.what()).find("invalid") == std::string::npos));
    }
}
// Test 15: Special Characters
void test_special_characters()
{
    HuffmanCoder coder;
    std::string specials = "\n\t\x01\x7F"; // Newline, tab, non-printables

    // Create test file
    std::ofstream out("specials.txt");
    out << specials;
    out.close();

    // Round trip test
    coder.encoder("specials.txt", "specials.zap");
    coder.decoder("specials.zap", "specials_out.txt");

    // Verify
    std::ifstream decoded("specials_out.txt");
    std::string content((std::istreambuf_iterator<char>(decoded)),
                        (std::istreambuf_iterator<char>()));
    assert(content == specials);

    // Cleanup
    remove("specials.txt");
    remove("specials.zap");
    remove("specials_out.txt");
}

#endif // UNIT_TEST_H