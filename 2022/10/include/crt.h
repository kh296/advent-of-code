#ifndef CRT_H
#define CRT_H

#include <string>
#include <vector>

using namespace std;

class CRT{
    private:
    vector<int> cycles;
    int xRegister;
    const int lineLength = 40;
    public:
    CRT(string);
    void applyInstruction(string);
    int signalStrength(int);
    int summedSignalStrengths();
    string renderImage();
};

#endif
