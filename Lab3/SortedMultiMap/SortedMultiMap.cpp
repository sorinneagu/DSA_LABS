#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include "ValueIterator.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

//Theta(capacity)
SortedMultiMap::SortedMultiMap(Relation r) {
    this->relation = r;
    this->capacity = 50;
    this->elements = new TElem[this->capacity];
    this->next = new int[this->capacity];
    this->head = -1;
    for (int i = 0; i < this->capacity; i++)
        this->next[i] = i + 1;
    this->next[this->capacity - 1] = -1;
    this->firstEmpty = 0;
    this->nrElements = 0;
}


//Complexity: O(n)
void SortedMultiMap::add(TKey c, TValue v) {
    //list is full , resize is needed
    if (firstEmpty == -1)
    {
        this->resize();
    }
    else
    {   //insert element into element list
        int pos = firstEmpty;
        firstEmpty = this->next[firstEmpty];
        this->elements[pos] = make_pair(c, v);
        this->next[pos] = -1;

        //list is empty => insert on first position / set element as head
        if (this->head == -1)
        {
            this->head = pos;
            nrElements++;
        }
        else
        {
            //find the proper position for element to be inserted
            int current = this->head;
            int prev = -1;
            while (current != -1 && (relation(this->elements[current].first, c)))
            {
                prev = current;
                current = this->next[current];
            }

            //element should be on positions between 1 and nrElements
            if (prev != -1)
            {
                this->next[pos] = this->next[prev];
                this->next[prev] = pos;
                this->nrElements++;
            }
            else
                //element should be on position 0
            {
                this->next[pos] = this->head;
                this->head = pos;
                this->nrElements++;
            }

        }
    }
}

//Complexity: O(n)
vector<TValue> SortedMultiMap::search(TKey c) const {
    vector <TValue> result;
    int current = this->head;

    //parsing the list until reaching key c
    while (current != -1 && this->elements[current].first != c)
    {
        current = this->next[current];
    }

    //adding all the values from key c to the result set
    while (current != -1 && this->elements[current].first == c)
    {
        result.push_back(this->elements[current].second);
        current = this->next[current];
    }
    return result;
}

//Complexity: O(n)
bool SortedMultiMap::remove(TKey c, TValue v) {
    int prev = 0;
    int current = this->head;

    //parsing the list until reaching key c
    while (current != -1 && this->elements[current].first != c)
    {
        prev = current;
        current = this->next[current];
    }

    //parsing the list until reaching value v
    while (current != -1 && this->elements[current].first == c && this->elements[current].second != v)
    {
        prev = current;
        current = this->next[current];
    }

    //removing element if element was found
    if (current != -1 && this->elements[current].first == c && this->elements[current].second == v) {
        if (current == this->head)
            this->head = this->next[this->head];
        else
            this->next[prev] = this->next[current];

        this->next[current] = this->firstEmpty;
        this->firstEmpty = current;
        this->nrElements--;
        return true;
    }
    return false;
}

//Theta(1)
int SortedMultiMap::size() const {
    return  this->nrElements;
}

//Theta(1)
bool SortedMultiMap::isEmpty() const {
    if (this->nrElements == 0)
        return true;
    return false;
}

//Complexity: Theta(newCapacity)
void SortedMultiMap::resize() {
    int newCapacity = this->capacity * 2;
    auto* newElements = new TElem[newCapacity];
    int* newNext = new int[newCapacity];
    for (int i = 0; i < this->capacity; i++) {
        newElements[i] = this->elements[i];
        newNext[i] = this->next[i];
    }

    for (int i = this->capacity; i < newCapacity - 1; i++) {
        newNext[i] = i + 1;
    }
    newNext[newCapacity - 1] = -1;

    delete[] this->elements;
    delete[] this->next;

    this->elements = newElements;
    this->next = newNext;
    this->firstEmpty = this->capacity;
    this->capacity = newCapacity;
}

//Theta(1)
SMMIterator SortedMultiMap::iterator() const {

    return SMMIterator(*this);
}

//Theta(1)
ValueIterator SortedMultiMap::valueIterator(TKey k) const {
    return ValueIterator(*this, k);
}


//Theta(1)
SortedMultiMap::~SortedMultiMap() {
    delete[] this->elements;
    delete[] this->next;
}