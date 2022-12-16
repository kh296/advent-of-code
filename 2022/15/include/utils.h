#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

using namespace std;

vector<string> splitString(string, string);

struct Interval {int start, end;};
 
bool intervalCompare(Interval, Interval);

void mergeIntervals(vector<Interval> &);
#endif
