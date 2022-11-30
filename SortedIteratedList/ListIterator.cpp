#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <exception>
using namespace std;

ListIterator::ListIterator(const SortedIteratedList& list) : list(list) {
	this->current = list.head;
}
//Theta(1)

void ListIterator::first() {
	this->current = this->list.head;
}
//Theta(1)

void ListIterator::next() {
	if (this->current == NULL)
		throw exception();
	else
		this->current = this->current->next;
}
//Theta(1)

bool ListIterator::valid() const {
	if (this->current == NULL)
		return false;
	else
		return true;
}
//Theta(1)

TComp ListIterator::getCurrent() const {
	if (this->current == NULL)
		throw exception();
	else
		return this->current->info;
}
//Theta(1)

TComp ListIterator::getNext() const {
	if (this->current->next == NULL)
		throw exception();
	else
		return this->current->next->info;
}
//Theta(1)
