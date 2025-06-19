/*
 * Graph.h
 * CS15 Graph Traversals Lab
 * 
 * Class representing a Graph to be used by PathFinder class. This class 
 * contains functions that will be useful for implementing BFS and DFS, such as
 * mark_vertex() and get_neighbors().
 * 
 * Updated by rgilk01 and jdavid07 11/13/20
 */

#ifndef GRAPH_H
#define GRAPH_H

#include "City.h"
#include <iostream>
#include <ostream>
#include <queue>

const std::string NULL_EDGE = "-1";
const int         NULL_PRED = -1;

class Graph {
    public:
        Graph();
        Graph(int n_vertices);
        ~Graph();
        Graph(const Graph& other);
        Graph& operator=(const Graph &rhs);

        /* Mutator Functions */
        void initialize_graph(int n_vertices);
        void add_vertex(City v);
        void add_edge(City, City, std::string);

        /* Accessor Functions */
        void print_matrix(std::ostream&) const;
        std::string get_edge(City from, City to) const;

        /* Helpers for BFS, DFS */
        void get_to_vertices(City, std::queue<City> &adj) const;
        void clear_marks();
        void mark_vertex(City c);
        bool is_marked(City c) const;
        bool is_vertex(City c) const;
        void initialize_path();
        void update_predecessor(City pred, City curr);
        void report_path(std::ostream& out, City start, City end) const;

        /* Getter Functions */
        City get_vertex(City c) const;

    private:
        int           curr_vertex;
        int           num_vertices;
        City         *vertices;
        std::string **edges;
        int          *path;
        bool         *marks;

        int index_is(City* vertices, City v) const;
};

#endif 