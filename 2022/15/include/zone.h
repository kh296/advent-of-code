#ifndef ZONE_H
#define ZONE_H

#include <string>
#include <unordered_set>
#include <vector>
#include "sensor.h"
#include "utils.h"

class Zone {
    private:
    const string delimiters = "xy,:=";
    vector<Sensor*> sensors;
    unordered_set<int> beacons;
    unordered_set<int> exclusions;
    vector<Interval> intervals;
    public:
    Zone(string);
    void addSensor(string);
    void setIntervalsAndBeacons(int, int, int);
    int positionsExcluded(int);
    long tuningFrequency(int);
};

#endif
