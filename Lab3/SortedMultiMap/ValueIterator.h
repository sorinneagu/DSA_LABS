#pragma once

#include "SortedMultiMap.h"

class ValueIterator {
    friend class SortedMultiMap;
private:
    //DO NOT CHANGE THIS PART
    const SortedMultiMap& map;
    int current;
    TKey key;

public:
    ValueIterator(const SortedMultiMap& map, TKey k);
    void first();
    void next();
    bool valid() const;
    TValue getCurrent() const;
};
