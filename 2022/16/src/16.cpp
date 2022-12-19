// Solutions for Advent of Code 2022 day 16:
// https://adventofcode.com/2022/day/16

#include <iostream>
#include <string>
#include "network.h"

int main(int argc, char *argv[])
{
    Network network = Network(argv[1]);
    std::cout << "Part 1: " << network.maxPressureRelease1("AA", 30)
        << std::endl;
    std::cout << "Part 2: " << network.maxPressureRelease2("AA", 26)
        << std::endl;
    return 0;
}
