/*
 * PathFinder.h
 * CS15 Graph Traversals Lab
 *
 * A class that builds and traverses a graph of cities to find the paths
 * between cities.
 */

#ifndef _PATH_FINDER_H_
#define _PATH_FINDER_H_

#include "Graph.h"
#include <iostream>
#include <fstream>

class PathFinder
{
public:
    PathFinder();
    ~PathFinder();

    void run();
    void populate_graph(std::ifstream &data);
    void bfs();
    void dfs();

private:
    Graph graph;

    void clean_up();

    bool run_bfs(City city1, City city2);
    bool run_dfs(City city1, City city2);
    bool dfs_helper(City current, City target);
    std::pair<std::string, std::string> get_cities();
    std::string get_airline();
};

#endif