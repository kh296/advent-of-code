#ifndef MONKEY_H
#define MONKEY_H

#include <queue>
#include <string>
#include <vector>

using namespace std;

class Monkey{
    private:
    long int id;
    queue<long int> items;
    string opSymbol;
    long int opInt;
    long int divisor;
    long int testTrue;
    long int testFalse;
    long int itemsInspected;
    public:
    Monkey(long int, vector<string>);
    void addItem(long int);
    long int getActivity();
    long int getId();
    long int getDivisor();
    void inspectAndDistribute(vector<Monkey*>&, long int&, long int&);
};

#endif
