// These includes are necessary for got_int( )
#include <string>
#include <cstdio>

#include "RPNCalc.h"
#include <vector>

using namespace std;

/*
 * Name: got_int
 * Purpose:    determines whether a string contains an encoding of an
 *             integer value and loads said integer into an integer
 *             variable whose address has been passed to this function.
 *             An integer encoding contains an optional sign and
 *             a sequence of digits.  Extraneous whitespace is
 *             ignored.
 * Parameters: s contains a string that might encode an integer.
 *             resultp contains the address of an integer variable to
 *             store the integer from s in, should the conversion
 *             succeed.
 *             can be parsed from said string
 * Returns:    true if an integer was successfully parsed from the
 *             provided string;
 *             false otherwise (s did not contain a valid integer
 *             encoding)
 * Effects:    *resultp will be set the integer value encoded by s
 *             on success; otherwise it is undetermined (may be set
 *             if there are extra characters after digits)
 *
 * Author: Mark A. Sheldon, Tufts University, Fall 2016
 * Note to students: you do not have to modify this commentnot
 */
bool got_int(string s, int *resultp)
{
    char extra; /* Holds first non-whitespace character after integer */
                /* Should not match anything:  want "3." to fail      */
    return sscanf(s.c_str(), " %d %c", resultp, &extra) == 1;
}

/*
 * Name: run
 * Purpose: Starts the RPN calculator in user input mode, reading commands
 * from standard input.
 * Parameters: None.
 * Returns: None.
 * Effects: Continuously reads and processes commands until the user enters
 * "quit".
 */
void RPNCalc::run()
{
    run(std::cin);
}

/*
 * Name: run
 * Purpose: Starts the RPN calculator, reading commands from the provided
 * input stream.
 * Parameters: input: The input stream to read commands from.
 * Returns: None.
 * Effects: Continuously reads and processes commands until the end of the
 *  input stream or "quit" is encountered.
 */
void RPNCalc::run(std::istream &input)
{
    std::string command;
    while (true)
    {
        if (not std::getline(input, command))
            break;

        if (command == "quit")
        {
            std::cerr << "Thank you for using CalcYouLater.\n";
            return;
        }
        else
        {
            processCommand(command);
        }
    }
}

/*
 * Name: processCommand
 * Purpose: Processes a single command by tokenizing it and executing
 * the correct operation.
 * Parameters: command: The command string to process.
 * Returns: None.
 * Effects: Executes the command, modifying the stack or producing output
 * as necessary.
 */
void RPNCalc::processCommand(const std::string &command)
{
    std::istringstream iss(command);
    std::string token;
    DatumStack originalStack = stack;
    bool errorOccurred = false;

    while (iss >> token)
    {
        try
        {
            if (token == "+" or token == "-" or token == "*" or token == "/")
            {
                handleArithmetic(token);
            }
            else if (token == "<" or token == ">" or token == "==")
            {
                handleComparison(token);
            }
            else if (token == "if")
            {
                handleIf();
            }
            else if (token == "print")
            {
                handlePrint();
            }
            else if (token == "{")
            {
                std::string rstring = parser.parseRString(iss);
                stack.push(Datum(rstring.c_str()));
            }
            else if (token == "drop")
            {
                handleDrop();
            }
            else if (token == "dup")
            {
                handleDup();
            }
            else if (token == "swap")
            {
                handleSwap();
            }
            else if (token == "not")
            {
                handleNot();
            }
            else if (token == "clear")
            {
                handleClear();
            }
            else if (token == "#t")
            {
                stack.push(Datum(true));
            }
            else if (token == "#f")
            {
                stack.push(Datum(false));
            }
            else if (token == "exec")
            {
                if (stack.isEmpty())
                {
                    handleError("Error: empty_stack");
                }
                else
                {
                    Datum rstringDatum = stack.pop();
                    if (rstringDatum.isRString())
                    {
                        std::string rstring = rstringDatum.getRString();
                        std::istringstream rss(rstring);
                        executeRString(rstring);
                    }
                    else
                    {
                        handleError("Error: expected rstring for exec");
                    }
                }
            }
            else if (token == "file")
            {
                if (stack.isEmpty())
                {
                    throw std::runtime_error("Error: empty stack");
                }
                Datum filenameDatum = stack.pop();
                if (not(filenameDatum.isRString()))
                {
                    throw std::runtime_error("Error: expected rstring for file");
                }
                std::string rstring = filenameDatum.getRString();

                // Strip braces from the rstring
                if (rstring.size() < 2 or not(rstring.front() == '{') or not(rstring.back() == '}'))
                {
                    throw std::runtime_error("Error: malformed rstring for filename");
                }
                std::string filename = rstring.substr(1, rstring.size() - 2);

                size_t start = filename.find_first_not_of(" \t");
                size_t end = filename.find_last_not_of(" \t");
                if (start == std::string::npos)
                {
                    throw std::runtime_error("Error: malformed rstring for filename");
                }
                filename = filename.substr(start, end - start + 1);

                std::ifstream file(filename);
                if (not(file.is_open()))
                {
                    throw std::runtime_error("Error: unable to open " + filename + ".");
                }
                run(file);
            }
            else
            {

                int val;
                if (got_int(token, &val))
                {
                    stack.push(Datum(val));
                }
                else
                {
                    handleError(token + ": unimplemented");
                    errorOccurred = true;
                }
            }
        }
        catch (const std::runtime_error &e)
        {
            handleError(e.what());
            errorOccurred = true;
        }
    }

    if (errorOccurred)
    {
        stack = originalStack;
    }
}

/*
 * Name: executeRString
 * Purpose: Executes the commands contained within an rstring.
 * Parameters: rstring: The rstring containing commands to execute.
 * Returns: None.
 * Effects: Processes each command in the rstring, modifying the stack
 * or producing output as necessary.
 */
void RPNCalc::executeRString(const std::string &rstring)
{

    if (rstring.empty() or not(rstring.front() == '{') or not(rstring.back() == '}'))
    {
        handleError("Error: malformed rstring");
        return;
    }
    std::string content = rstring.substr(1, rstring.size() - 2);
    std::istringstream iss(content);
    std::string command;
    while (std::getline(iss, command))
    {
        processCommand(command);
    }
}

/*
 * Name: handleArithmetic
 * Purpose: Perform arithmetic operation on top two integers.
 * Parameters: op - The operator (+, -, *, /).
 * Effects: Pops two integers, computes result, and pushes it.
 * Throws: "empty_stack" if <2 elements, "invalid operands" if non-integer.
 */
void RPNCalc::handleArithmetic(const std::string &op)
{
    if (stack.size() < 2)
    {
        stack.clear();

        throw std::runtime_error("Error: empty_stack");
    }

    Datum d1 = stack.pop();
    Datum d2 = stack.pop();

    if (not(d1.isInt()) or not(d2.isInt()))
    {
        stack.push(d2);
        stack.push(d1);
        stack.pop();
        stack.pop();
        throw std::runtime_error("Error: invalid operands for " + op);
    }

    if (op == "/" and d1.getInt() == 0)
    {
        stack.push(d2);
        stack.push(d1);
        stack.pop();
        stack.pop();
        throw std::runtime_error("Error: division by 0.");
    }

    int result = 0;
    if (op == "+")
    {
        result = d2.getInt() + d1.getInt();
    }
    else if (op == "-")
    {
        result = d2.getInt() - d1.getInt();
    }
    else if (op == "*")
    {
        result = d2.getInt() * d1.getInt();
    }
    else if (op == "/")
    {
        if (d1.getInt() == 0)
        {
            stack.push(d2);
            stack.push(d1);
            handleError("Error: division by 0.");
        }
        result = d2.getInt() / d1.getInt();
    }
    stack.push(Datum(result));
}

/*
 * Name: handleComparison
 * Purpose: Compare top two integers and push boolean result.
 * Parameters: op - The operator (<, >, ==).
 * Effects: Pops two integers, compares them, and pushes boolean.
 * Throws: "empty_stack" if <2 elements, "invalid operands" if non-integer.
 */
void RPNCalc::handleComparison(const std::string &op)
{
    try
    {
        Datum d1 = stack.pop();
        Datum d2 = stack.pop();
        if (d1.isInt() and d2.isInt())
        {
            bool result = false;
            if (op == "<")
                result = d2.getInt() < d1.getInt();
            else if (op == ">")
                result = d2.getInt() > d1.getInt();
            else if (op == "==")
                result = d2.getInt() == d1.getInt();
            stack.push(Datum(result));
        }
        else
        {
            throw std::runtime_error("Error: invalid operands for " + op);
        }
    }
    catch (const std::runtime_error &e)
    {
        handleError(e.what());
    }
}

/*
 * Name: handleIf
 * Purpose: Execute conditional block based on top boolean.
 * Effects: Pops condition, true-block, false-block. Executes rstring based on condition.
 * Throws: "empty_stack" if <3 elements, "expected boolean" or "expected rstring" on type errors.
 */
void RPNCalc::handleIf()
{
    if (stack.size() < 3)
    {
        handleError("Error: empty stack");
        return;
    }

    Datum falseBlock = stack.pop();
    Datum trueBlock = stack.pop();
    Datum condition = stack.pop();

    if (not(condition.isBool()))
    {
        handleError("Error: expected boolean in if test");
        stack.push(condition);
        stack.push(trueBlock);
        stack.push(falseBlock);
        return;
    }

    if (not(trueBlock.isRString()) or not(falseBlock.isRString()))
    {
        handleError("Error: expected rstring in if branch");
        stack.push(condition);
        stack.push(trueBlock);
        stack.push(falseBlock);
        return;
    }

    if (condition.getBool())
    {
        executeRString(trueBlock.getRString());
    }
    else
    {
        executeRString(falseBlock.getRString());
    }
}

/*
 * Name: handlePrint
 * Purpose: Handles the "print" command by popping the top element
 * from the stack and printing it.
 * Parameters: None.
 * Returns: None.
 * Effects: Modifies the stack by popping the top element. Prints the
 * element to standard output. Throws an error if the stack is empty.
 */
/*
 * Name: handlePrint
 * Purpose: Print the top element of the stack without popping it.
 * Effects: Outputs the top element to std::cout. Booleans are formatted as #t/#f.
 * Throws: "empty_stack" if stack is empty.
 */
void RPNCalc::handlePrint()
{
    if (stack.isEmpty())
    {
        handleError("Error: empty_stack");
        return;
    }
    const Datum &d = stack.top(); // Do NOT pop the element

    if (d.isBool())
    {
        std::cout << (d.getBool() ? "#t" : "#f") << std::endl;
    }
    else
    {
        std::cout << d.toString() << std::endl;
    }
}
/*
 * Name: handleError
 * Purpose: Handles errors by printing an error message to standard error.
 * Parameters: message - The error message to print.
 * Returns: None.
 * Effects: Prints the error message to standard error.
 */
void RPNCalc::handleError(const std::string &message)
{
    std::cerr << message << std::endl;
}
/*
 * Name: handleDrop
 * Purpose: Remove the top element from the stack.
 * Effects: Stack size decreases by 1.
 * Throws: "empty_stack" if stack is empty.
 */
void RPNCalc::handleDrop()
{
    if (stack.isEmpty())
    {
        throw std::runtime_error("Error: empty_stack");
    }
    stack.pop();
}
/*
 * Name: handleDup
 * Purpose: Duplicate the top element of the stack.
 * Effects: Stack size increases by 1.
 * Throws: "empty_stack" if stack is empty.
 */
void RPNCalc::handleDup()
{
    if (stack.isEmpty())
    {
        throw std::runtime_error("Error: empty_stack");
    }
    Datum top = stack.top();
    stack.push(top);
}
/*
 * Name: handleSwap
 * Purpose: Swap the top two elements of the stack.
 * Effects: Order of top two elements is reversed.
 * Throws: "empty_stack" if <2 elements.
 */
void RPNCalc::handleSwap()
{
    if (stack.size() < 2)
    {
        throw std::runtime_error("Error: empty_stack");
    }
    Datum a = stack.pop();
    Datum b = stack.pop();
    stack.push(a);
    stack.push(b);
}
/*
 * Name: handleNot
 * Purpose: Negate the top boolean element of the stack.
 * Effects: Pops the boolean, pushes its negation.
 * Throws: "empty_stack" if empty, "expected boolean" if non-boolean.
 */
void RPNCalc::handleNot()
{
    if (stack.isEmpty())
    {
        throw std::runtime_error("Error: empty_stack");
    }
    Datum d = stack.pop();
    if (not(d.isBool()))
    {
        stack.push(d); // Restore the element
        throw std::runtime_error("Error: expected boolean for not");
    }
    stack.push(Datum(not(d.getBool())));
}
/*
 * Name: handleClear
 * Purpose: Empty the stack.
 * Effects: Stack becomes empty.
 */
void RPNCalc::handleClear()
{
    stack.clear();
}
