// Implementation of class representing a valve.

#include "valve.h"

// Initialise with id, flow rate, and bit for keeping track of whether visited.
Valve::Valve(std::string id_, int flowRate_, int bit_) {
    id = id_;
    flowRate = flowRate_;
    bit = (bit_ >= 0) ? 1 << bit_ : -1;
}

// Enable streaming of valve objects.
std::ostream & operator << (std::ostream &out, const Valve &valve)
{
    out << valve.id << ": flowRate=" << valve.flowRate
        << "; bit=" << valve.bit;
    for (auto distance : valve.distances) {
        out << "; " << distance.first << ":" << distance.second;
    }
    return out;
}
