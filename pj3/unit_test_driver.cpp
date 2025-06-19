#include "unit_tests.h"
#include <iostream>

int main()
{
    // Phase 1 tests
    test_count_freqs_empty();
    test_count_freqs_single_char();
    test_count_freqs_whitespace();
    test_serialize_single_node();
    test_serialize_simple_tree();
    test_deserialize_single_node();
    test_deserialize_nested_tree();

    test_deserialize_invalid();

    // Phase 2 tests
    test_round_trip_basic();
    test_empty_file();
    test_single_character();
    test_invalid_zap_file();
    test_special_characters();

    // Done with tests
    std::cout << "All tests passed!\n";
    return 0;
}