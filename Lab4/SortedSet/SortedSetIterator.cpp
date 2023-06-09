#include "SortedSetIterator.h"
#include <exception>

using namespace std;

SortedSetIterator::SortedSetIterator(SortedSet& m) : multime(m)
// Theta(MOD)
{
    // Clone the hashtable locally
    itHashTable = new Node * [m.MOD];

    first();
}

void SortedSetIterator::first()
// Theta(MOD)
{
    // Clone the hashtable locally
    for (int i = 0; i < multime.MOD; i++)
        itHashTable[i] = multime.hashTable[i].head;

    // Search for minimum value (with respect to the relation) from the locally cloned hashtable
    Node* first = nullptr;
    int position;
    for (int i = 0; i < multime.MOD; i++)
    {
        if (itHashTable[i] == nullptr)
            continue;

        if (first == nullptr || multime.relation(itHashTable[i]->value, first->value))
        {
            first = itHashTable[i];
            position = i;
        }
    }

    // Minimum was found
    if (first != nullptr)
    {
        currentElement = first->value;
        itHashTable[position] = itHashTable[position]->next; // Eliminate node 'first' from the locally cloned hashTable
    }
    else
        currentElement = NULL_TELEM;
}


void SortedSetIterator::next()
// Theta(MOD)
{
    // If iterator not valid throw exception
    if (!valid())
        throw std::exception();

    // Search for next element
    Node* next = nullptr;
    int position;
    for (int i = 0; i < multime.MOD; i++)
    {
        // Empty sll at this hashvalue
        if (itHashTable[i] == nullptr) continue;

        // If next was not found yet or there is a value closer to the current one that satisfies the relation => next = newValue
        if (next == nullptr || multime.relation(itHashTable[i]->value, next->value))
        {
            next = itHashTable[i];
            position = i;
        }
    }
    // Next element was found
    if (next != nullptr)
    {
        // Set current element to next and eliminate the node 'next' from the iterator hashTable
        currentElement = next->value;
        itHashTable[position] = itHashTable[position]->next;
    }
    else
        currentElement = NULL_TELEM;
}


TElem SortedSetIterator::getCurrent() const
// Theta(1)
{
    if (!valid())
        throw std::exception();
    return currentElement;
}

bool SortedSetIterator::valid() const
// Theta(1)
{
    return (currentElement != NULL_TELEM);
}
