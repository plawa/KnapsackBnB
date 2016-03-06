
// ***********************************
//
// Author: Piotr Lawniczak (209775)
//		www.piotrlawniczak.eu
//
// ***********************************

#include "stdafx.h"
#include "KnapsackBnB.h"
#include <ctime>


//creates new knapsack with default capacity of 0
KnapsackBnB::KnapsackBnB()
{
	KnapsackBnB(0);
}
KnapsackBnB::KnapsackBnB(int capacity_)
{
	srand((size_t)time(NULL)); //for generating random instances of problem
	capacity = capacity_;
	nrOfItems = 0;
}
KnapsackBnB::~KnapsackBnB()
{
}

void KnapsackBnB::bNb(bool test)
{
	NodesPriorQueue PQ;
	node u(-1, 0, 0, nrOfItems);
	node v(-1, 0, 0, nrOfItems);		//root: level = -1, because of array index starts from 0
	int maxBenefit = 0;					//benefit of the best combination found so far
	int steps = 0;						//holds steps made until optimal solution is found
	vector<bool> bestItems;				//stores set of best combination found so far
	bestItems.assign(nrOfItems, false); //to start, fulfills array with false values, amount of nrOfItems
	v.bound = bound(v);
	PQ.push(v);

	while (!PQ.empty())
	{
		steps++;
		v = PQ.top();	//take node with best bound
		PQ.pop();		//remove from queue
		if (v.bound > maxBenefit) 
		{
			u.level = v.level + 1;
			u.size = v.size + sizeT[u.level];
			u.benefit = v.benefit + benefitT[u.level];
			u.itemsTaken = v.itemsTaken;		//copying array of items taken
			u.itemsTaken[u.level] = true;		//mark u.level-th item as taken

			if (u.size <= capacity && u.benefit > maxBenefit) 
			{
				maxBenefit = u.benefit;
				for (int i = 0; i <= u.level; i++) 
					bestItems[i] = u.itemsTaken[i];
			}
			u.bound = bound(u);
			if (u.bound > maxBenefit)
				PQ.push(u);

			u.size = v.size;
			u.benefit = v.benefit;
			u.bound = bound(u);
			u.itemsTaken[u.level] = false;
			if (u.bound > maxBenefit)
				PQ.push(u);
		}
	}
	if (!test) 
	{
		cout << endl << " Items taken (descending order by Ben/Size):" << endl;
		for (int i = 0; i < nrOfItems; i++)
			if (bestItems[i])
				cout << " Benefit: " << benefitT[i] << ", size: " << sizeT[i] << endl;
		cout << endl << " MaxBenefit: " << maxBenefit << endl << endl << " Steps made: " << steps << endl << endl;
	}
}

float KnapsackBnB::bound(node u) 
{
	int  j, k;							//indexes
	int totalSize;
	float result;

	if (u.size >= capacity)				//if size of item is bigger than knapsack's capacity
		return 0;						//then finish computing the bound
	else
	{
		result = static_cast<float>(u.benefit);
		j = u.level + 1;				//lower level
		totalSize = u.size;
		while (j < nrOfItems && totalSize + sizeT[j] <= capacity) //add items until the knapsack is full or there is any item left
		{
			totalSize += sizeT[j];
			result += benefitT[j++];	//!INCREASES j by 1!
		}
		k = j;
		if (k < nrOfItems)
			result += (capacity - totalSize) * benefitT[k] / sizeT[k];//takes the franction of item
		return result;
	}
}

void KnapsackBnB::deleteItems()
{
	nrOfItems = 0;
	benefitT.clear();
	sizeT.clear();
}

void KnapsackBnB::quickSort(int left, int right) 
{
	int i = left;
	int j = right;
	float x = bnfBySize((left + right) / 2);
	do 
	{
		while (bnfBySize(i) > x)
			i++;
		while (bnfBySize(j) < x)
			j--;
		if (i <= j) 
		{
			swap(benefitT[i], benefitT[j]);
			swap(sizeT[i], sizeT[j]);
			i++;
			j--;
		}
	} while (i <= j);

	if (left < j) 
		quickSort(left, j);

	if (right > i)
		quickSort(i, right);
}

float KnapsackBnB::bnfBySize(int index) {
	return static_cast<float>(benefitT[index]) / static_cast<float>(sizeT[index]);
}

void KnapsackBnB::addItem(int size, int benefit)
{
	sizeT.push_back(size);
	benefitT.push_back(benefit);
	nrOfItems++;
	quickSort(0, nrOfItems - 1);
}

void KnapsackBnB::generate(int _capacity, int _nrOfItems)
{
	deleteItems();
	capacity = _capacity;
	int totalSize = 0;
	for (int i = 0; i < _nrOfItems - 1; i++) {	//adds one less items than demanded
		int size = rand() % 20 + 1;				//range: 1-20
		int benefit = rand() % 50 + 1;			//range: 1-50
		addItem(size, benefit);
		totalSize += size;
	}
	if (totalSize < capacity) {
		int size = _capacity - totalSize + rand() % 20 + 1;
		int benefit = rand() % 50 + 1;
		addItem(size, benefit);
	}
	else {
		int size = rand() % 20 + 1;	
		int benefit = rand() % 50 + 1;
		addItem(size, benefit);
	}
}


void KnapsackBnB::showItems()
{
	cout << "\n Knapsack capacity: " << capacity << endl << endl;
	for (int i = 0; i < nrOfItems; i++)
		cout << " Benefit: " << benefitT[i] << ", Size: " << sizeT[i] << ", Ben/Size: " << bnfBySize(i) << endl;
	cout << endl;
}

void KnapsackBnB::setCapacity(int _capacity)
{
	capacity = _capacity;
}

int KnapsackBnB::getCapacity()
{
	return capacity;
}



//*********************************************************************************************
//
//									T R A S H
//
//*********************************************************************************************


//void KnapsackBnB::breadthFirstSearch()
//{
//	listToArrays();
//	//dynamically allocate and copy original
//	queue<node> Q;					//queue of nodes
//	node u(0, 0, 0, nrOfItems);		//initialized by '0' values and amount of items for initialize bool array of items taken
//	node v(-1, 0, 0, nrOfItems);	//root
//	int maxBenefit = 0;
//	bool *bestItems = new bool[nrOfItems] { false };	//stores set of best combination found so far
//	Q.push(v);
//
//	int steps = 0;
//
//	while (!Q.empty())
//	{
//		steps++;
//		v = Q.front();				//take the node
//		Q.pop();					//and remove it from queue
//		u.level = v.level + 1;		//go lower in tree
//		u.size = v.size + sizeT[u.level];
//		u.benefit = v.benefit + benefitT[u.level];
//		for (int i = 0; i < u.level; i++)			//copying array of items taken
//			u.itemsTaken[i] = v.itemsTaken[i];
//		u.itemsTaken[u.level] = true;				//mark u.level-th item as taken
//
//		if (u.size <= capacity && u.benefit > maxBenefit) {
//			maxBenefit = u.benefit;
//			for (int i = 0; i <= u.level; i++) {
//				bestItems[i] = u.itemsTaken[i];
//			}
//		}
//		if (bound(u) > maxBenefit)
//			Q.push(u);
//		u.size = v.size;		//node u = node v
//		u.benefit = v.benefit;
//		u.itemsTaken[u.level] = false;
//		if (bound(u) > maxBenefit)
//			Q.push(u);
//	}
//
//	cout << endl << " Items taken (descending order):" << endl;
//	for (int i = 0; i < nrOfItems; i++)
//		if (bestItems[i])
//			cout << " Benefit: " << benefitT[i] << ", size: " << sizeT[i] << endl;
//	cout << endl << " MaxBenefit: " << maxBenefit << endl << endl << " Steps made: " << steps << endl;
//}