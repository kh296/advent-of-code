// Solutions for Advent of Code 2022 day 06:
// https://adventofcode.com/2022/day/6

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

// Identify marker having given sequence length in message.
int getMarker(string message, int sequenceLength=4) {
    if (message.length() >= sequenceLength) {
        for (int idx=sequenceLength; idx < message.length(); idx++) {
            unordered_set<char> characters;
            for (auto character : message.substr(
                idx - sequenceLength, sequenceLength)) {
                characters.insert(character);
            }
            if (sequenceLength == characters.size()){
                return idx;
            }
        }
    }
    return -1;
}

// Read message from file at given path.
string getMessage(string path) {
    string message;
    ifstream inFile(path);
    getline(inFile, message);
    return message;
}

int main(int argc, char *argv[])
{
    string path;
    if (argc > 1) {
        path = argv[1];
    }
    else {
        path = "example.txt";
    }

    string message = getMessage(path);
    std::cout << "Start-of-package marker: " << getMarker(message, 4) << endl;
    std::cout << "Start-of-message marker: " << getMarker(message, 14) << endl;

    return 0;
};