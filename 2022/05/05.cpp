// Solutions for Advent of Code 2022 day 05:
// https://adventofcode.com/2022/day/5

#include <fstream>
#include <iostream>
#include <map>
#include <stack>
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
}

class Cargo {
    private:
    vector<stack<char>> stacks;
    char cargoIdentifier = '[';
    char moveIdentifier = 'm';

    public:
    string top = "";

    void addCrates(string line){
        if (line.find(cargoIdentifier) == string::npos) return;
        for (int idx1=0; 4 * idx1 < line.length(); idx1++) {
            if (idx1 == stacks.size()){
                stack<char> newStack;
                stacks.push_back(newStack);
            }

            int idx2 = 4 * idx1 + 1;
            char crate = line[idx2];
            if (' ' != crate) {
                stacks[idx1].push(crate);
            }
        }
    }

    void reverseStacks() {
        for(int idx = 0 ; idx < stacks.size(); idx++) {
            if (!stacks[idx].empty()) {
                stack<char> stk;
                while (!stacks[idx].empty()) {
                    stk.push(stacks[idx].top());
                    stacks[idx].pop();
                }
                stacks[idx] = stk;
            }
        }
    }

    void moveCrates(string line, int crateMover=9000) {
        if (line.find(moveIdentifier) == string::npos) return;
        stack<char> stk;
        vector<string> elements = splitString(line, ' ');
        int nCrate = stoi(elements[1]);
        int idx1 = stoi(elements[3]) - 1;
        int idx2 = stoi(elements[5]) - 1;

        for (int iCrate=1; iCrate <= nCrate; iCrate++) {
            if (9000 == crateMover) {
                stacks[idx2].push(stacks[idx1].top());
            }
            else if (9001 == crateMover) {
                stk.push(stacks[idx1].top());
            }
            stacks[idx1].pop();
        }

        if (9001 == crateMover) {
            while (!stk.empty()) {
                stacks[idx2].push(stk.top());
                stk.pop();
            }
        }
    }

    string getTopCrates() {
        string topCrates = "";
        for(int idx = 0 ; idx < stacks.size(); idx++) {
            topCrates += stacks[idx].top();
        }
        return topCrates;
    }

    Cargo(string path, int crateMover=9000) {
        string line = "[";
        ifstream inFile(path);

        while (line.find(cargoIdentifier) != string::npos) {
            getline (inFile, line);
            addCrates(line);
        }
        reverseStacks();

        while (getline (inFile, line)) {
            moveCrates(line, crateMover);
        }

        inFile.close();

    top = getTopCrates();
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

    std::cout << "Top 1: " << Cargo(path, 9000).top << endl;
    std::cout << "Top 2: " << Cargo(path, 9001).top << endl;

    return 0;
}