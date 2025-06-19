#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#include "DatumStack.h"
#include "Datum.h"
#include "parser.h"
#include "RPNCalc.h"
#include <iostream>
#include <cassert>
#include <sstream>

/*
 *  unit_test.h
 *  Jack Craig
 *  02/12/2025
 *
 *  CS 15 Project 1: CalcYouLater
 *  Unit tests for the CalcYouLater project.
 *
 */

// Test 1: Default constructor creates an empty stack
void test_DatumStack_constructor()
{
    DatumStack stack;
    assert(stack.isEmpty());
    assert(stack.size() == 0);
}

// Test 2: Constructor with initial data
void test_DatumStack_constructor_with_data()
{
    Datum data[] = {Datum(1), Datum(2), Datum(3)};
    DatumStack stack(data, 3);
    assert(stack.size() == 3);
    assert(stack.top().getInt() == 3);
}

// Test 3: Push a Datum onto the stack
void test_push()
{
    DatumStack stack;
    stack.push(Datum(42));
    assert(stack.size() == 1);
    assert(stack.top().getInt() == 42);
}

// Test 4: Pop a Datum from the stack
void test_pop()
{
    DatumStack stack;
    stack.push(Datum(42));
    Datum d = stack.pop();
    assert(d.getInt() == 42);
    assert(stack.isEmpty());
}

// Test 5: Pop from an empty stack throws an error
void test_pop_empty_stack()
{
    DatumStack stack;
    try
    {
        stack.pop();
        assert(false); // Should not reach here
    }
    catch (const std::runtime_error &e)
    {
        assert(std::string(e.what()) == "empty_stack");
    }
}

// Test 6: Check if the stack is empty
void test_isEmpty()
{
    DatumStack stack;
    assert(stack.isEmpty());
    stack.push(Datum(42));
    assert(!stack.isEmpty());
}

// Test 7: Get the top element without popping
void test_top()
{
    DatumStack stack;
    stack.push(Datum(42));
    assert(stack.top().getInt() == 42);
    assert(stack.size() == 1);
}

// Test 8: Top on an empty stack throws an error
void test_top_empty_stack()
{
    DatumStack stack;
    try
    {
        stack.top();
        assert(false); // Should not reach here
    }
    catch (const std::runtime_error &e)
    {
        assert(std::string(e.what()) == "empty_stack");
    }
}

// Test 9: Clear the stack
void test_clear()
{
    DatumStack stack;
    stack.push(Datum(42));
    stack.push(Datum(43));
    stack.clear();
    assert(stack.isEmpty());
    assert(stack.size() == 0);
}

// Test 10: Get the size of the stack
void test_size()
{
    DatumStack stack;
    assert(stack.size() == 0);
    stack.push(Datum(42));
    assert(stack.size() == 1);
    stack.push(Datum(43));
    assert(stack.size() == 2);
}

// Test 1: Parse a valid rstring
void test_parseRString_valid()
{
    std::istringstream input("{ hello world }");
    Parser parser;
    std::string rstring = parser.parseRString(input);
    assert(rstring == " hello world ");
}

// Test 2: Parse an rstring with nested braces
void test_parseRString_nested_braces()
{
    std::istringstream input("{ { inner } outer }");
    Parser parser;
    std::string rstring = parser.parseRString(input);
    assert(rstring == " { inner } outer ");
}

// Test 3: Parse an rstring with no closing brace throws an error
void test_parseRString_no_closing_brace()
{
    std::istringstream input("{ hello world");
    Parser parser;
    try
    {
        parser.parseRString(input);
        assert(false); // Should not reach here
    }
    catch (const std::runtime_error &e)
    {
        assert(std::string(e.what()) == "Error: missing closing brace for rstring");
    }
}

// Test 4: Parse an rstring with no opening brace throws an error
void test_parseRString_no_opening_brace()
{
    std::istringstream input("hello world }");
    Parser parser;
    try
    {
        parser.parseRString(input);
        assert(false); // Should not reach here
    }
    catch (const std::runtime_error &e)
    {
        assert(std::string(e.what()) == "Error: missing opening brace for rstring");
    }
}

// Test 5: Parse an empty rstring
void test_parseRString_empty()
{
    std::istringstream input("{ }");
    Parser parser;
    std::string rstring = parser.parseRString(input);
    assert(rstring == " ");
}

// Test 6: Parse an rstring with only spaces
void test_parseRString_spaces()
{
    std::istringstream input("{    }");
    Parser parser;
    std::string rstring = parser.parseRString(input);
    assert(rstring == "    ");
}

// Test 7: Parse an rstring with multiple lines
void test_parseRString_multiline()
{
    std::istringstream input("{ line1\nline2 }");
    Parser parser;
    std::string rstring = parser.parseRString(input);
    assert(rstring == " line1\nline2 ");
}

// Test 8: Parse an rstring with special characters
void test_parseRString_special_chars()
{
    std::istringstream input("{ !@#$%^&*() }");
    Parser parser;
    std::string rstring = parser.parseRString(input);
    assert(rstring == " !@#$%^&*() ");
}

// Test 9: Parse an rstring with numbers
void test_parseRString_numbers()
{
    std::istringstream input("{ 123 456 }");
    Parser parser;
    std::string rstring = parser.parseRString(input);
    assert(rstring == " 123 456 ");
}

// Test 10: Parse an rstring with mixed content
void test_parseRString_mixed()
{
    std::istringstream input("{ hello 123 { inner } }");
    Parser parser;
    std::string rstring = parser.parseRString(input);
    assert(rstring == " hello 123 { inner } ");
}

// Test 1: Simple arithmetic (3 + 4)
void test_RPNCalc_addition()
{
    std::istringstream input("3 4 + print\nquit\n");
    std::ostringstream output;
    RPNCalc calc;
    calc.run(input);
    // Expected output: 7
}

// Test 2: Subtraction (5 - 3)
void test_RPNCalc_subtraction()
{
    std::istringstream input("5 3 - print\nquit\n");
    std::ostringstream output;
    RPNCalc calc;
    calc.run(input);
    // Expected output: 2
}

// Test 3: Multiplication (2 * 3)
void test_RPNCalc_multiplication()
{
    std::istringstream input("2 3 * print\nquit\n");
    std::ostringstream output;
    RPNCalc calc;
    calc.run(input);
    // Expected output: 6
}

// Test 4: Division (6 / 2)
void test_RPNCalc_division()
{
    std::istringstream input("6 2 / print\nquit\n");
    std::ostringstream output;
    RPNCalc calc;
    calc.run(input);
    // Expected output: 3
}

// Test 5: Division by zero (6 / 0)
void test_RPNCalc_division_by_zero()
{
    std::istringstream input("6 0 / print\nquit\n");
    std::ostringstream output;
    RPNCalc calc;
    calc.run(input);
    // Expected output: Error: division by zero
}

// Test 6: Comparison (3 < 4)
void test_RPNCalc_comparison()
{
    std::istringstream input("3 4 < print\nquit\n");
    std::ostringstream output;
    RPNCalc calc;
    calc.run(input);
    // Expected output: true
}

// Test 7: If command (3 < 4 ? 1 : 0)
void test_RPNCalc_if()
{
    std::istringstream input("3 4 < { 1 } { 0 } if print\nquit\n");
    std::ostringstream output;
    RPNCalc calc;
    calc.run(input);
    // Expected output: 1
}

// Test 8: Print on empty stack
void test_RPNCalc_print_empty_stack()
{
    std::istringstream input("print\nquit\n");
    std::ostringstream output;
    RPNCalc calc;
    calc.run(input);
    // Expected output: Error: empty stack
}

// Test 9: Invalid operands (3 + hello)
void test_RPNCalc_invalid_operands()
{
    std::istringstream input("3 hello + print\nquit\n");
    std::ostringstream output;
    RPNCalc calc;
    calc.run(input);
    // Expected output: Error: invalid operands for +
}

// Test 10: Exec command ({ 3 4 + } exec)
void test_RPNCalc_exec()
{
    std::istringstream input("{ 3 4 + } exec print\nquit\n");
    std::ostringstream output;
    RPNCalc calc;
    calc.run(input);
    // Expected output: 7
}

#endif // UNIT_TEST_H