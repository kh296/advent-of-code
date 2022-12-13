// Implementation of class representing a monkey.
#include <iostream>
#include "monkey.h"
#include "utils.h"

using namespace std;

// Parse inputs to define properties.
Monkey::Monkey(long int inId, vector<string> lines){
    id = inId;
    itemsInspected = 0;
    vector<string> elements;
    elements = splitString(lines[0], ' ');
    for (long int idx = 4; idx < elements.size(); idx++) {
        addItem(stoi(elements[idx]));
    }
    elements = splitString(lines[1], ' ');
    opSymbol = elements[6];
    opInt = 0;
    if ("old" != elements[7]) {opInt = stoi(elements[7]);}
    elements = splitString(lines[3], ' ');
    divisor = stoi(splitString(lines[2], ' ')[5]);
    testTrue = stoi(splitString(lines[3], ' ')[9]);
    testFalse = stoi(splitString(lines[4], ' ')[9]);
}

// Add to the items held.
void Monkey::addItem(long int item) {
    items.push(item);
}

// Return number of items inspected.
long int Monkey::getActivity() {
    return itemsInspected;
}

// Return monkey's id.
long int Monkey::getId() {
    return id;
}

// Return divisor used in determing action following item inspection.
long int Monkey::getDivisor() {
    return divisor;
}

// Inspect item, and pass on to another monkey,
// adjusting item value to reflect worry level.
void Monkey::inspectAndDistribute(vector<Monkey*> &monkies, long int &destressFactor, long int &lcm) {
    long int item;
    while (!items.empty()) {
        item = items.front();
        long int val = (opInt == 0) ? item : opInt;
        item = (opSymbol == "+") ? item + val : item * val;
	// To avoid item value becoming exceeding long int
	// in case where destressFactor is 1,
	// replace item value by remainder after dividing by
	// lowest common multiple of divisors.
	// This gives a smaller number, with remainder from
	// division by divisors unchanged.
        item = (1 == destressFactor) ? (item % lcm) : (item / destressFactor);
        long int otherId = (item % divisor == 0) ? testTrue : testFalse;
        monkies[otherId]->addItem(item);
        items.pop();
        itemsInspected++;
    }
}
