#include "unit_test.h"
#include <iostream>

int main()
{
    // Datum Stack tests
    test_DatumStack_constructor();
    test_DatumStack_constructor_with_data();
    test_push();
    test_pop();
    test_pop_empty_stack();
    test_isEmpty();
    test_top();
    test_top_empty_stack();
    test_clear();
    test_size();

    std::cout << "All DatumStack tests passed!" << std::endl;

    // parser tests
    test_parseRString_valid();
    test_parseRString_nested_braces();
    test_parseRString_no_closing_brace();
    test_parseRString_no_opening_brace();
    test_parseRString_empty();
    test_parseRString_spaces();
    test_parseRString_multiline();
    test_parseRString_special_chars();
    test_parseRString_numbers();
    test_parseRString_mixed();

    std::cout << "All Parser tests passed!" << std::endl;

    // RPNCalc tests
    test_RPNCalc_addition();
    test_RPNCalc_subtraction();
    test_RPNCalc_multiplication();
    test_RPNCalc_division();
    test_RPNCalc_division_by_zero();
    test_RPNCalc_comparison();
    test_RPNCalc_if();
    test_RPNCalc_print_empty_stack();
    test_RPNCalc_invalid_operands();
    test_RPNCalc_exec();

    std::cout << "All RPNCalc tests passed!" << std::endl;

    // Done with tests
    std::cout << "All unit tests passed!" << std::endl;
    return 0;
}
