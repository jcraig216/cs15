/*
 * planet-driver.cpp
 *
 * CS 15 Lab 02
 * Edited by Elizabeth Hom, Sept 2020
 * Edited by Matt Russell, Juliana Vega, and Alexis Blair, Jan 2021
 * Edited by Katherine Quintanilla, Jan 2025
 *
 * Driver for a planetary system program, details a linked list of planets.
 *
 * See the TODO sections for details on what to do.
 *
 */

#include "LinkedList.h"
#include "Planet.h"
#include <iostream>

/* get_planet_names
 *    Purpose: Populate the planet_names array via names entered through cin
 * Parameters: Pointer to an array of planets and the size of the array
 *    Returns: None
 */
void get_planet_names(Planet *planets, int size)
{
    std::string name;
    int distance;

    for (int i = 0; i < size; i++)
    {
        std::cout << "Enter: planet_name planet_distance\n";
        std::cin >> name >> distance;
        planets[i] = Planet(name, distance);
        std::cout << std::endl;
    }
}

/* main
 *    Purpose: Populate 2 LinkedLists of Planets with client input
 * Parameters: None
 *    Returns: int - 0, representing EXIT_SUCCESS
 *       Note: One linkedlist will be the 'opposite' order of the way the
 *             planets were entered unless reverse() is implemented
 */
int main()
{
    int num_planets;
    Planet *planet_array;

    LinkedList first_planet_linked_list;
    LinkedList second_planet_linked_list;

    std::cout << "Please enter the number of planets: ";
    std::cin >> num_planets;
    planet_array = new Planet[num_planets];
    get_planet_names(planet_array, num_planets);

    /*
     * ******************************************************************
     *                           TODO: Part 1
     *       insert all planets into the LinkedList, using the
     *       pushAtFront function of the LinkedList class
     *
     * NOTE: because you push at the front of the list, the
     *       resulting list should be the opposite of the way
     *       the planets are entered
     * NOTE: for this part, use first_planet_linked_list
     * ******************************************************************
     */
    for (int i = 0; i < num_planets; i++)
    {
        first_planet_linked_list.pushAtFront(planet_array[i]);
    }

    std::cout << "Part 1: PushAtFront list of planets\n";
    std::cout << first_planet_linked_list.toString() << "\n";

    /*
     * ******************************************************************
     *                           TODO: Part 2
     *       insert all planets into the LinkedList, using the
     *       pushAtBack function of the LinkedList class
     *
     * NOTE: because you push at the back of the list, the
     *       resulting list should be the same order that the
     *       planets are entered
     * NOTE: for this part, use second_planet_linked_list
     * ******************************************************************
     */
    for (int i = 0; i < num_planets; i++)
    {
        second_planet_linked_list.pushAtBack(planet_array[i]);
    }

    std::cout << "Part 2: pushAtBack list of planets\n";
    std::cout << second_planet_linked_list.toString() << "\n";

    /*
     * ******************************************************************
     *                           TODO: JFFE
     *       call the reverse function of the LinkedList class to reverse
     *       the list
     *
     * NOTE: because first_planet_linked_list was previously 'opposite',
     *       the resulting list should be the same order that the
     *       planets are entered
     * ******************************************************************
     */

    /* call reverse() here */

    std::cout << "JFFE: PushAtFront list of planets, reversed\n";
    std::cout << first_planet_linked_list.toString() << "\n";

    /* deallocating the heap-allocated memory associated with the planet_names */
    delete[] planet_array;

    return 0;
}
