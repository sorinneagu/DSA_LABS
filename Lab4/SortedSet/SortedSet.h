#pragma once
//DO NOT INCLUDE SETITERATOR

//DO NOT CHANGE THIS PART
typedef int TElem;
typedef TElem TComp;
typedef bool(*Relation)(TComp, TComp);
#define NULL_TELEM -11111
#define LOADFACTOR 0.7

class SortedSetIterator;

class Node {
public:
    TElem value;
    Node* next;
};

class SLL {
public:Node* head;
};

class SortedSet {
    friend class SortedSetIterator;

private:
    SLL* hashTable;
    int MOD;
    int length;
    int capacity;
    Relation relation;

public:
    //constructor
    explicit SortedSet(Relation r);

    // adds an element to the sorted set
    // if the element was added, the operation returns true, otherwise (if the element was already in the set)
    // it returns false
    bool add(TComp e);


    //removes an element from the sorted set
    //if the element was removed, it returns true, otherwise false
    bool remove(TComp e);

    //checks if an element is in the sorted set
    bool search(TElem elem) const;


    //returns the number of elements from the sorted set
    int size() const;

    //checks if the sorted set is empty
    bool isEmpty() const;

    //returns an iterator for the sorted set
    SortedSetIterator iterator();

    // destructor
    ~SortedSet();

    void resize();

    bool isSubsetOf(SortedSet& s);
};