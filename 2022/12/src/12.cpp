// Solutions for Advent of Code 2022 day 11:
// https://adventofcode.com/2022/day/11

#include <iostream>
#include "pathfinder.h"

using namespace std;

int main(int argc, char *argv[])
{
    PathFinder pathfinder = PathFinder(argv[1]);
    cout << "Part 1: " << pathfinder.stepsFromStart() << endl;
    cout << "Part 2: " << pathfinder.minStepsFromLowPoints() << endl;
    return 0;
}
