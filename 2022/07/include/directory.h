#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <filesystem>
#include <vector>
#include "file.h"

using namespace std;

class Directory {
    private:
    std::filesystem::path path;
    vector<File*> files;
    vector<Directory*> subdirs;

    public:
    Directory(std::filesystem::path pathValue);
    void addFile(File* file);
    void addSubdir(Directory* subdir);
    int getSize();
    std::filesystem::path getPath();
};

#endif