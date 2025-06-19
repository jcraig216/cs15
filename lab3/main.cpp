/*
 *      main.cpp
 *      Circular Buggers
 *      CS15 Lab 4
 *
 *      Simple test program that tests the CircularBuffer, Stack, and Queue
 *      classes for our Pokedex. Comment and un-comment out tests to narrow
 *      down where particular bugs are occurring.
 *
 *      For functional bugs: what do we want each CircularBuffer function
 *      to accomplish? To guide your thinking, replace the phrase
 *      [ TODO: INSERT TEST CONDITION HERE! ] above each of the tests with your
 *      goals for testing that function. What properties (invariants) of the
 *      CircularBuffer should be true after we call a function?
 *
 *      For memory bugs: if you run valgrind on your program,
 *      (e.g. `valgrind ./pokedex`) it will tell you what line in your code
 *      is causing a memory-related bug!
 *
 *      2016-09-16 Created by Yennie Jun
 *      2016-09-20 Updated by Mark A. Sheldon, Tufts University
 *                 Documenation, factored testing into separate
 *                 functions.
 *      2019-08-01 Modified by Alice Dempsey
 *      2020-01-31 Modified by Juliana Vega
 *                 Removed "sequence" wording
 *      2020-09-21 Modified by Matt Champlin
 *                 Updated songs to be current top 10.
 *                 Removed numbering from songs. Print function handles
 *                 numbering now.
 *                 Made parameters in tests void to avoid warnings.
 *      2024-02-07 Modified by Skylar Gilfeather
 *                 Updated header
 *      2024-09-29 Modified by Hameedah Lawal
 *                 Removed mention of songs, reformatted print statements,
 *                 added asserts to stack and queue tests, and
 *                 removed trailing comma in toString()
 *
 */

#include <iostream>
#include <cassert>

#include "CircularBuffer.h"
#include "Queue.h"
#include "Stack.h"

using namespace std;

void testCircularBuffer_emptyConstructor();
void testCircularBuffer_capacityConstructor(int initialCapacity);

void testCircularBuffer_addAtFront(string pokemon[]);
void testCircularBuffer_removeFromFront(string pokemon[]);

void testCircularBuffer_addAtBack(string pokemon[]);
void testCircularBuffer_removeFromBack(string pokemon[], int numPokemon);

void testStack(string pokemon[], int numPokemon);
void testQueue(string pokemon[], int numPokemon);

/* main()
 * Purpose: Runs tests for the CircularBuffer, Stack, and Queue classes on bug
 *          type Pokemon.
 * Parameters: None
 * Return: None
 */
int main()
{
    /* bug type pokemon */
    string pokemon[10] = {
        "Beedrill", "Scyther", "Butterfree", "Snom", "Joltik",
        "Heracross", "Vivillion", "Venomoth", "Metapod", "Volcarona"};

    const int numPokemon = sizeof(pokemon) / sizeof(string);

    /*
     * TODO: comment and uncomment these tests out to narrow down
     * where the bugs are!
     */

    cout << "TESTING CIRCULAR BUFFER\n\n";
    cout << "-----------------------\n";

    testCircularBuffer_emptyConstructor();
    testCircularBuffer_capacityConstructor(numPokemon / 2);

    testCircularBuffer_addAtFront(pokemon);
    testCircularBuffer_removeFromFront(pokemon);

    testCircularBuffer_addAtBack(pokemon);
    testCircularBuffer_removeFromBack(pokemon, numPokemon);

    cout << "\nIf all of the tests above pass, good job!\n";
    cout << "You caught all of the Circular Buffer bugs!\n";

    cout << "\nTESTING STACK\n";
    cout << "-------------\n";
    /* test Stack, implemented with CircularBuffer */
    testStack(pokemon, numPokemon);

    cout << "\nTESTING QUEUE\n";
    cout << "-------------\n";
    /* test Queue, implemented with CircularBuffer */
    testQueue(pokemon, numPokemon);

    return 0;
}

/*
 ******** PART 1: TESTING THE CIRCULAR BUFFER ********
 */

/*  testCircularBuffer_emptyConstructor()
 *  Purpose: tests CircularBuffer::CircularBuffer(), and ensures that
 *          [ TODO: INSERT TEST CONDITION HERE! ]
 *  Parameters: None
 *  Return: None
 */
void testCircularBuffer_emptyConstructor()
{
    cout << "\nTesting our Circular Buffer Pokedex's default constructor.\n";
    CircularBuffer myBuffer;
    assert(myBuffer.size() == 0);
}

/*  testCircularBuffer_capacityConstructor()
 *  Purpose: tests CircularBuffer::CircularBuffer(int capacity), and ensures
 *          that [ TODO: INSERT TEST CONDITION HERE! ]
 *  Parameters: pokemon[]  - a predetermined list of pokemon
 *              numPokemon - The number of pokemon in pokemon[]
 *  Return: None
 */
void testCircularBuffer_capacityConstructor(int initialCapacity)
{
    cout << "\nTesting our Circular Buffer Pokedex's capacity constructor.\n";
    CircularBuffer myBuffer(initialCapacity);
    assert(myBuffer.size() == 0);
    assert(myBuffer.toString() == "[ ]");
}

/*  testCircularBuffer_addAtFront()
 *  Purpose: tests CircularBuffer::addAtFront(ElementType elem), and ensures
 *          that [ TODO: INSERT TEST CONDITION HERE! ]
 *  Parameters: pokemon[]  - a predetermined list of pokemon
 *              numPokemon - The number of pokemon in pokemon[]
 *  Return: None
 */
void testCircularBuffer_addAtFront(string pokemon[])
{
    cout << "\nTesting our Circular Buffer Pokedex's addAtFront.\n";
    CircularBuffer myBuffer(4); // calls the capacity constructor
    myBuffer.addAtFront(pokemon[0]);
    myBuffer.addAtFront(pokemon[1]);

    string bufferString = "[ '" + pokemon[1] + "', '" + pokemon[0] + "' ]";
    assert(myBuffer.toString() == bufferString);
}

/*  testCircularBuffer_removeFromFront()
 *  Purpose: tests CircularBuffer::removeFromFront(), and ensures
 *          that [ TODO: INSERT TEST CONDITION HERE! ]
 *  Parameters: pokemon[]  - a predetermined list of pokemon
 *              numPokemon - The number of pokemon in pokemon[]
 *  Return: None
 */
void testCircularBuffer_removeFromFront(string pokemon[])
{
    cout << "\nTesting our Circular Buffer Pokedex's removeFromFront.\n";
    CircularBuffer myBuffer(4);
    myBuffer.addAtFront(pokemon[0]);
    myBuffer.addAtFront(pokemon[1]);
    myBuffer.addAtFront(pokemon[2]);

    assert(pokemon[2] == myBuffer.removeFromFront());
    assert(pokemon[1] == myBuffer.removeFromFront());

    string bufferString = "[ '" + pokemon[0] + "' ]";
    assert(myBuffer.toString() == bufferString);
}

/*  testCircularBuffer_addAtBack()
 *  Purpose: tests CircularBuffer::addAtBack(ElementType elem), and ensures
 *          that [ TODO: INSERT TEST CONDITION HERE! ]
 *  Parameters: pokemon[]  - a predetermined list of pokemon
 *              numPokemon - The number of pokemon in pokemon[]
 *  Return: None
 */
void testCircularBuffer_addAtBack(string pokemon[])
{
    cout << "\nTesting our Circular Buffer Pokedex's addAtBack.\n";
    CircularBuffer myBuffer(4);

    myBuffer.addAtBack(pokemon[0]);
    myBuffer.addAtBack(pokemon[1]);
    myBuffer.addAtBack(pokemon[2]);
    myBuffer.addAtBack(pokemon[3]);

    assert(pokemon[0] == myBuffer.removeFromFront());
    assert(pokemon[1] == myBuffer.removeFromFront());

    myBuffer.addAtBack(pokemon[4]);
    myBuffer.addAtBack(pokemon[5]);

    string bufferString = "[ '" + pokemon[2] + "', "
                                               "'" +
                          pokemon[3] + "', "
                                       "'" +
                          pokemon[4] + "', "
                                       "'" +
                          pokemon[5] + "' ]";
    assert(myBuffer.toString() == bufferString);
}

/*  testCircularBuffer_removeFromBack()
 *  Purpose: tests CircularBuffer::removeFromBack(), and ensures
 *          that [ TODO: INSERT TEST CONDITION HERE! ]
 *  Parameters: pokemon[]  - a predetermined list of pokemon
 *              numPokemon - The number of pokemon in pokemon[]
 *  Return: None
 */
void testCircularBuffer_removeFromBack(string pokemon[], int numPokemon)
{
    cout << "\nTesting our Circular Buffer Pokedex's removeFromBack.\n";
    CircularBuffer myBuffer(4);
    string bufferString = "[ ";

    for (int i = 0; i < numPokemon; i++)
    {
        myBuffer.addAtBack(pokemon[i]);
        /* while we're at it, build the solution string for myBuffer */
        bufferString += "'" + pokemon[i];
        if (i == numPokemon - 1)
        {
            bufferString += "' ";
        }
        else
        {
            bufferString += "', ";
        }
    }
    bufferString += "]";
    assert(myBuffer.toString() == bufferString);

    for (int i = numPokemon - 1; i >= 0; i--)
    {
        assert(pokemon[i] == myBuffer.removeFromBack());
    }
}

/*
 ******** PART 2: TESTING THE STACK ********
 */

/*  testStack()
 *  Purpose: Tests all operations on the Stack
 *  Parameters: pokemon[]  - a predetermined list of pokemon
 *              numPokemon - The number of pokemon in pokemon[]
 *  Return: None
 */
void testStack(string pokemon[], int numPokemon)
{
    cout << "\nThere are no Pokemon in the Stack Pokedex: ";

    Stack myStack;
    assert(myStack.toString() == "[ ]");
    cout << myStack.toString() << endl;

    cout << "\nAdding all 10 pokemon to the stack." << endl;

    string stackString = "";

    /* add all pokemon to the stack */
    for (int i = 0; i < numPokemon; i++)
    {
        myStack.push(pokemon[i]);

        /* build solution string in reverse order to match myStack */
        if (i == 0)
        {
            stackString = "'" + pokemon[i] + "'";
        }
        else
        {
            stackString = "'" + pokemon[i] + "', " + stackString;
        }
    }

    stackString = "[ " + stackString;
    stackString += " ]";
    assert(myStack.toString() == stackString);

    cout << "Our Stack Pokedex contains the following Pokemon: ";
    cout << myStack.toString() << endl;

    cout << "\nWe're missing Luke Ito's favorite bug pokemon. Let's add it!\n";

    myStack.push("Scizor");
    cout << "Added Scizor to the top of the Stack Pokedex.\n";

    cout << "\nLet's remove Scizor, and add another pokemon.\n";
    cout << "Removing " << myStack.pop() << " from the top of the Stack Pokedex\n";

    cout << "\nAdding Vespiquen to the top of the Stack Pokedex!\n";
    myStack.push("Vespiquen");

    cout << "Our Stack Pokedex now contains the following Pokemon: ";
    cout << myStack.toString() << endl;
}

/*
 ******** PART 3: TESTING THE QUEUE ********
 */

/*  testQueue()
 *  Purpose: Tests all operations on the Queue
 *  Parameters: pokemon[]  - a predetermined list of pokemon
 *              numPokemon - The number of pokemon in pokemon[]
 *  Return: None
 */
void testQueue(string pokemon[], int numPokemon)
{
    cout << "\nThere are no Pokemon in the Queue Pokedex: ";

    Queue myQueue;
    assert(myQueue.toString() == "[ ]");
    cout << myQueue.toString() << endl;

    cout << "\nAdding all 10 pokemon to the queue." << endl;

    string queueString = "[ ";

    /* add all pokemon to the queue */
    for (int i = 0; i < numPokemon; i++)
    {
        myQueue.enqueue(pokemon[i]);

        queueString += "'" + pokemon[i];
        if (i == numPokemon - 1)
        {
            queueString += "' ";
        }
        else
        {
            queueString += "', ";
        }
    }

    queueString += "]";

    assert(myQueue.toString() == queueString);

    cout << "Our Queue Pokedex now contains the following Pokemon: ";
    cout << myQueue.toString() << endl;

    cout << "\nWe're missing Luke Ito's favorite bug pokemon. Let's add it!\n";

    myQueue.enqueue("Scizor");
    cout << "Added Scizor to the back of the Queue Pokedex.\n";

    cout << "\nLet's remove Beedrill, and add another pokemon.\n";
    cout << "Removing " << myQueue.dequeue() << " from the front of the Queue Pokedex\n";

    cout << "\nAdding Vespiquen to the back of the Queue Pokedex!\n";
    myQueue.enqueue("Vespiquen");

    cout << "Our Queue Pokedex now contains the following Pokemon: ";
    cout << myQueue.toString() << endl;
}