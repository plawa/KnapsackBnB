
// ***********************************
//
//		Author: Piotr £awniczak
//		 www.piotrlawniczak.eu
//
// ***********************************

#include "stdafx.h"
#include "KnapsackBnB.h"
#include <thread>

#define INFO "\n ********************************************\n\n"\
			"  Branch & Bound solver of knapsack problem\n\n"\
			"  \tAuthor: www.piotrlawniczak.eu\n\n"\
			" ********************************************\n\n"
#define MENU " 1. Add items (and initialize knapsack if not already)\n"\
			" 2. Generate an instance of problem - for validation purposes\n"\
			" 3. Solve problem - Branch & Bound algorithm\n"\
			" 4. Solve problem - Brute Force\n"\
			" 5. Generate many instances for experiment\n"\
			" 6. Run experiment - B&B Single Thread\n"\
			" 7. Run experiment - B&B Multiple Threads\n"\
			" 8. Run experiment - Brute Force (Single Thread)\n"\
			" 0. Exit\n\n "
void addItem(KnapsackBnB& _knapsack);
void generateInstance(KnapsackBnB& _knapsack);
void generateForExperiment();
void experimentWithSingleThread();
void experimentWithMultipleThreads();
void experimentBruteForce();
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
		} while (choice > 8);
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
			knapsack.bruteForce();
			break;
		case 5:
			generateForExperiment();
			break;
		case 6:
			experimentWithSingleThread();
			break;
		case 7:
			experimentWithMultipleThreads();
			break;
		case 8:
			experimentBruteForce();
			break;
		case 0:
			exit(0);
		default:
			cout << " The number you've chosen does not exist!" << endl;
		}
		fflush(stdin);
	}

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


const int capacity[] = { 140, 180, 110, 100, 120 };
const int nrOfItems[] = { 10, 10, 10, 15, 15 };
const int nrOfInstances = sizeof(nrOfItems) / sizeof(int);
KnapsackBnB exKnap[sizeof(nrOfItems) / sizeof(int)]; //instances of problem
bool generated = false;

void generateForExperiment(){
	cout << " Generating instances of problem..." << endl;
	for (int j = 0; j < sizeof(nrOfItems) / sizeof(int); j++)
		exKnap[j].generate(capacity[j], nrOfItems[j]);
	generated = true;
	cout << endl << " All instances were successfully generated. You can now start an experiment." << endl << endl << " ";
	system("pause");
}

void experimentWithSingleThread() {
	if (!generated) {
		cout << " Error. First you have to generate instances for experiment!" << endl << endl;
		return;
	}
	TimeMeasure timer;					//utility for time measuring
	double time = 0.0;

	cout << " Solving started!" << endl;
	timer.startTimer();
	for (int j = 0; j < nrOfInstances; j++)
		solve(exKnap[j]);
	time = timer.stopTimer();
	printf("\n SINGLE THREAD. Overall Time: %.2f [ms] \n\n", time);
}

void experimentWithMultipleThreads() {
	if (!generated) {
		cout << " Error. You have to generate instances for experiment at first!" << endl << endl;
		return;
	}
	TimeMeasure timer;				   //utility for time measuring
	double time = 0.0;
	thread watki[nrOfInstances];

	cout << " Solving started!" << endl;
	timer.startTimer();

	for (int i = 0; i < nrOfInstances; i++)
		watki[i] = thread(solve, exKnap[i]);

	for (int i = 0; i < nrOfInstances; i++)
		watki[i].join();

	time = timer.stopTimer();
	printf("\n MULTIPLE THREADS. Overall Time: %.2f [ms] \n\n", time);
}

void experimentBruteForce() {
	if (!generated) {
		cout << " Error. You have to generate instances for experiment at first!" << endl << endl;
		return;
	}
	TimeMeasure timer;				   //utility for time measuring
	double time = 0.0;

	cout << " Solving started!" << endl;
	timer.startTimer();

	for (int i = 0; i < nrOfInstances; i++)
		exKnap[i].bruteForce(true);

	time = timer.stopTimer();
	printf("\n BRUTE FORCE (SINGLE THREAD). Overall Time: %.2f [ms] \n\n", time);
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