#ifndef NETWORK_H
#define NETWORK_H

#include <map>
#include <string>
#include <vector>
#include "valve.h"

class Network {
    private:
    const std::string delimiters = "=;,";
    const int bigNumber = 10000;
    std::map<std::string, Valve*> valves;
    std::vector<std::string> valveIds;
    std::vector<std::string> pressureValveIds;
    public:
    Network(std::string);
    void addValve(std::string);
    void setDistances();
    void visitValve(std::string, int, int, int, std::map<int, int> &);
    int maxPressureRelease1(std::string, int);
    int maxPressureRelease2(std::string, int);
};

#endif
