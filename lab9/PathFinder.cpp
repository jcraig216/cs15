/*
 * PathFinder.cpp
 * CS15 Graph Traversals Lab
 *
 * Implementation of PathFinder.h.
 *
 * 2025-03-31 Modified by Lindsay Ulrey
 *            Edited to follow CS15 style guide.
 *            Added comments for clarity.
 *            Added file header and function contracts.
 *            Edited parameters of run_bfs() for consistency. Revised neighbor
 *            traversal in run_bfs() to avoid range-based for loop.
 *            Revised run() to remove switch statment.
 */

#include "PathFinder.h"
#include <vector>
#include <queue>
#include <random>

/* constructor
 *    Purpose: Initialize PathFinder.
 * Parameters: None
 *    Returns:
 *       Note: Nothing to do for Graph class, it self initializes
 */
PathFinder::PathFinder()
{
    /* Initialize random seed */
    srand(time(NULL));
}

/* destructor
 *    Purpose: None
 * Parameters: None
 *    Returns: None
 */
PathFinder::~PathFinder()
{
    /* Nothing to do, Graph and PathFinder class self destruct */
}

/* run_bfs()
 *    Purpose: Run breadth-first traversal from cities c1 to c2.
 * Parameters: City c1   - starting city node
 *             City c2   - ending city node
 *    Returns: bool      - true if there exists a path between c1 and c2,
 *                         false otherwise
 */
bool PathFinder::run_bfs(City c1, City c2)
{
    if (c1.get_name() == c2.get_name())
    {
        return true;
    }

    graph.clear_marks();
    graph.initialize_path();

    std::queue<City> q;
    q.push(c1);
    graph.mark_vertex(c1);

    while (!q.empty())
    {
        City current = q.front();
        q.pop();

        std::queue<City> neighbors;
        graph.get_to_vertices(current, neighbors);

        while (!neighbors.empty())
        {
            City neighbor = neighbors.front();
            neighbors.pop();

            if (!graph.is_marked(neighbor))
            {
                graph.mark_vertex(neighbor);
                graph.update_predecessor(current, neighbor);

                if (neighbor.get_name() == c2.get_name())
                {
                    return true;
                }

                q.push(neighbor);
            }
        }
    }

    return false;
}

/* run_dfs()
 *    Purpose: Run recursive depth-first traversal from cities c1 to c2.
 * Parameters: City c1   - starting city node
 *             City c2   - ending city node
 *    Returns: bool      - true if there exists a path between c1 and c2,
 *                         false otherwise
 */
bool PathFinder::run_dfs(City c1, City c2)
{
    graph.clear_marks();
    graph.initialize_path();
    return dfs_helper(c1, c2);
}

/* dfs_helper()
 *    Purpose: Helper function for recursive depth-first search
 * Parameters: City current - current city being examined
 *             City target  - city we're trying to reach
 *    Returns: bool         - true if path exists, false otherwise
 */
bool PathFinder::dfs_helper(City current, City target)
{
    if (current.get_name() == target.get_name())
    {
        return true;
    }

    graph.mark_vertex(current);

    std::queue<City> neighbors;
    graph.get_to_vertices(current, neighbors);

    while (!neighbors.empty())
    {
        City neighbor = neighbors.front();
        neighbors.pop();

        if (!graph.is_marked(neighbor))
        {
            graph.update_predecessor(current, neighbor);
            if (dfs_helper(neighbor, target))
            {
                return true;
            }
        }
    }

    return false;
}

/* The functions below are mostly for setup, so no need to look at them! */

/* get_cities()
 *    Purpose: Get city names from user input.
 * Parameters: None
 *    Returns: pair<string, string> - City names in pair
 */
std::pair<std::string, std::string> PathFinder::get_cities()
{
    std::string city1, city2;
    std::cout << "City 1? ";
    std::cin >> city1;
    std::cout << "City 2? ";
    std::cin >> city2;
    return std::make_pair(city1, city2);
}

/* bfs()
 *    Purpose: Run breadth-first traversal.
 * Parameters: None
 *    Returns: None
 *       Note: Calls run_bfs(), which must be completed before bfs() can work
 */
void PathFinder::bfs()
{
    std::pair<std::string, std::string> cities = get_cities();
    if (run_bfs(cities.first, cities.second))
    {
        graph.report_path(std::cout, cities.first, cities.second);
    }
    else
    {
        std::cout << "No flight from " << cities.first << " to "
                  << cities.second
                  << ".\n";
    }
    graph.clear_marks();
}

/* dfs()
 *    Purpose: Run depth-first traversal.
 * Parameters: None
 *    Returns: None
 *       Note: Calls run_dfs(), which must be completed before dfs() can work
 */
void PathFinder::dfs()
{
    std::pair<std::string, std::string> cities = get_cities();
    City city1 = graph.get_vertex(cities.first);
    City city2 = graph.get_vertex(cities.second);

    if (run_dfs(city1, city2))
    {
        graph.report_path(std::cout, city1, city2);
    }
    else
    {
        std::cout << "No flight from " << city1.get_name() << " to "
                  << city2.get_name() << ".\n";
    }
    graph.clear_marks();
}

/* run()
 *    Purpose: Read and process user commands to traverse graph.
 * Parameters: None
 *    Returns: None
 */
void PathFinder::run()
{
    std::string cmnd = "";
    bool running = true;

    try
    {
        while (running)
        {
            std::cout << "Command? ";
            std::cin >> cmnd;
            /* process command from input */
            if (cmnd == "print" or cmnd == "p")
            {
                graph.print_matrix(std::cout);
            }
            else if (cmnd == "bfs")
            {
                bfs();
            }
            else if (cmnd == "dfs")
            {
                dfs();
            }
            else if (cmnd == "quit" or cmnd == "q")
            {
                running = false;
            }
            else
            {
                std::cout << "Command not recognized! Try again." << std::endl;
            }
        }
        clean_up();
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << e.what() << '\n';
        run();
    }
}

/* clean_up()
 *    Purpose: Print ending message for program.
 * Parameters: None
 *    Returns: None
 */
void PathFinder::clean_up()
{
    std::cout << "Thanks for finding paths and such!" << std::endl;
}

/* get_airline()
 *    Purpose: Get random airline name from array.
 * Parameters: None
 *    Returns: None
 */
std::string PathFinder::get_airline()
{
    std::string airlines[] = {"Delta", "American Airlines", "Spirit", "Virgin",
                              "Jet Blue", "Southwest", "United"};
    int random = rand() % 7;
    return airlines[random];
}

/* populate_graph()
 *    Purpose: Set up graph of cities using data from a filestream.
 * Parameters: ifstream &data - contents of file dictating cities and their
 *                              connections
 *    Returns: None
 */
void PathFinder::populate_graph(std::ifstream &data)
{
    std::string vertex = "";
    std::vector<City> cities;

    while (data >> vertex)
    {
        City c(vertex);
        while (data >> vertex)
        {
            if (vertex == "###")
            {
                cities.push_back(c);
                break;
            }
            else
            {
                c.add_neighbor(vertex);
            }
        }
    }

    graph.initialize_graph(cities.size());

    /* dont worry too much about the for loop syntax here!
     * essentially 'auto' tells the complier to deduce the type
     * and the colon (:) is used to iterate through each element
     * in cities
     */
    for (auto &city : cities)
    {
        graph.add_vertex(city);
    }
    for (auto &city : cities)
    {
        for (auto &edge : city.get_neighbors())
        {
            graph.add_edge(city, edge, get_airline());
        }
    }
}