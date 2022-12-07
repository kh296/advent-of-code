// Implementation of class representing a directory.

#include <filesystem>
#include "directory.h"
#include "file.h"

using namespace std;

Directory::Directory(std::filesystem::path pathValue) {
    path = pathValue;
}

void Directory::addFile(File* file) {files.push_back(file);}

void Directory::addSubdir(Directory* subdir) {subdirs.push_back(subdir);}

std::filesystem::path Directory::getPath() {return path;}

int Directory::getSize(){
    int size = 0;
    for (auto file : files) {
        size += file->getSize();
    }
        for (auto subdir : subdirs) {
        size += subdir->getSize();
    }
    return size;
}
