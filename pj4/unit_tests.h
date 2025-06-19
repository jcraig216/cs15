#ifndef UNIT_TESTS_H
#define UNIT_TESTS_H

#include "processing.h"
#include "gerp.h"
#include "index.h"
#include <cassert>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <atomic>
#include <thread>
#include <chrono>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdio>

// ======================== STRING SANITIZATION ========================
void test_strip_empty()
{
    assert(stripNonAlphaNum("") == "");
}

void test_strip_all_non_alnum()
{
    assert(stripNonAlphaNum("$$$") == "");
    assert(stripNonAlphaNum("day--") == "day");
}

void test_strip_mixed()
{
    assert(stripNonAlphaNum("!!comp15!!") == "comp15");
}

void test_strip_no_strip()
{
    assert(stripNonAlphaNum("hello123") == "hello123");
}

void test_strip_edge_case()
{
    assert(stripNonAlphaNum("***a***") == "a");
}

void test_strip_internal_non_alnum()
{
    assert(stripNonAlphaNum("don't") == "don't");
    assert(stripNonAlphaNum("user-name") == "user-name");
}

void test_strip_numbers_only()
{
    assert(stripNonAlphaNum("12345") == "12345");
}

void test_strip_single_char()
{
    assert(stripNonAlphaNum("a") == "a");
    assert(stripNonAlphaNum("!") == "");
}

// ======================== DIRECTORY TRAVERSAL ========================
void test_traverse_basic()
{
    mkdir("test_tinyData", 0777);
    mkdir("test_tinyData/subdir", 0777);
    std::ofstream("test_tinyData/file1.txt").close();
    std::ofstream("test_tinyData/subdir/file2.txt").close();

    std::streambuf *original = std::cout.rdbuf();
    std::stringstream buffer;
    std::cout.rdbuf(buffer.rdbuf());
    traverseDirectory("test_tinyData");

    std::vector<std::string> outputLines;
    std::string line;
    while (std::getline(buffer, line))
        outputLines.push_back(line);

    remove("test_tinyData/subdir/file2.txt");
    remove("test_tinyData/file1.txt");
    rmdir("test_tinyData/subdir");
    rmdir("test_tinyData");
    std::cout.rdbuf(original);

    assert(not(std::find(outputLines.begin(), outputLines.end(),
                         "test_tinyData/file1.txt") == outputLines.end()));
}

void test_traverse_empty()
{
    mkdir("test_empty_dir", 0777);
    std::streambuf *original = std::cout.rdbuf();
    std::stringstream buffer;
    std::cout.rdbuf(buffer.rdbuf());
    traverseDirectory("test_empty_dir");
    std::cout.rdbuf(original);
    rmdir("test_empty_dir");
    assert(buffer.str().empty());
}

void test_traverse_hidden_files()
{
    mkdir("test_hidden", 0777);
    std::ofstream("test_hidden/.gitignore").close();
    std::streambuf *original = std::cout.rdbuf();
    std::stringstream buffer;
    std::cout.rdbuf(buffer.rdbuf());
    traverseDirectory("test_hidden");
    std::cout.rdbuf(original);
    remove("test_hidden/.gitignore");
    rmdir("test_hidden");
    assert(not(buffer.str().find(".gitignore") == std::string::npos));
}

// ======================== INDEXING & SEARCH ========================
void test_indexing_performance()
{
    Index idx;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i)
        idx.addLine("dummy_path", i, "Line_" + std::to_string(i));
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::high_resolution_clock::now() - start);
    assert(duration.count() < 50);
}

void test_large_index_performance()
{
    Index idx;
    for (int i = 0; i < 100000; ++i)
        idx.addLine("file" + std::to_string(i % 100), i,
                    "line_" + std::to_string(i));
    assert(idx.searchCaseSensitive("line_99999").size() == 1);
}

void test_index_duplicate_lines()
{
    Index idx;
    idx.addLine("file1", 1, "Hello");
    idx.addLine("file2", 1, "Hello");
    assert(idx.searchCaseSensitive("Hello").size() == 2);
}

void test_index_empty_lines()
{
    Index idx;
    idx.addLine("file", 1, "");
    assert(idx.searchCaseSensitive("").empty());
}

void test_index_special_chars_in_words()
{
    Index idx;
    idx.addLine("file", 1, "c++_is_fun!");
    assert(not(idx.searchCaseSensitive("c++_is_fun").empty()));
}

void test_search_exact_match()
{
    Index idx;
    idx.addLine("file", 1, "CS15");
    assert(not(idx.searchCaseSensitive("CS15").empty()));
}

void test_search_partial_match_no_results()
{
    Index idx;
    idx.addLine("file", 1, "computer");
    assert(idx.searchCaseSensitive("comp").empty());
}

void test_search_case_insensitive_multiple()
{
    Index idx;
    idx.addLine("file", 1, "Hello");
    idx.addLine("file", 2, "HELLO");
    assert(idx.searchCaseInsensitive("hello").size() == 2);
}

// ======================== COMMAND PROCESSING ========================
void test_command_prompt()
{
    mkdir("test_prompt_dir", 0777);
    std::ofstream("test_prompt_dir/test_file.txt").close();
    Gerp gerp;
    std::atomic<bool> prompt_shown{false};
    std::thread t([&]()
                  { gerp.buildIndex("test_prompt_dir"); 
                  gerp.run("test_output.txt"); });
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::ofstream cmd("test_input.txt");
    cmd << "@q\n";
    cmd.close();
    freopen("test_input.txt", "r", stdin);
    t.join();
    remove("test_input.txt");
    remove("test_output.txt");
    remove("test_prompt_dir/test_file.txt");
    rmdir("test_prompt_dir");
    assert(prompt_shown);
}

void test_command_invalid()
{
    std::stringstream input("@invalid\n@q\n");
    std::streambuf *orig = std::cin.rdbuf(input.rdbuf());
    Gerp gerp;
    gerp.run("output.txt");
    std::cin.rdbuf(orig);
}

void test_command_missing_filename()
{
    std::stringstream input("@f\n@q\n");
    std::streambuf *orig = std::cin.rdbuf(input.rdbuf());
    Gerp gerp;
    gerp.run("output.txt");
    std::cin.rdbuf(orig);
}

// ======================== ERROR HANDLING ========================
void test_error_permission_denied()
{
    std::ofstream("readonly.txt").close();
    chmod("readonly.txt", 0444); // Read-only

    Gerp gerp;
    std::stringstream input("@f readonly.txt\n@q\n");
    std::streambuf *orig = std::cin.rdbuf(input.rdbuf());

    // Redirect cerr to capture error message
    std::stringstream errorBuffer;
    std::streambuf *origErr = std::cerr.rdbuf(errorBuffer.rdbuf());

    gerp.run("dummy_output.txt");
    std::cerr.rdbuf(origErr);
    std::cin.rdbuf(orig);

    assert(not(errorBuffer.str().find("Failed to open") ==
               std::string::npos));
    chmod("readonly.txt", 0644);
    remove("readonly.txt");
}

// ======================== MEMORY MANAGEMENT ========================
void test_memory_leak_index()
{
    Index *idx = new Index();
    for (int i = 0; i < 1000; i++)
        idx->addLine("file", i, "line" + std::to_string(i));
    delete idx;
}

// ======================== EXTRA TESTS ========================
void test_file_switch_valid()
{
    Gerp gerp;
    std::stringstream input("@f valid.txt\n@q\n");
    std::streambuf *orig = std::cin.rdbuf(input.rdbuf());

    gerp.run("dummy_output.txt");
    std::ifstream newFile("valid.txt");
    assert(newFile.good()); // Verify file was created
    newFile.close();
    remove("valid.txt");
    std::cin.rdbuf(orig);
}

void test_empty_file_processing()
{
    Gerp gerp;
    mkdir("test_empty", 0777);
    std::ofstream("test_empty/empty.txt").close();

    // Use public API to test
    gerp.buildIndex("test_empty");
    std::stringstream input(" \n@q\n"); // Query empty string
    std::streambuf *orig = std::cin.rdbuf(input.rdbuf());

    // Redirect output
    std::ofstream out("test_output.txt");
    std::streambuf *coutBuf = std::cout.rdbuf(out.rdbuf());

    gerp.run("test_output.txt");
    std::cout.rdbuf(coutBuf);
    std::cin.rdbuf(orig);

    // Check output file
    std::ifstream result("test_output.txt");
    std::string line;
    bool found = false;
    while (std::getline(result, line))
    {
        if (not(line.find("Not Found") == std::string::npos))
            found = true;
    }
    assert(found);

    remove("test_empty/empty.txt");
    rmdir("test_empty");
    remove("test_output.txt");
}

#endif // UNIT_TESTS_H