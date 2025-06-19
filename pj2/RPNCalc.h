/*
 *  RPNCalc.h
 *  Jack Craig
 *  02/26/2025
 *
 *  CS 15 Project 2: CalcYouLater
 *  Executes commands using the Stack and Parser.
 *
 */

#ifndef RPNCALC_H
#define RPNCALC_H

#include "DatumStack.h"
#include "parser.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdexcept>

class RPNCalc
{
private:
    DatumStack stack;
    Parser parser;

    void processCommand(const std::string &command);
    void executeRString(const std::string &rstring);
    void handleArithmetic(const std::string &op);
    void handleComparison(const std::string &op);
    void handleIf();
    void handlePrint();
    void handleError(const std::string &message);
    void handleDrop();
    void handleDup();
    void handleSwap();
    void handleNot();
    void handleClear();

public:
    RPNCalc() = default;
    void run();
    void run(std::istream &input);
};

#endif // RPNCALC_H