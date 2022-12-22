// Solutions for Advent of Code 2022 day 20:
// https://adventofcode.com/2022/day/20

#include <iostream>
#include <string>
#include "decrypter.h"

int main(int argc, char *argv[])
{
    Decrypter decrypter = Decrypter(argv[1]);
    int key = 811589153;
    std::cout << "Part 1: " << decrypter.getCoordinates(1, 1) << std::endl;
    std::cout << "Part 2: " << decrypter.getCoordinates(10, key) << std::endl;
    return 0;
}
