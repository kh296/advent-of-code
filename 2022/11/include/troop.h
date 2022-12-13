#ifndef TROOP_H
#define TROOP_H

#include <string>
#include <vector>
#include "monkey.h"

using namespace std;

class Troop{
    private:
    vector<Monkey*> monkies;
    long int nRound;
    long int destressFactor;
    long int divisorsLCM;
    public:
    Troop(string, long int, long int);
    void completeRounds();
    long int monkeyBusiness();
};

#endif
