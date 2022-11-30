#pragma once
#include "SortedIteratedList.h"

class ListIterator {
	friend class SortedIteratedList;
	
private:
	const SortedIteratedList& list;
	ListIterator(const SortedIteratedList& list);
	SLLNode* current;
	
public:
	void first();
	void next();
	bool valid() const;
        TComp getCurrent() const;
	TComp getNext() const;
};
