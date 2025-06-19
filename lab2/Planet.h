/*
 * Planet.h
 *
 * CS 15 Lab 02
 * Edited by Elizabeth Hom, Sept 2020
 *
 * The Planet class contains functions and info regarding a Planet object.
 *
 */

#ifndef PLANET_H_
#define PLANET_H_

#include <string>

class Planet {
public:
    Planet();
    Planet(std::string name, int distance_from_sun);
    Planet(const Planet &other);
    
    Planet &operator=(const Planet &other);

    std::string toString() const;

private:
    std::string name;
    int         distance_from_sun;
};

#endif
