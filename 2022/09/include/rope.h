#ifndef ROPE_H
#define ROPE_H

#include <map>
#include <string>
#include <set>
#include <tuple>
#include <vector>

using namespace std;

class Rope{
    private:
    vector<tuple<int, int>> knots;
    map<string, tuple<int, int>> moves;
    map<int, set<int>> tailPoints;
    public:
    Rope(string, int);
    void moveKnots(string);
    void moveHead(tuple<int, int>);
    void moveTrailing(int); 
    void updateTailPoints();
    int tailPointCount();
};

#endif