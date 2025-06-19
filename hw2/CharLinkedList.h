/*
 *  CharLinkedList.h
 *  Jack Craig jcraig05
 *  01/28/2025
 *
 *  CS 15 HW 2 Cheshire ConCATenation - Time to get linked up in Fur
 *
 *  This class is the implementation of a linked list ADT
 *
 */

#ifndef CHAR_LINKED_LIST_H
#define CHAR_LINKED_LIST_H

#include <string>

class CharLinkedList
{

public:
    CharLinkedList();
    CharLinkedList(char c);
    CharLinkedList(char arr[], int size);
    CharLinkedList(const CharLinkedList &other);

    ~CharLinkedList();

    CharLinkedList &operator=(const CharLinkedList &other);

    bool isEmpty() const;
    void clear();
    int size() const;
    char first() const;
    char last() const;
    char elementAt(int index) const;

    std::string toString() const;
    std::string toReverseString() const;

    void pushAtBack(char c);
    void pushAtFront(char c);
    void insertAt(char c, int index);
    void insertInOrder(char c);
    void popFromFront();
    void popFromBack();
    void removeAt(int index);
    void replaceAt(char c, int index);
    void concatenate(CharLinkedList *other);

private:
    struct Node
    {
        char data;
        Node *next;
    };

    Node *front;
    int numItems;

    Node *newNode(char data, Node *next);
    void toReverseStringHelper(std::stringstream &ss, Node *curr) const;
    void replaceAtHelper(Node *curr, char c, int index);
};
#endif
