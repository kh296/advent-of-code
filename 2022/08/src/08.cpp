// Solutions for Advent of Code 2022 day 08:
// https://adventofcode.com/2022/day/8

#include <iostream>
#include "forest.h"

using namespace std;

int main(int argc, char *argv[])
{
    Forest forest = Forest(argv[1]);
    cout << "Part 1: " << forest.getVisibleTreeCount() << endl;
    cout << "Part 2: " << forest.getMaxScenicScore() << endl;

    return 0;
}