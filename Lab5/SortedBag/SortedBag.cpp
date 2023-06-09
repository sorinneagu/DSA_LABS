#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <stack>
#include <iostream>

SortedBag::SortedBag(Relation r) {
	
	this->root = nullptr;
	this->relation = r;
	this->lenght = 0;

}

BSTNode* SortedBag::getSuccessor(BSTNode* node)
{
	if (node == nullptr) {

		return nullptr;

	 }

	node = node->right;
	while (node->left != nullptr) {

		node = node->left;

	}

	return node;
}

BSTNode* SortedBag::getParent(BSTNode* node) const
{
	BSTNode* current = this->root;
	BSTNode* parent = nullptr;

	while (current != nullptr) {
		
		if (current == node) {

			return parent;
		
		}

		parent = current;
		if (this->relation(current->info, node->info)) {

			current = current->right;

		}

		else {

			current = current->left;

		}

	}
	return parent;
}

void SortedBag::add(TComp e) {
	
	// Creating the new node

	BSTNode* newNode = new BSTNode;
	newNode->info = e;
	newNode->left = nullptr;
	newNode->right = nullptr;

	// Searching for the proper position to add to

	BSTNode* current = this->root;
	BSTNode* prev = nullptr;

	while (current != nullptr) {

		prev = current;
		if (this->relation(current->info, e)) {
			
			current = current->right;

		}

		else {

			current = current->left;
		
		}
	}

	if (this->root == nullptr) { // Empty BST
		
		this->root = newNode;
	
	}
	
	else {

		if (this->relation(prev->info, e)) {

			prev->right = newNode;

		}

		else {

			prev->left = newNode;
		}
	}

	this->lenght++;
}


bool SortedBag::remove(TComp e) {
	
	BSTNode* current = this->root;
	BSTNode* parent = nullptr;

	bool found = false;

	while (current != nullptr && !found) {

		if (current->info == e) {
			
			found = true;

		}
		
		else {
			
			parent = current;
			if (this->relation(current->info, e)) {
				
				current = current->right;

			}

			else {

				current = current->left;
			
			}
		}
	}

	if (!found) {

		return false;

	}

	// No child branch

	if (current->right == nullptr && current->left == nullptr) {

		if (parent == nullptr) {

			this->root = nullptr;

		}


		else {

			if (parent->right = current) {

				parent->right = nullptr;

			}
			
			else {

				parent->left = nullptr;

			}
		}

		this->lenght--;
		return true;
	}

	// One child branch

	else 

	if (current->right == nullptr || current->left == nullptr) {

		BSTNode* child;
			
		if (current->right == nullptr) {

			child = current->left;

		}

		else {

			if (current->left == nullptr) {
				child = current->right;
			}
		}

		if (parent == nullptr) {

			this->root = child;
			
		}

		else {

			if (parent->right == current) {
					
				parent->right = child;

			}
			else {

				parent->left = child;

			}
		}

		this->lenght--;
		return true;
	}
	
	// 2 children branch

	else {
		
		BSTNode* nodeToDelete = current;
		BSTNode* successor = getSuccessor(current);
		parent = getParent(successor);

		parent->left = nullptr;

		nodeToDelete->info = successor->info;
		this->lenght--;
		return true;
	}
}


bool SortedBag::search(TComp elem) const {

	BSTNode* current = this->root;
	if (current == nullptr) {

		return false;

	}
	
	else {
		while (current != nullptr) {

			if (current->info == elem) {

				return true;
			}

			if (this->relation(current->info, elem)) {
				
				current = current->right;

			}

			else {

				current = current->left;

			}
		}
	}
	return false;
}


int SortedBag::nrOccurrences(TComp elem) const {
	
	BSTNode* current = this->root;
	int count = 0;

	if (current == nullptr) {
		
		return 0;
	
	}

	else {

		while (current != nullptr) {

			if (current->info == elem) {

				count++;

			}

			if (this->relation(current->info, elem)) {
				
				current = current->right;

			}

			else {

				current = current->left;

			}
		}
		return count;
	}
}



int SortedBag::size() const {
	return this->lenght;
}


bool SortedBag::isEmpty() const {
	return (this->lenght == 0);
}


SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}


SortedBag::~SortedBag() {
	std::stack<BSTNode*> stack;
	BSTNode* current = this->root;

	while (current != nullptr) {

		stack.push(current);
		current = current->left;

	}

	while (stack.size() != 0) {

		current = stack.top();
		stack.pop();
		current = current->right;

		while (current != nullptr) {

			stack.push(current);
			current = current->left;

		}
		delete current;
	}
}
