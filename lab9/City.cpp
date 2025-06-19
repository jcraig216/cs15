/*
 * City.cpp
 * CS15 Graph Traversals Lab
 *
 * Implementation of City class, which contains a name and a list of 
 * neighboring city names (strings).
 * 
 * Edited by Kathy Quintanilla, November 2024
 *      added function contracts + fixed style
 */

#include <iostream>
#include "City.h"

/* constructor
 *   Purpose: Construct a City instance with a nonce value.
 * Arguments: None
 *   Returns: None
 */
City::City()
{
    name = "";  /* A peculiar name for a city! */
}

/* constructor(string n)
 *   Purpose: Construct a City instance with a given value.
 * Arguments: string -- name of City
 *   Returns: None
 */
City::City(std::string n)
{
    name = n;
}

/* destructor
 *   Purpose: Recycle all memory associated with City instance.
 * Arguments: None
 *   Returns: None
 */
City::~City()
{
    /* Nothing to do */
}

/* get_neighbors()
 *   Purpose: Return the names of all this City's neighbors.
 * Arguments: None
 *   Returns: std::vector<std::string> -- vector containing all the names of
 *                                        this City's neighboring cities.
 */
std::vector<std::string> City::get_neighbors()
{
    return neighbors;
}

/* overload ==
 *   Purpose: Check if two Cities are equal to each other.
 * Arguments: const City &rhs -- the City to check this City against
 *   Returns: bool -- true if this City and the given City are the same City; 
 *                    false otherwise.
 */
bool City::operator==(const City &rhs) const
{
    return this->name == rhs.name;
}

/* overload !=
 *   Purpose: Check if two Cities are not equal to each other.
 * Arguments: const City &rhs -- the City to check this City against
 *   Returns: bool -- true if this City and the given City are not the same 
 *                    City; false otherwise.
 */
bool City::operator!=(const City &rhs) const
{
    return this->name != rhs.name;
}

/* get_num_neighbors
 *   Purpose: Get the number of neighbors that this City has.
 * Arguments: None
 *   Returns: int -- number of neighbors this City has.
 */
int City::get_num_neighbors()
{
    return neighbors.size();
}
  
/* get_name
 *   Purpose: Get the name of this City.
 * Arguments: None
 *   Returns: std::string -- name of this City.
 */
std::string City::get_name()
{
    return name;
}

/* add_neighbor
 *   Purpose: Add a neighbor to this City.
 * Arguments: std::string -- name of new neighboring City.
 *   Returns: None
 */
void City::add_neighbor(std::string city)
{
    neighbors.push_back(city);
}