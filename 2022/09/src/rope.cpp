// Implementation of class representing a rope, with knots along its length.

#include <fstream>
#include <iostream>
#include "rope.h"

using namespace std;

// Perform initialisation, read data, and initiate knot movements.
Rope::Rope(string inPath, int nKnot){
    for (int iKnot = 0; iKnot < nKnot; iKnot++) {
        tuple<int, int> knot(0, 0);
        knots.push_back(knot);
    }
    moves = {{"U", make_tuple(0, 1)}, {"D", make_tuple(0, -1)},
        {"L", make_tuple(-1, 0)}, {"R", make_tuple(1, 0)}};        
    updateTailPoints();

    ifstream inFile(inPath);
    string move;
    while (getline(inFile, move)) {
	moveKnots(move);
	}
}

// Move rope knots, based on move instruction.
void Rope::moveKnots(string move) {
    string direction = move.substr(0, 1);
    int nMove = stoi(move.substr(2, move.length() - 2));
    for (int iMove = 0; iMove < nMove; iMove++) {
        moveHead(moves[direction]);
        for (int iKnot = 1; iKnot < knots.size(); iKnot++) {
            moveTrailing(iKnot);
        }
        updateTailPoints();
    }
}

// Move head knot by one step.
void Rope::moveHead(tuple<int, int> dxy) {
    get<0>(knots[0]) += get<0>(dxy);
    get<1>(knots[0]) += get<1>(dxy);
}

// Move knot to keep pace with the knot ahead.
void Rope::moveTrailing(int iKnot) {
    int dx = get<0>(knots[iKnot - 1]) - get<0>(knots[iKnot]);
    int dy = get<1>(knots[iKnot - 1]) - get<1>(knots[iKnot]);

    if (abs(dx) == 2 || abs(dy) == 2) {
        get<0>(knots[iKnot]) += (dx > 0) - (dx < 0);
        get<1>(knots[iKnot]) += (dy > 0) - (dy < 0);
    }
}

// Update record of points visited by tail.
void Rope::updateTailPoints() {
    if (tailPoints.find(get<0>(knots.back())) == tailPoints.end()) {
        set<int> newSet;
        tailPoints[get<0>(knots.back())] = newSet;
    }
    tailPoints[get<0>(knots.back())].insert(get<1>(knots.back()));
}

// Count number of points visited by tail.
int Rope::tailPointCount() {
    int nPoint = 0;
    for (auto item : tailPoints) {
        nPoint += item.second.size();
    }
    return nPoint;
}