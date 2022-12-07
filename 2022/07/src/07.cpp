// Solutions for Advent of Code 2022 day 07:
// https://adventofcode.com/2022/day/7

#include <iostream>
#include "explorer.h"

using namespace std;

int main(int argc, char *argv[])
{
    string path;
    if (argc > 1) {
        path = argv[1];
    }
    else {
        path = "example.txt";
    }

    Explorer explorer = Explorer(path);
    cout << "Part 1: " << explorer.getSizeSum(100000) << endl;
    cout << "Part 2: " << explorer.getDeleteSize(70000000, 30000000) << endl;

    return 0;
}
