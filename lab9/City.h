/*
 * City.h
 * CS15 Graph Traversals Lab
 *
 * Vertices in the graph will be City instances for this lab.
 * A City has a name and list of neighboring City names (list of strings).
 * Note that Cities are comparable with == and !=.
 * 
 * Edited by Kathy Quintanilla, November 2024
 *      added function contracts + fixed style
 */

#ifndef _CITY_H_
#define _CITY_H_

#include <string>
#include <vector>

class City {
    public:
        City();
        City(std::string n);
        ~City();

        bool operator==(const City& rhs) const;
        bool operator!=(const City& rhs) const;

        int         get_num_neighbors();
        std::string get_name();

        std::vector<std::string> get_neighbors();

        void add_neighbor(std::string city);

    private:
        std::string              name;
        std::vector<std::string> neighbors;
};

#endif
