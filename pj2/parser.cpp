#include "parser.h"
#include <sstream>
#include <stdexcept>

/*
 * name:      parseRString()
 * purpose:   Parse an rstring from the input stream.
 * arguments: Input stream to read from.
 * returns:   The parsed rstring.
 * effects:   Reads input until a complete rstring is found.
 */
std::string Parser::parseRString(std::istream &input)
{
    std::string rstring = "{"; // Start with '{'
    char ch;
    int braceCount = 1;

    while (input.get(ch))
    {
        rstring += ch;
        if (ch == '{')
            braceCount++;
        else if (ch == '}')
        {
            braceCount--;
            if (braceCount == 0)
                break; // Stop after matching '}'
        }
    }

    if (braceCount != 0)
    {
        throw std::runtime_error("Error: rstring braces don't match");
    }
    return rstring; // Returns "{ 3 4 + }"
}
