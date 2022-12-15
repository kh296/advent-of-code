#include "utils.h"

// Split string at each occurrence of another string.
// Return vector of strings representing the result.
vector<string> splitString(string str, string delimiter) {
    vector<string> elements;
    string element;
    size_t posStart = 0;
    size_t posEnd = 0;
    while ((posEnd = str.find(delimiter, posStart)) != string::npos) {
	    element = str.substr(posStart, posEnd - posStart);
	    posStart = posEnd + delimiter.length();
	    elements.push_back(element);
    }
    elements.push_back(str.substr(posStart));
    return elements;
}
