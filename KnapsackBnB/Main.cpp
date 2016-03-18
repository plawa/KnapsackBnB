
// ***********************************
//
// Author: Piotr Lawniczak (209775)
//		www.piotrlawniczak.eu
//
// ***********************************

#include "stdafx.h"
#include "KnapsackBnB.h"
#include <thread>

#define INFO "\n ********************************************\n\n"\
			"  Branch & Bound solver of knapsack problem\n\n"\
			" ********************************************\n\n"
#define MENU " 1. Add item\n"\
			" 2. Generate an instance of problem\n"\
			" 3. Solve problem - Branch & Bound algorithm\n"\
			" 4. Run experiment - Single Thread\n"\
			" 5. Run experiment - Multiple Threads\n"\
			" 0. Exit\n\n "
void addItem(KnapsackBnB& _knapsack);
void generateInstance(KnapsackBnB& _knapsack);
void experimentWithSingleThread();
void experimentWithMultipleThreads();
void solve(KnapsackBnB knap);

int main()
{
	KnapsackBnB knapsack;
	unsigned char choice;
	
	cout << INFO;
	while (true) {
		do {
			cout << MENU;
			scanf_s("%hhd", &choice);
			fflush(stdin);
		} while (choice >= 6);
		switch (choice) {
		case 1:
			addItem(knapsack);
			knapsack.showItems();
			break;
		case 2:
			generateInstance(knapsack);
			knapsack.showItems();
			break;
		case 3:
			knapsack.bNb();
			break;
		case 4:
			experimentWithSingleThread();
			break;
		case 5:
			experimentWithMultipleThreads();
			break;
		case 0:
			exit(0);
		default:
			cout << " The number you've chosen does not exist!" << endl;
		}
		fflush(stdin);
	}


	knapsack.showItems();
	knapsack.bNb();
	getchar();
	return 0;
}


void addItem(KnapsackBnB& _knapsack) {
	int tempSize, tempBenefit, amount;
	if (!_knapsack.getCapacity()) {  //if capacity is 0 = is not set
		cout << " Enter knapsack's capacity: ";
		cin >> tempSize;
		_knapsack.setCapacity(tempSize);
	}
	cout << " Enter amout of items you want to add: ";
	cin >> amount;
	for (int i = 1; i <= amount; i++) {
		cout << " Enter the size of " << i << " item: ";
		cin >> tempSize;
		cout << " Enter the benefit of " << i << " item: ";
		cin >> tempBenefit;
		_knapsack.addItem(tempSize, tempBenefit);
	}
}


void generateInstance(KnapsackBnB& _knapsack) {
	int amount, cap;
	cout << " Enter capacity of knapsack: ";
	scanf_s("%d", &cap);
	cout << " Enter amount of items to generate: ";
	scanf_s("%d", &amount);
	_knapsack.generate(cap, amount);
}

void experimentWithSingleThread() {
	const int tests = 100;
	const int capacity[] = {40,  80, 120, 160, 200, 240, 280, 320, 360, 400};
	const int nrOfItems[] = {200, 200, 200, 200, 200, 200, 200, 200, 200, 200};
	TimeMeasure timer;				//utility for performance measuring
	KnapsackBnB exKnap;				//new instance for testing
	double time;					//accumulates time

	for (int j = 0; j < sizeof(nrOfItems) / sizeof(int); j++) {
		time = 0.0;
		cout << "Capacity: " << capacity[j] << ", items: " << nrOfItems[j] << endl;
		for (int i = 0; i < tests; i++) {
			exKnap.generate(capacity[j], nrOfItems[j]);
			timer.startTimer();
			exKnap.bNb(true);
			time += timer.stopTimer();
		}
		printf("AVG Time: %.2f [ms] \n\n", time/static_cast<double>(tests));
	}
}

void experimentWithMultipleThreads() {
	const int tests = 100;
	const int capacity[] = { 40, 80, 120, 160, 200, 240, 280, 320, 360, 400 };
	const int nrOfItems[] = { 200, 200, 200, 200, 200, 200, 200, 200, 200, 200 };
	TimeMeasure timer;					//utility for time measuring
	double time = 0.0;
	KnapsackBnB exKnap[sizeof(nrOfItems) / sizeof(int)]; //instances of problem


	cout << "Generating instances of problem..." << endl;
	for (int j = 0; j < sizeof(nrOfItems) / sizeof(int); j++){
		exKnap[j].generate(capacity[j], nrOfItems[j]);
	}
	cout << endl << "All instances were successfully generated. ";
	system("pause");
	cout << "Solving started!" << endl;

	timer.startTimer();
	for (int j = 0; j < sizeof(nrOfItems) / sizeof(int); j++) {
		cout << j << ". Instance. Capacity: " << capacity[j] << ", items: " << nrOfItems[j] << endl;
		new thread(solve, exKnap[j]);
	}
	time = timer.stopTimer();
	printf("\nMULTIPLE THREADS. Overall Time: %.2f [ms] \n\n", time);
}

void solve(KnapsackBnB knap){
	knap.bNb(true);
	return;
}


//*********************************************************
//
//						T R A S H
//
//*********************************************************

// *** My instance of problem ***
// capacity 26
//knapsack.addItem(12, 24);
//knapsack.addItem(7, 13);
//knapsack.addItem(11, 23);
//knapsack.addItem(8, 15);
//knapsack.addItem(9, 16);