// Solutions for Advent of Code 2022 day 15:
// https://adventofcode.com/2022/day/15

#include <iostream>
#include <string>
#include "zone.h"

using namespace std;

int main(int argc, char *argv[])
{
    string path = argv[1];
    // Need different parameters for example input and puzzle input.
    int y0 = (path.find("example") != string::npos) ? 10 : 2000000;
    int dxy = (path.find("example") != string::npos) ? 20 : 4000000;

    int part1 = Zone(path).positionsExcluded(y0);
    cout << "Part 1: " << part1 << endl;
    long part2 = Zone(path).tuningFrequency(dxy);
    cout << "Part 2: " << part2 << endl;
    return 0;
}
