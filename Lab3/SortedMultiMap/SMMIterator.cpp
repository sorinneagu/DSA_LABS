#include "SMMIterator.h"
#include "SortedMultiMap.h"
// Everything here has Theta(1) complexity.


SMMIterator::SMMIterator(const SortedMultiMap & d) : map(d) {
    //TODO - Implementation
    current = map.head;
}

void SMMIterator::first() {
    //TODO - Implementation
    current = map.head;
}

void SMMIterator::next() {
    //TODO - Implementation
    if (current != -1)
        current = map.next[current];
    else
    {
        exception e;
        throw e;
    }
}

bool SMMIterator::valid() const {
    //TODO - Implementation
    if (current != -1)
        return true;
    return false;
}

TElem SMMIterator::getCurrent() const {
    //TODO - Implementation
    if (current != -1)
        return map.elements[current];
    else
    {
        exception e;
        throw e;
    }
}
