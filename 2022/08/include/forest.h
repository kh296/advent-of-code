#ifndef FOREST_H
#define FOREST_H

#include <string>
#include <vector>

using namespace std;

class Forest{
    private:
    vector<vector<int>> trees;
    int nRow;
    int nCol;
    public:
    Forest(string inPath);
    int getVisibleTreeCount();
    int isVisible(int iRow, int iCol);
    int isVisibleOneDirection(
        int iRow, int iCol, int jRow1, int jRow2, int jCol1, int jCol2);
    int getMaxScenicScore();
    int getScenicScore(int iRow, int iCol);
    int getViewingDistance(
        int iRow, int iCol, int jRow1, int jRow2, int jCol1, int jCol2);
};

#endif
