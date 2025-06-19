/*
 *  unit_tests.h
 *  YOUR NAME HERE
 *  DATE CREATED
 *
 *  CS 15 HW 2 Cheshire ConCATenation - Time to linked up in Fur
 *x
 *  FILE PURPOSE HERE
 *
 */
#include <cassert>

#include "CharLinkedList.h"

void pushAtBack_empty_correct()
{
    CharLinkedList test_list;
    test_list.pushAtBack('a');
    test_list.pushAtBack('b');
    test_list.pushAtBack('c');
    assert(test_list.size() == 3);
    assert(test_list.elementAt(2) == 'c');
}

void pushAtFront_empty_correct()
{
    CharLinkedList test_list;
    test_list.pushAtFront('a');
    assert(test_list.size() == 1);
    assert(test_list.elementAt(0) == 'a');
}

void popFromFront_empty_correct()
{
    CharLinkedList test_list;
    test_list.pushAtFront('a');
    test_list.pushAtFront('b');
    test_list.pushAtFront('c');
    assert(test_list.size() == 3);
    test_list.popFromFront();
    assert(test_list.size() == 2);
    assert(test_list.elementAt(0) == 'b');
}

void popFromBack_empty_correct()
{
    CharLinkedList test_list;
    test_list.pushAtFront('a');
    test_list.pushAtFront('b');
    test_list.pushAtFront('c');
    assert(test_list.size() == 3);
    test_list.popFromBack();
    assert(test_list.size() == 2);
    assert(test_list.elementAt(1) == 'b');
}

void removeAt_empty_correct()
{
    CharLinkedList test_list;
    test_list.pushAtFront('a');
    test_list.pushAtFront('b');
    test_list.pushAtFront('c');
    assert(test_list.size() == 3);
    test_list.removeAt(0);
    assert(test_list.size() == 2);
    assert(test_list.elementAt(0) == 'b');
}

void replaceAt_empty_correct()
{
    CharLinkedList test_list;
    test_list.pushAtFront('a');
    test_list.pushAtFront('b');
    test_list.pushAtFront('c');
    test_list.replaceAt('e', 2);
    assert(test_list.size() == 3);
    assert(test_list.elementAt(2) == 'e');
}

void clear_empty_correct()
{
    CharLinkedList test_list;
    test_list.pushAtFront('a');
    test_list.pushAtFront('b');
    test_list.pushAtFront('c');
    assert(test_list.size() == 3);
    test_list.clear();
    assert(test_list.size() == 0);
}

void first_empty_correct()
{
    CharLinkedList test_list;
    test_list.pushAtFront('a');
    test_list.pushAtFront('b');
    test_list.pushAtFront('c');
    assert(test_list.size() == 3);
    assert(test_list.first() == 'c');
}

void last_empty_correct()
{
    CharLinkedList test_list;
    test_list.pushAtFront('a');
    test_list.pushAtFront('b');
    test_list.pushAtFront('c');
    assert(test_list.size() == 3);
    assert(test_list.last() == 'a');
}

void concatenate_test()
{
    char test_arr1[3] = {'c', 'a', 't'};
    char test_arr2[8] = {'C', 'H', 'E', 'S', 'H', 'I', 'R', 'E'};

    CharLinkedList list1(test_arr1, 3);
    CharLinkedList list2(test_arr2, 8);

    list1.concatenate(&list2);

    assert(list1.size() == 11);
    assert(list1.toString() == "[CharArrayList of size 11 <<catCHESHIRE>>]");
}

void concatenate_test_empty()
{
    char test_arr1[3] = {'d', 'o', 'g'};

    CharLinkedList list1(test_arr1, 3);
    CharLinkedList list2;

    list1.concatenate(&list2);

    assert(list1.size() == 3);
    assert(list1.toString() == "[CharArrayList of size 3 <<dog>>]");
}

void insertAt_out_of_range()
{
    CharLinkedList test_list;
    bool range_error_thrown = false;
    std::string error_message = "";
    try
    {
        test_list.insertAt('a', 42);
    }
    catch (const std::range_error &e)
    {
        range_error_thrown = true;
        error_message = e.what();
    }
    assert(range_error_thrown);
    assert(error_message == "index (42) not in range [0..0]");
}

void insertAt_front_correct()
{
    CharLinkedList test_list('a');
    test_list.insertAt('b', 0);
    assert(test_list.size() == 2);
    assert(test_list.elementAt(0) == 'b');
    assert(test_list.elementAt(1) == 'a');
}

void insertAt_back_correct()
{
    CharLinkedList test_list('a');
    test_list.insertAt('b', 1);
    assert(test_list.size() == 2);
    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
}

void insertAt_middle_correct()
{
    char test_arr[5] = {'a', 'b', 'd', 'e', 'f'};
    CharLinkedList test_list(test_arr, 5);
    test_list.insertAt('c', 2);
    assert(test_list.size() == 6);
    assert(test_list.elementAt(2) == 'c');
}

void insertInOrder_test()
{
    char test_arr[6] = {'a', 'b', 'd', 'e', 'f', 'g'};
    CharLinkedList test_list(test_arr, 6);
    test_list.insertInOrder('c');
    assert(test_list.size() == 7);
    assert(test_list.elementAt(2) == 'c');
    assert(test_list.toString() == "[CharArrayList of size 7 <<abcdefg>>]");
}

void isEmpty_test()
{
    CharLinkedList test_list;
    assert(test_list.isEmpty() == true);
    test_list.pushAtFront('a');
    assert(test_list.isEmpty() == false);
    test_list.popFromFront();
    assert(test_list.isEmpty() == true);
}

void toString_test()
{
    CharLinkedList test_list;
    assert(test_list.toString() == "[CharArrayList of size 0 <<>>]");
    test_list.pushAtFront('a');
    test_list.pushAtFront('b');
    test_list.pushAtFront('c');
    assert(test_list.toString() == "[CharArrayList of size 3 <<cba>>]");
}

void toReverseString_test()
{
    CharLinkedList test_list;
    assert(test_list.toReverseString() == "[CharArrayList of size 0 <<>>]");
    test_list.pushAtFront('a');
    test_list.pushAtFront('b');
    test_list.pushAtFront('c');
    assert(test_list.toReverseString() == "[CharArrayList of size 3 <<abc>>]");
}

void elementAt_out_of_range()
{
    CharLinkedList test_list;
    bool range_error_thrown = false;
    std::string error_message = "";
    try
    {
        test_list.elementAt(42);
    }
    catch (const std::range_error &e)
    {
        range_error_thrown = true;
        error_message = e.what();
    }
    assert(range_error_thrown);
    assert(error_message == "index (42) not in range of [0..0)");
}

void popFromFront_empty_list()
{
    CharLinkedList test_list;
    bool runtime_error_thrown = false;
    std::string error_message = "";
    try
    {
        test_list.popFromFront();
    }
    catch (const std::runtime_error &e)
    {
        runtime_error_thrown = true;
        error_message = e.what();
    }
    assert(runtime_error_thrown);
    assert(error_message == "cannot pop from empty LinkedList");
}

void popFromBack_empty_list()
{
    CharLinkedList test_list;
    bool runtime_error_thrown = false;
    std::string error_message = "";
    try
    {
        test_list.popFromBack();
    }
    catch (const std::runtime_error &e)
    {
        runtime_error_thrown = true;
        error_message = e.what();
    }
    assert(runtime_error_thrown);
    assert(error_message == "cannot pop from empty LinkedList");
}

void replaceAt_out_of_range()
{
    CharLinkedList test_list;
    bool range_error_thrown = false;
    std::string error_message = "";
    try
    {
        test_list.replaceAt('a', 42);
    }
    catch (const std::range_error &e)
    {
        range_error_thrown = true;
        error_message = e.what();
    }
    assert(range_error_thrown);
    assert(error_message == "index (42) not in range [0..0]");
}

void removeAt_out_of_range()
{
    CharLinkedList test_list;
    bool range_error_thrown = false;
    std::string error_message = "";
    try
    {
        test_list.removeAt(42);
    }
    catch (const std::range_error &e)
    {
        range_error_thrown = true;
        error_message = e.what();
    }
    assert(range_error_thrown);
    assert(error_message == "index (42) not in range [0..0]");
}

void insertInOrder_empty_list()
{
    CharLinkedList test_list;
    test_list.insertInOrder('a');
    assert(test_list.size() == 1);
    assert(test_list.elementAt(0) == 'a');
}

void insertInOrder_at_end()
{
    char test_arr[5] = {'a', 'b', 'c', 'd', 'e'};
    CharLinkedList test_list(test_arr, 5);
    test_list.insertInOrder('f');
    assert(test_list.size() == 6);
    assert(test_list.elementAt(5) == 'f');
}

void insertInOrder_at_beginning()
{
    char test_arr[5] = {'b', 'c', 'd', 'e', 'f'};
    CharLinkedList test_list(test_arr, 5);
    test_list.insertInOrder('a');
    assert(test_list.size() == 6);
    assert(test_list.elementAt(0) == 'a');
}

void concatenate_both_empty()
{
    CharLinkedList list1;
    CharLinkedList list2;
    list1.concatenate(&list2);
    assert(list1.size() == 0);
    assert(list1.toString() == "[CharArrayList of size 0 <<>>]");
}

void concatenate_first_empty()
{
    char test_arr[5] = {'a', 'b', 'c', 'd', 'e'};
    CharLinkedList list1;
    CharLinkedList list2(test_arr, 5);
    list1.concatenate(&list2);
    assert(list1.size() == 5);
    assert(list1.toString() == "[CharArrayList of size 5 <<abcde>>]");
}

void concatenate_second_empty()
{
    char test_arr[5] = {'a', 'b', 'c', 'd', 'e'};
    CharLinkedList list1(test_arr, 5);
    CharLinkedList list2;
    list1.concatenate(&list2);
    assert(list1.size() == 5);
    assert(list1.toString() == "[CharArrayList of size 5 <<abcde>>]");
}

void clear_empty_list()
{
    CharLinkedList test_list;
    test_list.clear();
    assert(test_list.size() == 0);
    assert(test_list.toString() == "[CharArrayList of size 0 <<>>]");
}

void first_empty_list()
{
    CharLinkedList test_list;
    bool runtime_error_thrown = false;
    std::string error_message = "";
    try
    {
        test_list.first();
    }
    catch (const std::runtime_error &e)
    {
        runtime_error_thrown = true;
        error_message = e.what();
    }
    assert(runtime_error_thrown);
    assert(error_message == "cannot get first of empty LinkedList");
}

void last_empty_list()
{
    CharLinkedList test_list;
    bool runtime_error_thrown = false;
    std::string error_message = "";
    try
    {
        test_list.last();
    }
    catch (const std::runtime_error &e)
    {
        runtime_error_thrown = true;
        error_message = e.what();
    }
    assert(runtime_error_thrown);
    assert(error_message == "cannot get last of empty LinkedList");
}