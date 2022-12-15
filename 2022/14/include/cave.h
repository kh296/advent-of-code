#ifndef CAVE_H
#define CAVE_H

#include <string>
#include <vector>

using namespace std;

class Cave {
    private:
    const string delim1 = " -> ";
    const string delim2 = ",";
    int x0;
    int y0;
    int xlims[2];
    int ylims[2];
    vector<string> inLines;
    vector<string> cells;
    int dx;
    int dy;
    public:
    Cave(string, int, int, bool, bool);
    void getLimits(int, int);
    void createMap(bool);
    void showMap();
    int getCol(int);
    int getRow(int);
    void dropSand();
    int unitsOfSand();
};

#endif
