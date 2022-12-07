#include <string>
#include <vector>
#include "utils.h"

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