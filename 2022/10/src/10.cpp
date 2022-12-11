// Solutions for Advent of Code 2022 day 10:
// https://adventofcode.com/2022/day/10

#include <iostream>
#include "crt.h"

using namespace std;

int main(int argc, char *argv[])
{
    CRT crt = CRT(argv[1]);
    cout << "Part 1: " << crt.summedSignalStrengths() << endl;
    cout << "Part 2: " << crt.renderImage() << endl;
    return 0;
}