#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <queue>
#include <string>
#include <vector>
#include <unordered_set>
#include "point.h"

using namespace std;

class PathFinder {
    private:
    vector<vector<Point*>> terrain;
    Point* startPoint;
    Point* endPoint;
    queue<Point*> pointsToCheck;
    unordered_set<Point*> pointsVisited;
    vector<Point*> lowPoints;
    int maxRow;
    int maxCol;
    public:
    PathFinder(string);
    void definePaths();
    int stepsFromPoint(Point*);
    int stepsFromStart();
    int minStepsFromLowPoints();
};

#endif
