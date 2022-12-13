// Solutions for Advent of Code 2022 day 11:
// https://adventofcode.com/2022/day/11

#include <iostream>
#include "troop.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout << "Part 1: " << Troop(argv[1], 20, 3).monkeyBusiness() << endl;
    cout << "Part 2: " << Troop(argv[1], 10000, 1).monkeyBusiness() << endl;
    return 0;
}
