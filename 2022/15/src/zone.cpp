// Implementation of class representing a cave.

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include "zone.h"

using namespace std;

// Read data, and define sensors.
Zone::Zone(string path_) {
    ifstream inFile(path_);
    string line;
    while (getline(inFile, line)) {
	    addSensor(line);
    }
}

// Add to vector of sensors.
// Each sensor has information about its own coordinates,
// and the coordinates of the detected beacon.
void Zone::addSensor(string line) {
    for (auto delimiter : delimiters) {
	line.erase(remove(line.begin(), line.end(), delimiter), line.end());
    }
    vector<string> elements = splitString(line, " ");
    int x1 = stoi(elements[2]);
    int y1 = stoi(elements[3]);
    int x2 = stoi(elements[8]);
    int y2 = stoi(elements[9]);

    Sensor* sensor = new Sensor(x1, y1, x2, y2);
    sensors.push_back(sensor);
}

// Set information on excluded intervals and detected beacons for row y.
// If xMin and xMax aren't equal, consider only the region that they delimit
// (end points included).
void Zone::setIntervalsAndBeacons(int y, int xMin, int xMax) {
    beacons.clear();
    intervals.clear();
    int dx, dy;
    int idxMin, idxMax;
    for (auto sensor : sensors) {
        if (sensor->getYb() == y) {beacons.insert(sensor->getXb());}	
	dy = abs(y - sensor->getYs());
	dx = sensor->getDxy() - dy;
	if (dx >= 0) {
	    idxMin = (xMin == xMax) ?
                sensor->getXs() - dx : max(xMin, sensor->getXs() - dx);
	    idxMax = (xMin == xMax) ?
                sensor->getXs() + dx : min(xMax, sensor->getXs() + dx);
	    intervals.push_back(Interval({idxMin, idxMax}));
	}
    }
    mergeIntervals(intervals);
}

// Determine number of excluded positions for row y.
int Zone::positionsExcluded(int y) {
    setIntervalsAndBeacons(y, 0, 0);
    int excluded = 0;
    for (auto interval : intervals) {
	    excluded += (1 + interval.end - interval.start);
    }
    return excluded - beacons.size();
}

// Determine tuning frequency corresonding to first non-excluded position.
long Zone::tuningFrequency(int dxy) {
    int x, y;
    for (y = 0; y <= dxy; y++) {
        setIntervalsAndBeacons(y, 0, dxy);    
	if (intervals[0].end != dxy) {break;}
    }
    x = intervals[0].end + 1;
    return (4000000 * (long) x + y);
}
