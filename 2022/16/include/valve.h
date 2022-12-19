#ifndef VALVE_H
#define VALVE_H

#include <iostream>
#include <map>
#include <string>

class Valve {
    private:
    std::string id;
    int flowRate;
    int bit;
    std::map<std::string, int> distances;

    public:
    Valve(std::string, int, int);

    friend std::ostream & operator << (std::ostream &out, const Valve &);
    friend class Network;
};

#endif
