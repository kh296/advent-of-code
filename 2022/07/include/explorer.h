#ifndef EXPLORER_H
#define EXPLORER_H

#include <filesystem>
#include <map>
#include <string>
#include <vector>
#include "directory.h"

using namespace std;

class Explorer{
    private:
    std::filesystem::path currentPath;
    map<std::filesystem::path, Directory*> directories;
    public:
    Explorer(string inPath);
    void cd(string newDir);
    void parse(string str);
    int getSizeSum(int maxSize);
    int getDeleteSize(int systemSize, int minFreeSpace);
};

#endif
