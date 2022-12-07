// Implementation of class representing a file.

#include <filesystem>
#include "file.h"

File::File(std::filesystem::path pathValue, int sizeValue) {
    path = pathValue;
    size = sizeValue;
}

std::filesystem::path File::getPath() {return path;}

int File::getSize() {return size;};
