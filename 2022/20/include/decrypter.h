#ifndef DECRYPTER_H
#define DECRYPTER_H

#include <string>
#include <vector>

class Decrypter {
    private:
    std::vector<long> numbers;
    public:
    Decrypter(std::string);
    std::vector<long> mix(int, long);
    long getCoordinates(int, int);
};

#endif
