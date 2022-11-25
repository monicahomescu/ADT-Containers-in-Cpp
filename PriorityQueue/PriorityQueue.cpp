
#include "PriorityQueue.h"
#include <exception>
using namespace std;

PriorityQueue::PriorityQueue(Relation r) {
	this->length = 0;
	this->rel = r;
	this->firstFree = 0;
	this->head = -1;
	this->cap = 10;
	this->nodes = new SLLANode[this->cap];
	for (int i = 0; i < this->cap - 1; i++)
		this->nodes[i].next = i + 1;
	this->nodes[this->cap - 1].next = -1;
}
//Theta(cap)

void PriorityQueue::resize() {
	SLLANode* newNodes = new SLLANode[this->cap * 2];
	for (int i = 0; i < this->cap; i++)
		newNodes[i] = this->nodes[i];
	for (int i = this->cap; i < this->cap * 2 - 1; i++)
		newNodes[i].next = i + 1;
	newNodes[this->cap - 1].next = -1;
	this->firstFree = this->cap;
	this->cap *= 2;
	delete[] this->nodes;
	this->nodes = newNodes;
}
//Theta(cap)

void PriorityQueue::push(TElem e, TPriority p) {
	if (this->length == this->cap)
		 this->resize();
	int newNode = this->firstFree;
	this->firstFree = this->nodes[firstFree].next;
	if (this->length == 0)
		this->head = newNode;
	else {
		int current = this->head;
		int previous = -1;
		while (current != -1) {
			previous = current;
			current = this->nodes[current].next;
		}
		this->nodes[previous].next = newNode;
	}
	this->nodes[newNode].info.first = e;
	this->nodes[newNode].info.second = p;
	this->nodes[newNode].next = -1;
	this->length++;
}
//BC:Theta(1), WC:Theta(length); T:O(length)

//throws exception if the queue is empty
Element PriorityQueue::top() const {
	if (this->length == 0)
		throw exception();
	int current = this->head;
	int elem = current;
	while (current != -1) {
		if (this->rel(this->nodes[current].info.second, this->nodes[elem].info.second))
			elem = current;
		current = this->nodes[current].next;
	}
	return this->nodes[elem].info;
}
//Theta(length)

Element PriorityQueue::pop() {
	if (this->length == 0)
		throw exception();
	int current = this->head;
	int previous = -1;
	Element highest = top();
	while (current != -1 && !(this->nodes[current].info.first == highest.first && this->nodes[current].info.second == highest.second)) {
		previous = current;
		current = this->nodes[current].next;
	}
	if (current == this->head)
		this->head = this->nodes[current].next;
	else
		this->nodes[previous].next = this->nodes[current].next;
	this->nodes[current].next = this->firstFree;
	this->firstFree = current;
	this->length--;
	return this->nodes[current].info;
}
//BC:Theta(1), WC:Theta(length); T:O(length)

bool PriorityQueue::isEmpty() const {
	if (this->length == 0)
		return true;
	return false;
}
//Theta(1)

PriorityQueue::~PriorityQueue() {
	delete[] this->nodes;
};
//Theta(1)

TPriority PriorityQueue::priorityOf(TElem elem) const
{
	int current = this->head;
	TPriority p = -1;
	while (current != -1) {
		if (this->nodes[current].info.first == elem)
		{
			p = this->nodes[current].info.second;
			break;
		}
		current = this->nodes[current].next;
	}
	return p;
}
//BC:Theta(1), WC:Theta(length); T:O(length)