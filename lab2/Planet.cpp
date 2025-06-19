/*
 * Planet.cpp
 *
 * CS 15 Lab 02
 * Edited by Elizabeth Hom, Sept 2020
 * Edited by Matt Russell, Juliana Vega, and Alexis Blair, Jan 2021
 * Edited by Katherine Quintanilla, Jan 2025
 *
 * This file contains the implementation of Planet class functions.
 * 
 */

#include "Planet.h"
#include <sstream>
#include <string>

/* Default constructor
 *    Purpose: Creates a Planet object
 * Parameters: None
 *    Returns: None
 */
Planet::Planet() {}

/* Parametrized constructor
 *    Purpose: Creates a Planet object with a given name and distance
 * Parameters: string - name of planet
 *             int    - distance of the planet from the sun
 *    Returns: None
 */
Planet::Planet(std::string name, int distance_from_sun) {
    this->name              = name;
    this->distance_from_sun = distance_from_sun;
}


/* Copy constructor
 *    Purpose: Creates a Planet object with the same information of as that of
 *             'other'
 * Parameters: Planet - the planet object to copy the information from
 *    Returns: None
 */
Planet::Planet(const Planet &other) {
    this->name              = other.name;
    this->distance_from_sun = other.distance_from_sun;
}

/* Operator= overload
 *    Purpose: Updates the information of 'this' to be the same as that of
 *             'other'
 * Parameters: Planet - the planet object to copy the information from
 *    Returns: Reference to 'this' object
 */
Planet &Planet::operator=(const Planet &other) {
    if (this != &other) {
        this->name              = other.name;
        this->distance_from_sun = other.distance_from_sun;
    }

    return *this;
}


/* toString
 *    Purpose: Strings together the Planet's info
 * Parameters: None
 *    Returns: String with the name and distance to the sun of the Planet
 */
std::string Planet::toString() const {
    std::stringstream ss;
    ss << this->name << ": " << this->distance_from_sun;

    return ss.str();
}
