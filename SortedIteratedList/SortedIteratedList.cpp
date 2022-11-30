#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <iostream>
using namespace std;
#include <exception>

SortedIteratedList::SortedIteratedList(Relation r) {
	this->head = NULL;
	this->relation = r;
}
//Theta(1)

int SortedIteratedList::size() const {
	int s = 0;
	SLLNode* current = this->head;
	while (current != NULL) {
		s++;
		current = current->next;
	}
	return s;
}
//O(n)

bool SortedIteratedList::isEmpty() const {
	if (this->head == NULL)
		return true;
	else
		return false;
}
//Theta(1)

ListIterator SortedIteratedList::first() const {
	return ListIterator(*this);
}
//Theta(1)

TComp SortedIteratedList::getElement(ListIterator poz) const {
	return poz.getCurrent();
}
//Theta(1)

TComp SortedIteratedList::remove(ListIterator& poz) {
	if (poz.valid() == false)
		throw exception();
	TComp old;
	SLLNode* current = this->head;
	if (current == NULL)
		throw exception();
	SLLNode* previous = NULL;
	while (current != NULL && poz.current != current) {
		previous = current;
		current = current->next;
	}
	if (current != NULL) {
		old = current->info;
		if (current == this->head && previous == NULL) {
			if (current->next == NULL) {
				//list only contains element to remove
				this->head = NULL;
			}
			else {
				//element to remove is in first position
				this->head->info = this->head->next->info;
				this->head->next = this->head->next->next;
			}
		}
		else if (current->next == NULL) {
			//element to remove is in last position
			previous->next = NULL;
			current = NULL;
		}
		else {
			//element to remove is in the middle
			current->info = current->next->info;
			current->next = current->next->next;
		}
	}
	else
		throw exception();
	return old;
}
//BC: Theta(1), WC: Theta(n), T:O(n)

ListIterator SortedIteratedList::search(TComp e) const {
	ListIterator it{ *this };
	it.first();
	while (it.valid() == true && it.getCurrent() != e)
		it.next();
	return it;
}
//BC: Theta(1), WC: Theta(n), T:O(n)

void SortedIteratedList::add(TComp e) {
	if (this->head == NULL) {
		//list is empty
		SLLNode* newNode = new SLLNode();
		newNode->info = e;
		newNode->next = NULL;
		this->head = newNode;
	}
	else {
		SLLNode* current = this->head;
		SLLNode* previous = NULL;
		while (current != NULL && this->relation(current->info, e) == true) {
			previous = current;
			current = current->next;
		}
		if (current == NULL && previous != NULL) {
			//element is added at the end of the list
			SLLNode* newNode = new SLLNode();
			newNode->info = e;
			newNode->next = NULL;
			previous->next = newNode;
		}
		else if (current == this->head && previous == NULL) {
			//element is added in front of the list
			SLLNode* newNode = new SLLNode();
			newNode->info = e;
			newNode->next = current;
			this->head = newNode;
		}
		else {
			//elemnt is added in the middle of the list
			SLLNode* newNode = new SLLNode();
			newNode->info = e;
			newNode->next = current;
			previous->next = newNode;
		}
	}
}
//BC: Theta(1), WC: Theta(n), T:O(n)

SortedIteratedList::~SortedIteratedList() {
	SLLNode* current = this->head;
	while (current != NULL) {
		this->head = current->next;
		delete current;
		current = this->head;
	}
}
//O(n)
