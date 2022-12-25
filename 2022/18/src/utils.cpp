#include "utils.h"

// Split std::string at each occurrence of another std::string.
// Return std::vector of std::strings representing the result.
std::vector<std::string> splitString(std::string str, std::string delimiter)
{
    std::vector<std::string> elements;
    std::string element;
    size_t posStart = 0;
    size_t posEnd = 0;
    while ((posEnd = str.find(delimiter, posStart)) != std::string::npos) {
	    element = str.substr(posStart, posEnd - posStart);
	    posStart = posEnd + delimiter.length();
	    elements.push_back(element);
    }
    elements.push_back(str.substr(posStart));
    return elements;
}
