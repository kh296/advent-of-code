// Solutions for Advent of Code 2022 day 13:
// https://adventofcode.com/2022/day/13

#include <iostream>
#include "communicator.h"

int main(int argc, char *argv[])
{
    Communicator communicator = Communicator(argv[1]);
    std::cout << "Part 1: " << communicator.rightOrder() << std::endl;
    std::cout << "Part 2: " << communicator.decoderKey() << std::endl;
    return 0;
}
