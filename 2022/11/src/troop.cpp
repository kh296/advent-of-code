// Implementation of class representing a troop of monkeys.

#include <algorithm>
#include <fstream>
#include <iostream>
#include "troop.h"

using namespace std;

// Read data, and use to define monkeys in troop.
Troop::Troop(string path_, long int nRound_, long int destressFactor_) {
    ifstream inFile(path_);
    string line;
    long int id = 0;
    nRound = nRound_;
    destressFactor = destressFactor_;
    divisorsLCM = 1;
    while (getline(inFile, line)) {
        if (line.find("Monkey") != string::npos) {
            vector<string> lines;
            for (long int idx = 0; idx < 5; idx++) {
                getline(inFile,line);
                lines.push_back(line);
            }
            Monkey* monkey = new Monkey(id, lines);
            monkies.push_back(monkey);
            // Take advantage of fact that divisors in puzzle data
            // are all prime numbers.
            divisorsLCM *= monkey->getDivisor();
            id++;
        }
	}
    completeRounds();
}

// Complete round, in which each monkey pass on items to others.
void Troop::completeRounds() {
    for (long int iRound = 0; iRound < nRound; iRound++) {
        //cout << "Round " << (iRound + 1) << endl;
        for (auto monkey : monkies) {
            monkey->inspectAndDistribute(monkies, destressFactor, divisorsLCM);
        }
    }
}

// Calculate level of monkey business as product of numbers of items
// inspected by two most-active monkeys.
long int Troop::monkeyBusiness() {
    vector<long int> activities;
    for (auto monkey : monkies) {
        activities.push_back(monkey->getActivity());
    }
    if (activities.size() >= 2){
        sort(activities.begin(), activities.end(), greater<long int>());
        return (activities[0] * activities[1]);
    }
    return 0;
}
