// Solutions for Advent of Code 2022 day 18:
// https://adventofcode.com/2022/day/18

#include <iostream>
#include <string>
#include "droplet.h"

int main(int argc, char *argv[])
{
    Droplet droplet = Droplet(argv[1]);
    std::cout << "Part 1: " << droplet.surfaceArea() << std::endl;
    std::cout << "Part 2: " << droplet.externalSurfaceArea() << std::endl;
    return 0;
}
