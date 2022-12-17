#include "utils.h"

// Split string at each occurrence of another string.
// Return vector of strings representing the result.
std::vector<std::string> splitString(std::string str, std::string delimiter) {
    std::vector<std::string> elements;
    std::string element;
    std::size_t posStart = 0;
    std::size_t posEnd = 0;
    while ((posEnd = str.find(delimiter, posStart)) != std::string::npos) {
	    element = str.substr(posStart, posEnd - posStart);
	    posStart = posEnd + delimiter.length();
	    elements.push_back(element);
    }
    elements.push_back(str.substr(posStart));
    return elements;
}
