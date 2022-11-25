#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
//typedef std::pair<int, int>;
#define NULL_TELEM 0

struct Node {
	int line;
	int column;
	TElem value;
	Node* next;
};

class Matrix {

private:
	int nrL;
	int nrC;
	int size;
	int cap;
	Node **chain;
	void resize();

public:
	//constructor
	Matrix(int nrLines, int nrCols);

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

	//pair<int, int> positionOf(TElem elem) const;
};
