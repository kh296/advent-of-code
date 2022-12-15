// Solutions for Advent of Code 2022 day 14:
// https://adventofcode.com/2022/day/14

#include <iostream>
#include "cave.h"

using namespace std;

int main(int argc, char *argv[])
{
    int part1 = Cave(argv[1], 0, 0, false, false).unitsOfSand();
    cout << "Part 1: " << part1 << endl;
    int part2 = Cave(argv[1], 200, 2, true, false).unitsOfSand();
    cout << "Part 2: " << part2 << endl;
    return 0;
}
