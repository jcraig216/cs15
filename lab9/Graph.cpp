/*
 * Graph.cpp
 * CS15 Graph Traversals Lab
 *
 * Implementation of Graph class.
 * 
 * Edited by Kathy Quintanilla, November 2024
 *      added function contracts + fixed style
 */

#include <iostream>
#include <string>
#include <stack>
#include "Graph.h"
using namespace std;
 
/* default constructor
 *   Purpose: Construct a City instance with nonce values.
 * Arguments: None
 *   Returns: None
 */
Graph::Graph()
{
    curr_vertex = 0;
    edges       = nullptr;
    path        = nullptr;
    vertices    = nullptr;
    marks       = nullptr;
}
 
/* constructor
 *   Purpose: Initialize a Graph instance with num_v vertices.
 * Arguments: int -- number of verticies to initialize Graph instance with.
 *   Returns: None
 */
Graph::Graph(int num_v)
{
    initialize_graph(num_v);
}

/* copy constructor
 *   Purpose: Construct a copy instance of a given Graph.
 * Arguments: const Graph & -- Graph instance to copy.
 *   Returns: None
 */
Graph::Graph(const Graph &other)
{
    num_vertices = other.num_vertices;
    
    vertices = new City[num_vertices];
    marks    = new bool[num_vertices];
    path     = new int[num_vertices];
    
    edges = new string *[num_vertices];
    for (int i = 0; i < num_vertices;  i++) {
        edges[i] = new string[num_vertices];
    }
    
    for (int i = 0; i < num_vertices; i++) {
        vertices[i] = other.vertices[i];
        marks[i] = other.marks[i];
        path[i]  = other.path[i];
        for (int j = 0; j < num_vertices; j++) {
            edges[i][j] = other.edges[i][j];
        }
    }
    
}

/* destructor
 *   Purpose: Recycle all memory associated with this Graph instance.
 * Arguments: None
 *   Returns: None
 */
Graph::~Graph()
{
    delete [] vertices;
    delete [] marks;
    delete [] path;

    for (int i = 0; i < num_vertices; i++){
        delete [] edges[i];
    }
    
    delete [] edges;
}

/* overload assignment operator
 *   Purpose: Deep copy a given Graph instance.
 * Arguments: const Graph & -- Graph to make this Graph a deep copy of.
 *   Returns: Graph & -- this Graph instance that is now a deep copy.
 */
Graph &Graph::operator=(const Graph &rhs)
{
    /* Delete all memory associated with this Graph */
    delete [] marks;
    delete [] vertices;
    delete [] path;
    for (int i = 0; i < num_vertices; i++) {
        delete [] edges[i];
    }
    
    delete [] edges;
    
    /* Reestablish all Graph memory to mimic rhs memory */
    num_vertices = rhs.num_vertices;
    
    vertices = new City[num_vertices];
    marks    = new bool[num_vertices];
    
    path     = new int[num_vertices];
    edges    = new string *[num_vertices];
    for (int i = 0; i < num_vertices;  i++) {
        edges[i] = new string[num_vertices];
    }
    
    /* Copy over all information from rhs */
    for (int i = 0; i < num_vertices; i++) {
        vertices[i] = rhs.vertices[i];
        marks[i] = rhs.marks[i];
        path[i]  = rhs.path[i];
        for (int j = 0; j < num_vertices; j++) {
            edges[i][j] = rhs.edges[i][j];
        }
    }
    
    return *this;
}

/* initialize_graph
 *   Purpose: Allocates all memory associated with this Graph instance
 *            according to a given number of vertices.
 * Arguments: int -- number of verticies to initialize Graph instance with.
 *   Returns: None
 */
void Graph::initialize_graph(int num_v)
{
    curr_vertex  = 0;
    num_vertices = num_v;
    vertices     = new City[num_vertices];
    marks        = new bool[num_vertices];
    path         = new int[num_vertices];

    edges = new string *[num_vertices];
    for (int i = 0; i < num_vertices; i++) {
        edges[i] = new string[num_vertices];
    }

    /* Add nonce values */
    for (int i = 0; i < num_vertices; i++) {
        marks[i] = false;
        path[i] = NULL_PRED;
        for (int j = 0; j < num_vertices; j++) {
            edges[i][j] = NULL_EDGE;
        }
    }
}

/* add_vertex
 *   Purpose: Adds a new vertex to the end of the 2D array (edges) and 
 *            initializes every from/to edge to be NULL.
 * Arguments: City -- City to add to the Graph
 *   Returns: None
 */
void Graph::add_vertex(City v)
{
    if (curr_vertex >= num_vertices){
        return;
    }

    vertices[curr_vertex] = v;
    for (int i = 0; i < num_vertices; i++) {
        edges[curr_vertex][i] = NULL_EDGE;
        edges[i][curr_vertex] = NULL_EDGE;
    }
    curr_vertex++;
}

/* clear_marks
 *   Purpose: Sets all the marks to be false for algorithms that need to mark 
 *            vertices (BFS, DFS).
 * Arguments: None
 *   Returns: None
 */
void Graph::clear_marks()
{
    for (int i = 0; i < num_vertices; i++) {
        marks[i] = false;
        path[i] = NULL_PRED;
    }
}

/* initialize_path
 *   Purpose: Sets every value in the predecessor path to be the NULL edge.
 * Arguments: None
 *   Returns: None
 */
void Graph::initialize_path()
{
    for (int i = 0; i < num_vertices; i++) {
        path[i] = NULL_PRED;
    }
}

/* update_predecessor
 *   Purpose: Finds the location in the vertices array for predecessor and 
 *            current. Updates the path array to reflect pred relationship.
 * Arguments: City pred -- predecessor
 *            City curr -- current 
 *   Returns: None
 */
void Graph::update_predecessor(City pred, City curr)
{
    int pred_index, curr_index;

    for (int i = 0; i < num_vertices; i++) {
        if (vertices[i] == pred) {
            pred_index = i;
        }
        if (vertices[i] == curr) {
            curr_index = i;
        }
    }

    if (path[curr_index] == NULL_PRED) {
        path[curr_index] = pred_index;
    }
}

/* report_path
 *   Purpose: Finds path from start to end on the predecessor path and prints
 * Arguments: ostream &out -- output stream to print to
 *              City start -- start City vertex
 *              City end   -- end City vertex
 *   Returns: None
 */
void Graph::report_path(ostream &out, City start, City end) const
{
    if (start == end) {
        out << "You don't need to fly from " << start.get_name() << " to "
            << end.get_name() << "!\n";
        return;
    }

    stack<City> s;

    int index = index_is(vertices, end.get_name());
    s.push(vertices[index]);

    bool done = false;
    while (not done) {
        index = path[index];
            
        if (vertices[index].get_name() == start.get_name())
            done = true;
        s.push(vertices[index]);
    }

    while (not s.empty()) {
        City v = s.top();
        s.pop();
        if (not s.empty()) {
            City v2 = s.top();
            out << v.get_name() << " ---> ";
            out << v2.get_name() << " through ";
            out << get_edge(v, v2) << ".  ";
        }

    }
    out << "\nend of flight!" << endl;
}

/* mark_vertex
 *   Purpose: Sets the mark of this City vertex to true.
 * Arguments: City v -- vertex to mark.
 *   Returns: None
 */
void Graph::mark_vertex(City v)
{
    for (int i = 0; i < num_vertices; i++) {
        if (vertices[i] == v)
            marks[i] = true;
    }
}

/* is_marked
 *   Purpose: Returns value in marks array for this vertex.
 * Arguments: City v -- vertex to check.
 *   Returns: bool -- value in marks array for this vertex; false if vertex is
 *                    not in marks array.
 */
bool Graph::is_marked(City v) const
{
    for (int i = 0; i < num_vertices; i++) {
        if (vertices[i] == v) {
            return marks[i];
        }
    }

    return false;
}

/* is_vertex
 *   Purpose: Checks if a given vertex is in the Graph.
 * Arguments: City v -- vertex to check.
 *   Returns: bool -- true if vertex exists in the graph; false otherwise.
 */
bool Graph::is_vertex(City v) const
{
    for (int i = 0; i < num_vertices; i++) {
        if (vertices[i] == v) {
            return true;
        }
    }
    return false;
}

/* add_edge
 *   Purpose: Checks if a given vertex is in the Graph.
 * Arguments:        City f -- from vertex 
 *                   City t -- to vertex 
 *            string weight -- weight of edge
 *   Returns: None
 */
void Graph::add_edge(City f, City t, string weight)
{
    int row;
    int col;

    row = index_is(vertices, f);
    col = index_is(vertices, t);
    if (edges[row][col] == NULL_EDGE) {
        edges[row][col] = weight;
    }
}

/* get_vertex
 *   Purpose: Returns City with the given name if it exists.
 * Arguments: string s -- name of City to check.
 *   Returns: City -- City in the Graph if it exists.
 */
City Graph::get_vertex(City c) const
{ 
    for (int i = 0; i < num_vertices; i++) {
        if (c == vertices[i]) {
            return vertices[i];
        }
    }
    throw runtime_error("No city " + c.get_name() + " in Graph. Try again.");
}

/* get_edge
 *   Purpose: Returns the weight of an edge between two given Cities in the 
 *            Graph.
 * Arguments: City from -- from City.
 *              City to -- to City.
 *   Returns: string -- weight of the edge between the from City and to City.
 */
string Graph::get_edge(City from, City to) const
{
    int row;
    int col;
    row = index_is(vertices, from);
    col = index_is(vertices, to);
    return edges[row][col];
}

/* get_to_vertices
 *   Purpose: Finds all neighbors of the given vertex and enqueues.
 * Arguments:           City v -- City to get all neighbors of.
 *            queue<City> &adj -- queue of vertices by reference.
 *   Returns: None
 */
void Graph::get_to_vertices(City v, queue<City> &adj) const
{
    int from;
    int to;
    from = index_is(vertices, v);

    for (to = 0; to < num_vertices; to++) {
        if (edges[from][to] != NULL_EDGE) {
            if (vertices[to] != vertices[from]) {
                adj.push(vertices[to]);
            }
        }
    }
}

/* print_matrix
 *   Purpose: Print this Graph in matrix form.
 * Arguments: ostream &out -- output stream to print to.
 *   Returns: None
 */
void Graph::print_matrix(ostream &out) const
{
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) { 
            out << edges[i][j] << " ";
        }
        out << endl;
    }
}

/* index_is
 *   Purpose: Helper function to get the index of a given vertex from a given 
 *            vertex array *.
 * Arguments: City *vertices -- City vertex array * to check.
 *                    City v -- City to get the index of.
 *   Returns: int -- index of City in given array *.
 */
int Graph::index_is(City *vertices, City v) const
{
    int index = 0;
    while (not (v.get_name() == vertices[index].get_name())) {
        index++;
    }

    return index;
} 