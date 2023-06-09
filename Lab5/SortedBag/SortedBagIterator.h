#pragma once
#include "SortedBag.h"
#include <stack>

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
	const SortedBag& bag;
	SortedBagIterator(const SortedBag& b);

	//TODO - Representation

	BSTNode* current;
	std::stack<BSTNode*> s;
public:
	TComp getCurrent();
	bool valid();
	void next();
	void first();
};

