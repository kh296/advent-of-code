// Implementation of class representing a file-system explorer.

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "explorer.h"
#include "utils.h"

using namespace std;

Explorer::Explorer(string inPath){
    string line;
    ifstream inFile(inPath);
    currentPath = std::filesystem::path("");
    while (getline(inFile, line)) {
        parse(line);
    }
}

// Set current path following change of directory.
void Explorer::cd(string pathChange) {
    if ('/' == pathChange[0]) {
        currentPath = std::filesystem::path(pathChange);
    }
    else if (".." == pathChange) {
        currentPath = currentPath.parent_path();
    }
    else {
        currentPath.append(pathChange);
    }
}

// Parse line of screen output.
void Explorer::parse(string str) {
    vector<string> elements = splitString(str, ' ');
    if ("$" == elements[0]) {
        if ("cd" == elements[1]) {
            cd(elements[2]);
            if (directories.find(currentPath) == directories.end()) {
                Directory* dir = new Directory(currentPath);
                directories[currentPath] = dir;
                if (currentPath != "/") {
                    directories[currentPath.parent_path()]->addSubdir(dir);
                }
            }
        }
    }
    else if ("dir" != elements[0]) {
        std::filesystem::path filePath = std::filesystem::path(currentPath.c_str());
        filePath.append(elements[1]);
        int fileSize = stoi(elements[0]);
        File* file = new File(filePath, fileSize);
        directories[currentPath]->addFile(file);
    }

}

// Determine sum of sizes for directories with size no greater than maxSize.
int Explorer::getSizeSum(int maxSize) {
    int sizeSum = 0;
    for (auto item : directories) {
        int size = item.second->getSize();
        if (size <= maxSize) {
            sizeSum += size;
        }
    }
    return sizeSum;
}

// Determine smallest size of directory that needs to be deleted,
// given system size and minimum free space required.
int Explorer::getDeleteSize(int systemSize, int minFreeSpace) {
    int minSize = minFreeSpace - (systemSize - directories["/"]->getSize());
    int deleteSize = 0;
    if (minSize > 0) {
        deleteSize = systemSize;
        for (auto item : directories) {
            int size = item.second->getSize();
            if (size >= minSize && size < deleteSize) {
                deleteSize = size;
            }
        }
    }
    return deleteSize;
}
