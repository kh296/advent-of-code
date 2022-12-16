#include "utils.h"

// Split string at each occurrence of another string.
// Return vector of strings representing the result.
vector<string> splitString(string str, string delimiter)
{
    vector<string> elements;
    string element;
    size_t posStart = 0;
    size_t posEnd = 0;
    while ((posEnd = str.find(delimiter, posStart)) != string::npos) {
	    element = str.substr(posStart, posEnd - posStart);
	    posStart = posEnd + delimiter.length();
	    elements.push_back(element);
    }
    elements.push_back(str.substr(posStart));
    return elements;
}

// Test whether Interval int1 has start value smaller than Interval int2.
bool intervalCompare(Interval int1, Interval int2) {
    return int1.start < int2.start;}

// Given vector of Interval objects,
// merge in place to vector of non-overlapping intervals.
void mergeIntervals(vector<Interval> & intervals)
{
    sort(intervals.begin(), intervals.end(), intervalCompare);

    int idx1 = 0;
    for (int idx2 = 1; idx2 < intervals.size(); idx2++) {
        if (intervals[idx1].end >= intervals[idx2].start) {
	    intervals[idx1].end = max(intervals[idx1].end, intervals[idx2].end);
        }
	else {
	    idx1++;
	    intervals[idx1] = intervals[idx2];
	}
    }

    intervals.erase(intervals.begin() + idx1 + 1, intervals.end());
}
