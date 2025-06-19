
/*
 * Filename: Sorter.h
 * Part of: Lab assignment "Sorting" for COMP 15 Spring 2020
 *
 * Defines a Sorter class, including a parameterized constrcutor that specifies
 * a vector of ints and the named sorting algorithm. Can also check to see if 
 * its associated Data is sorted and print out that data.
 *
 *
 * Edited: John Cha (jcha04) 4/21/2024
 *         - cleaned up function contracts. Also created the class.
 *
 */



#ifndef SORTER__H
#define SORTER__H

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

/* Helpful constants */
const std::string supported_algos[] = 
    {"insertionAux", "insertionPlace", 
    "selectionAux", "selectionPlace", 
    "mergesort", "quicksort"};

const size_t NUM_ALGOS = sizeof(supported_algos) / sizeof(supported_algos[0]);

class Sorter {
    public:
        Sorter();
        Sorter(std::vector<int> input_data, std::string sort_algo);

        ~Sorter();
        
        std::chrono::duration<double> run_algorithm();
        void print_vector();
        bool is_sorted();

    private:
        /* private member variables */
        std::string which_algo;
        std::vector<int> data;

        
        /* Sorting functions*/
        void insertionAux  ();
        void insertionPlace();
        void insertFrom     (int idx);

        void selectionAux   ();
        void selectionPlace ();
        size_t indexOfMin(size_t from, size_t to);

        void mergesort();
        void mergesortHelper(int left, int right);
        void merge          (int left, int right, int split);

        void quicksort      ();
        void quicksortHelper(int left, int right);
        int  partition      (int left, int right);
};


#endif 