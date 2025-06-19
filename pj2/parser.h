#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <istream>

class Parser
{
public:
    std::string parseRString(std::istream &input);
};

#endif // PARSER_H