// Solutions for Advent of Code 2022 day 04
// https://adventofcode.com/2022/day/4

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Split string at each occurrence of a given character.
// Return vector of strings representing the result.
vector<string> splitString(string str, char delimiter) { 
    vector<string> elements;
    string element = "";

    for (auto chr : str) {
        if (chr == delimiter) {
            elements.push_back(element);
            element = "";
        }
        else {
            element += chr;
        }
    }

    if (element != "") {
        elements.push_back(element);
    }
        return elements;
};

// Represent assignment covering section from sectionMin to sectionMax.
class Assignment {
    public:
    int sectionMin;
    int sectionMax;

    Assignment(string range) {
        vector<string> limits = splitString(range, '-');
        sectionMin = stoi(limits[0]);
        sectionMax = stoi(limits[1]);
    }

    // Determine if this assignment fully contains other assignment.
    bool contains(Assignment other) {
        return (sectionMin <= other.sectionMin && sectionMax >= other.sectionMax);
    }

    // Determine if this assignment overlaps with other assignment.
    bool overlaps(Assignment other) {
        return ((sectionMin >= other.sectionMin && sectionMin <= other.sectionMax)
            || (sectionMax >= other.sectionMin && sectionMax <= other.sectionMax)
            || (other.sectionMin >= sectionMin && other.sectionMin <= sectionMax)
            || (other.sectionMax >= sectionMin && other.sectionMax <= sectionMax));
    }
};

// Read data for assignment pairs.
// Part 1: count the number of times that an assignment of a pair fully contains the other.
// Part 2: count the number of times that paired assignments overlap.
class AssignmentChecker {
    public:
    int contained = 0;
    int overlap = 0;
    AssignmentChecker(string path) {
        string line;
        ifstream inFile(path);

        while (getline (inFile, line)) {
            vector<string> ranges = splitString(line, ',');
            Assignment assignment1 = Assignment(ranges[0]);
            Assignment assignment2 = Assignment(ranges[1]);
            contained += (assignment1.contains(assignment2) || assignment2.contains(assignment1));
            overlap += (assignment1.overlaps(assignment2));
        }

        inFile.close();
    }
};

int main(int argc, char *argv[])
{
    string path;
    if (argc > 1) {
        path = argv[1];
    }
    else {
        path = "example.txt";
    }

    AssignmentChecker assignmentChecker = AssignmentChecker(path);
    std::cout << "Contained: " << assignmentChecker.contained << endl;
    std::cout << "Overlap: " << assignmentChecker.overlap << endl;

    return 0;
};