// Implementation of class representing pathfinder.

#include <fstream>
#include <iostream>
#include "pathfinder.h"

using namespace std;

// Read data; create map of terrain as array of points;
// identify start point, end point, lowest points;
// define all paths to end point.
PathFinder::PathFinder(string path_) {
    ifstream inFile(path_);
    string line;
    while (getline(inFile, line)) {
	vector<Point*> row;
	int irow = terrain.size();
	for (auto chr : line) {
	    int icol = row.size();
	    // Create and store point with current coordinates.
	    Point* point = new Point(icol, irow, chr);
	    row.push_back(point);

	    // Identify start point.
	    if (chr == 'S') {
		point->setH('a');
	        startPoint = point;
	    }
	    // Identify end point.
	    else if (chr == 'E') {
		point->setH('z');
	        endPoint = point;
	    }

	    // Identify low points (height 'a').
	    if (point->getH() == 'a') {
		lowPoints.push_back(point);
	    }
	}
	terrain.push_back(row);
    }
    maxRow = terrain.size();
    maxCol = terrain.back().size();
    definePaths();
}

// Define paths to end point (based on breadth-first search of points).
void PathFinder::definePaths() {
    pointsToCheck.push(endPoint);
    while (!pointsToCheck.empty()) {
	// Define current point.
	Point* point = pointsToCheck.front();
	pointsVisited.insert(point);
	pointsToCheck.pop();
	int x0 = point->getX();
	int y0 = point->getY();
	// Identify nearest neighbours from which current point can be reached.
	for(int irow = max(0, y0 - 1); irow < min(maxRow, y0 + 2); irow++) {
	    for(int icol = max(0, x0 - 1); icol < min(maxCol, x0 + 2); icol++) {
                if ((irow == y0 && icol == x0) || (irow != y0 && icol != x0)) {
		    continue;}
		Point* point2 = terrain[irow][icol];
		if (pointsVisited.find(point2) != pointsVisited.end()) {
		    continue;}
		if (point->getH() - point2->getH() <= 1) {
		    point2->setPrevious(point);
		    pointsToCheck.push(point2);
		    // Mark point as visited as soon as queued for checking;
		    // this avoids the point being queued multiple times.
		    pointsVisited.insert(point2);
                }
	    }
        }
    }
}

// Calculate the number of steps to reach the end from a specified point.
int PathFinder::stepsFromPoint(Point* point) {
    int nStep = 0;
    bool reachedEnd = true;
    while (point != endPoint) {
	if (point->getPrevious() == nullptr) {
	    reachedEnd = false;
	    break;
	}
        point = point->getPrevious();
	nStep++;
    }
    if (!reachedEnd) {nStep = -1;}
    return nStep;
}

// Calculate the number of steps to reach the end from the start point.
int PathFinder::stepsFromStart() {
    return stepsFromPoint(startPoint);
}

// Calculate the minimum number of steps to reach the end
// from any of the low points.
int PathFinder::minStepsFromLowPoints() {
    int minStep = -1;
    for (auto point : lowPoints) {
        int nStep = stepsFromPoint(point);
	if (-1 != nStep) {
	    if (nStep < minStep || minStep == -1) {
		minStep = nStep;
	    }
	}
    }
    return minStep;
}
