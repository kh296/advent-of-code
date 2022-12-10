// Solutions for Advent of Code 2022 day 09:
// https://adventofcode.com/2022/day/9

#include <iostream>
#include "rope.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout << "Part 1: " << Rope(argv[1], 2).tailPointCount() << endl;
    cout << "Part 2: " << Rope(argv[1], 10).tailPointCount() << endl;
    return 0;
}
