#ifndef FILE_H
#define FILE_H

#include <filesystem>

class File {
    private:
        std::filesystem::path path;
        int size;
    public:
        int getSize();
        std::filesystem::path getPath();
        File(std::filesystem::path pathValue, int sizeValue);
};

#endif