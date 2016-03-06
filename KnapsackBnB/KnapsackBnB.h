
// ***********************************
//
// Author: Piotr Lawniczak (209775)
//		www.piotrlawniczak.eu
//
// ***********************************

#pragma once
#include "stdafx.h"
#include <queue>
#include <vector>

struct node {
	node(int _level, int _benefit, int _size, int _nrOfItems) { 
		level = _level, benefit = _benefit, size = _size; 
		itemsTaken.assign(_nrOfItems, false);
	}
	int level;
	int benefit, size;
	float bound;
	vector<bool> itemsTaken;	//stores set of items included to the node
};
struct compareBound {			//for priority queue
	bool operator() (const node &firstNode, const node &secondNode) {
		if (firstNode.bound < secondNode.bound)
			return true;
		else return false;
	}
};

typedef priority_queue<node, vector<node>, compareBound> NodesPriorQueue;

class KnapsackBnB {
public:
	KnapsackBnB();						//constructs knapsack with capacity needed to enter later
	KnapsackBnB(int capacity);			
	~KnapsackBnB();
	void bNb(bool test = false);		//main branch&bound algorithm, prints solution on the screen if test is set to false (default)
	void addItem(int size, int benefit);
	void generate(int _capacity, int _nrOfItems);//generates random instance of problem
	void showItems();					//prints all items to ostream
	void setCapacity(int _capacity);
	int getCapacity();
private:
	void quickSort(int left, int right);//for sorting items by quotient of benefit and size in descending order
	float bnfBySize(int index);			//returns quotient of benefit and size for item with given index
	float bound(node u);				//counts upper bound of given node
	void deleteItems();
	vector<int> sizeT;					//array storing size of each item
	vector<int> benefitT;				//array storing benefit of each item
	int capacity;						//max capacity of knapsack
	int nrOfItems;						//counter of items
};