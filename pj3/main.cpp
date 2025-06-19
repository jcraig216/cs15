/*
 *  main.cpp
 *  Jack Craig
 *  03/15/2025
 *
 *  CS 15 Project 3: Zap
 *  Command-line interface for compression/decompression
 *  using Huffman coding.
 *
 */

#include "HuffmanCoder.h"
#include <iostream>
#include <stdexcept>

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        std::cerr << "Usage: ./zap [zap | unzap] inputFile outputFile\n";
        return EXIT_FAILURE;
    }

    HuffmanCoder coder;
    std::string command(argv[1]);
    std::string input(argv[2]);
    std::string output(argv[3]);

    try
    {
        if (command == "zap")
        {
            coder.encoder(input, output);
        }
        else if (command == "unzap")
        {
            coder.decoder(input, output);
        }
        else
        {
            std::cerr << "Usage: ./zap [zap | unzap] inputFile outputFile\n";
            return EXIT_FAILURE;
        }
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}