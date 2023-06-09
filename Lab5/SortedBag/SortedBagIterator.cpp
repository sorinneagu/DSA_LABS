#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {

	BSTNode* node = bag.root;

	while (node != nullptr) {
		this->s.push(node);
		node = node->left;
	}

	if (!this->s.empty()) {
		this->current = this->s.top();
	}

	else {
		this->current = nullptr;
	}
}

TComp SortedBagIterator::getCurrent() {

	if (this->current == nullptr) {

		throw exception();
	
	}

	else {

		return this->current->info;
	
	}
}

bool SortedBagIterator::valid() {
	
	return (this->current != nullptr);

}

void SortedBagIterator::next() {
	
	if (this->current == nullptr) {

		throw exception();

	}

	BSTNode* node = this->s.top();
	this->s.pop();

	if (node->right != nullptr) {

		node = node->right;
		while (node != nullptr) {

			this->s.push(node);
			node = node->left;

		}
	}
	
	if (!this->s.empty()) {

		this->current = this->s.top();

	}

	else {

		this->current = nullptr;

	}
}

void SortedBagIterator::first() {

	BSTNode* node = bag.root;

	while (node != nullptr) {

		this->s.push(node);
		node = node->left;

	}

	if (!this->s.empty()) {

		this->current = this->s.top();

	}

	else {

		this->current = nullptr;

	}
}

