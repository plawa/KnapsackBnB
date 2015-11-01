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
struct compareBound {
	bool operator() (const node &firstNode, const node &secondNode) {
		if (firstNode.bound < secondNode.bound)
			return true;
		else return false;
	}
};

struct item {
	//constructor for new item
	item(int _size, int _benefit, int _no) {
		size = _size, benefit = _benefit, no = _no;
	}
	//variables keeping size & benefit of item
	int size, benefit, no;
};
struct compareBenefitBySize {
	bool operator() (const item &firstItem, const item &secondItem) {
		if (static_cast<double>(firstItem.benefit) / static_cast<double>(firstItem.size) <
		static_cast<double>(secondItem.benefit) / static_cast<double>(secondItem.size))
			return true;
		else return false;
	}
};

typedef priority_queue<node, vector<node>, compareBound> NodesPriorQueue;
typedef priority_queue<item, vector<item>, compareBenefitBySize> ItemsPriorQueue;

class KnapsackBnB {
public:
	KnapsackBnB();
	KnapsackBnB(int capacity);
	~KnapsackBnB();
	void bNb();
	void addItem(int size, int benefit);
	void generate(int _capacity, int _nrOfItems);
	void showItems();
	void setCapacity(int _capacity);
	int getCapacity();
private:
	void quickSort(int left, int right);
	float bnfBySize(int index);
	float bound(node u);
	vector<int> sizeT;
	vector<int> benefitT;
	ItemsPriorQueue itemsQueue;
	int capacity;
	int nrOfItems;			//counter of items
	TimeMeasure timer;
};