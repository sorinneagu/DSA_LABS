#include "ValueIterator.h"

//Everything here has Theta(1) complexity.


ValueIterator::ValueIterator(const SortedMultiMap& map, const TKey k) :
    map{ map },
    key{ k }
{
    this->current = -1;
    int pos = map.head;
    bool found = false;
    //parsing the list until reaching key k
    while (pos != -1 && map.elements[pos].first != key)
    {
        pos = map.next[pos];
        found = true;
    }
    if (found) {
        this->current = pos;
    }
}

void ValueIterator::first() {
    //TODO - Implementation
    this->current = -1;
    int pos = map.head;
    bool found = false;
    //parsing the list until reaching key k
    while (pos != -1 && map.elements[pos].first != key)
    {
        pos = map.next[pos];
        found = true;
    }
    if (found) {
        this->current = pos;
    }
}

void ValueIterator::next() {
    //TODO - Implementation
    if (this->valid())
        current = map.next[current];
    else
    {
        exception e;
        throw e;
    }
}

bool ValueIterator::valid() const {
    //TODO - Implementation
    if (this->current != -1 && this->map.elements[current].first == this->key)
        return true;
    return false;
}

TValue ValueIterator::getCurrent() const {
    //TODO - Implementation
    if (valid())
        return map.elements[current].second;
    else
    {
        exception e;
        throw e;
    }
}

