/*
 *      ElementType.h
 *      Circular Buggers
 *      CS15 Lab 4
 * 
 *      File created and definition factored out by 
 *      Mark A. Sheldon, Tufts University, 2020 Spring
 * 
 *      The following defines a type called ElementType that is a synonym
 *      for string.  
 * 
 *      In fact, none of the classes in this lab depend on the element
 *      type. 
 * 
 *      The right way to deal with this in C++ is to make the classes
 *      *polymorphic* by using templates.  But we haven't learned about
 *      those, so we have factored the element type out into this header
 *      file, and each class can include it to find out what the element
 *      type is.
 *
 *      In principle, we could change the definition to another type, and
 *      just recompile and relink for buffers, stacks, and queues of that
 *      type. 
 *      
 */

#ifndef ELEMENTTYPE_H
#define ELEMENTTYPE_H

#include <string>

typedef std::string ElementType;

#endif
