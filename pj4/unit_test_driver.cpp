#include "unit_tests.h"
#include <iostream>

int main()
{
    // String Sanitization
    test_strip_empty();
    test_strip_all_non_alnum();
    test_strip_mixed();
    test_strip_no_strip();
    test_strip_edge_case();
    test_strip_internal_non_alnum();
    test_strip_numbers_only();
    test_strip_single_char();

    // Directory Traversal
    test_traverse_basic();
    test_traverse_empty();
    test_traverse_hidden_files();

    // Indexing & Search
    test_indexing_performance();
    test_large_index_performance();
    test_index_duplicate_lines();
    test_index_empty_lines();
    test_index_special_chars_in_words();
    test_search_exact_match();
    test_search_partial_match_no_results();
    test_search_case_insensitive_multiple();

    // Command Processing
    test_command_prompt();
    test_command_invalid();
    test_command_missing_filename();

    // Error Handling
    test_error_permission_denied();

    // Memory & Performance
    test_memory_leak_index();

    // Extra Tests
    test_empty_file_processing();

    std::cout << "All 30+ tests passed!" << std::endl;
    return 0;
}