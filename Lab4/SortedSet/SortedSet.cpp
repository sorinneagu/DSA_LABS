#include "SortedSet.h"
#include "SortedSetIterator.h"
#include <iostream>

// Theta(Capacity)
SortedSet::SortedSet(Relation r)
{
    this->length = 0;
    this->capacity = 13;
    this->hashTable = new SLL[this->capacity];

    //initial lists are empty
    for (int i = 0; i < this->capacity; i++)
        this->hashTable[i].head = nullptr;


    this->MOD = this->capacity;
    this->relation = r;
}

// O(length) + O(MOD + length) + O(Length) = O(MOD + 3length) = O(MOD + length)
bool SortedSet::add(TComp elem)
{

    // Elem is already in the set
    if (search(elem))
        return false;

    // Set needs resize bc LOADFACTOR was reached
    if (this->length * 1.0 / this->MOD * 1.0 >= LOADFACTOR)
        resize();

    // Computing the hashvalue for elem and creating a node with value==elem
    int position = abs(elem % this->MOD);
    Node* newNode = new Node();
    newNode->value = elem;
    newNode->next = nullptr;


    // If the head of the list at this hashvalue is nullptr => the node we want to add is the first in this list
    if (this->hashTable[position].head == nullptr)
    {
        this->hashTable[position].head = newNode;
    }
    else
    {   // We search for the position to insert to (so the elements in the lists are ordered)
        Node* current;
        Node* prev;
        current = this->hashTable[position].head;
        prev = nullptr;
        // We start from the head of the list and proceed untill the end of the list or untill the relation is not satisfied anymore
        while (current != nullptr && this->relation(current->value, newNode->value)) {
            prev = current;
            current = current->next;
        }
        // Position should be head of the list
        if (prev == nullptr)
        {
            newNode->next = this->hashTable[position].head;
            this->hashTable[position].head = newNode;
        }
        else
        {   // Somewhere in the list
            prev->next = newNode;
            newNode->next = current;
        }

    }
    //increase SortedSet size
    this->length++;
    return true;
}

// O(length)
bool SortedSet::remove(TComp elem)
{
    // Compute hashvalue for elem
    int position = abs(elem % this->MOD);

    if (this->hashTable[position].head == nullptr) // Nothing found at this hashvalue => nothing to remove
        return false;

    // If there is something at this hashvalue we parse the list untill we find the elem or end of list is reached
    Node* current = this->hashTable[position].head;
    Node* prev = nullptr;

    while (current != nullptr && current->value != elem) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) // element not found
        return false;

    if (prev == nullptr && current->value == elem) // element to remove is  head of sll at this hashvalue
    {
        this->hashTable[position].head = current->next;
        delete current;
        this->length--;
        return true;
    }
    else
        if (current->next == nullptr && current->value == elem) // element to remove is the last elem of the sll at this hashvalue
        {
            prev->next = nullptr;
            delete current;
            this->length--;
            return true;
        }
        else {   //somewhere in the list
            prev->next = current->next;
            delete current;
            this->length--;
            return true;
        }


}


// O(length)
bool SortedSet::search(TComp elem) const
{
    //compute hashvalue
    int position = abs(elem % this->MOD);
    Node* current;
    //parse list from this hashvalue
    current = this->hashTable[position].head;
    while (current != nullptr && current->value != elem)
        current = current->next;

    // if current == nullptr it means that the list was empty or the element was not found => return false
    if (current != nullptr && current->value == elem)
        return true;
    return false;
}

// Theta(1)
int SortedSet::size() const
{
    return this->length;
}

// Theta(1)
bool SortedSet::isEmpty() const
{
    if (this->length == 0)
        return true;
    return false;
}

// Theta(1)
SortedSetIterator SortedSet::iterator() {
    return SortedSetIterator(*this);
}

// Theta(MOD)
SortedSet::~SortedSet()
{
    // Delete every sll from the hashtable
    for (int i = 0; i < this->capacity; i++)
        delete this->hashTable[i].head;
    // Delete the sll that contained the slls
    delete[] this->hashTable;
}


void SortedSet::resize() {
    // Get all values from current SortedSet
    int* allValues = new int[this->MOD];
    int counter = 0;

    for (int i = 0; i < this->MOD; i++)
    {
        Node* current = this->hashTable[i].head;
        while (current != nullptr)
        {
            allValues[counter++] = current->value;
            current = current->next;
        }
    }

    // Double the capacity
    this->MOD *= 2;
    this->capacity *= 2;
    this->length = 0;
    SLL* newHashTable = new SLL[this->MOD];

    // Create new hash table
    for (int i = 0; i < this->MOD; ++i) {
        newHashTable[i].head = nullptr;
    }

    delete[] hashTable;
    this->hashTable = newHashTable;

    // Rehash all the elements from the old hashTable
    for (int i = 0; i < counter; i++)
        add(allValues[i]);
}


bool SortedSet::isSubsetOf(SortedSet& s) {

    for (int i = 0; i < this->MOD; i++)
    {
        Node* current = this->hashTable[i].head;
        while (current != nullptr)
        {
            if (!s.search(current->value))
            {
                return false;
            }
            current = current->next;
        }
    }
    return true;
}