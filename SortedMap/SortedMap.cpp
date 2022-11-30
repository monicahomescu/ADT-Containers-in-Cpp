#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
using namespace std;

SortedMap::SortedMap(Relation r) {
	this->rel = r;
	this->nrPairs = 0;
	this->capacity = 1;
	this->elements = new TElem[this->capacity];
}
//Theta(1)

void SortedMap::resize() {
	TElem* newElems = new TElem[this->capacity * 2];
	int index;
	for (index = 0; index < this->nrPairs; index++)
		newElems[index] = this->elements[index];
	delete[] this->elements;
	this->elements = newElems;
	this->capacity *= 2;
}
//Theta(nrPairs)

TValue SortedMap::add(TKey k, TValue v) {
	TValue returnedValue = NULL_TVALUE;
	if (this->capacity == this->nrPairs)
		this->resize();
	bool found = false;
	int index = 0;
	while (found == false && index < this->nrPairs && this->rel(this->elements[index].first, k) == true) 
	{
		if (this->elements[index].first == k) 
		{
			found = true;
			returnedValue = this->elements[index].second;
			this->elements[index].second = v;
		}
		else
			index++;
	}
	if (found == false) 
	{
		if (this->nrPairs > 0)
		{
			int i;
			for (i = this->nrPairs; i > index; i--)
				this->elements[i] = this->elements[i - 1];
		}
		this->elements[index].first = k;
		this->elements[index].second = v;
		this->nrPairs++;
	}
	return returnedValue;
}
//BC: Theta(1), WC: Theta(nrPairs), T: O(nrPairs)

TValue SortedMap::search(TKey k) const {
	TValue returnedValue = NULL_TVALUE;
	bool found = false;
	int index = 0;
	while (found == false && index < this->nrPairs && this->rel(this->elements[index].first, k) == true)
	{
		if (this->elements[index].first == k)
		{
			found = true;
			returnedValue = this->elements[index].second;
		}
		else
			index++;
	}
	return returnedValue;
}
//BC: Theta(1), WC: Theta(nrPairs), T: O(nrPairs)

TValue SortedMap::remove(TKey k) {
	TValue returnedValue = NULL_TVALUE;
	bool found = false;
	int index = 0;
	while (found == false && index < this->nrPairs && this->rel(this->elements[index].first, k) == true)
	{
		if (this->elements[index].first == k)
		{
			found = true;
			returnedValue = this->elements[index].second;
		}
		else
			index++;
	}
	if (found == true)
	{
		int i;
		for (i = index; i < this->nrPairs - 1; i++)
			this->elements[i] = this->elements[i + 1];
		this->nrPairs--;
	}
	return returnedValue;
}
//BC: Theta(nrPairs), WC: Theta(nrPairs), T: Theta(nrPairs)

int SortedMap::size() const {
	return this->nrPairs;
}
//Theta(1)

bool SortedMap::isEmpty() const {
	if (this->nrPairs == 0)
		return true;
	else
		return false;
}
//Theta(1)

SMIterator SortedMap::iterator() const {
	return SMIterator(*this);
}
//Theta(1)

SortedMap::~SortedMap() {
	delete[] this->elements;
}
//Theta(1)
