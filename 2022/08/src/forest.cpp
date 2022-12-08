// Implementation of class representing a forest (grid of trees).

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "forest.h"

using namespace std;

// Read data.
Forest::Forest(string inPath){
    string line;
    ifstream inFile(inPath);
    while (getline(inFile, line)) {
        vector<int> rowOfTrees;
        for (auto val : line) {
            rowOfTrees.push_back(atoi(&val));
        }
        trees.push_back(rowOfTrees);
	}
    nRow = trees.size();
    nCol = nRow > 0 ? trees[0].size() : 0;
}

// Calculate number of trees visible from edge of forest.
int Forest::getVisibleTreeCount() {
    int visibleTree = 2 * (nCol + nRow - 2);
    for (int iRow = 1; iRow < nRow - 1; iRow++) {
        for (int iCol = 1; iCol < nCol - 1; iCol++) {            
            visibleTree += isVisible(iRow, iCol);
        }
    }
    return visibleTree;
}

// Determine whether tree at specified row and colum in grid is visible.
int Forest::isVisible(int iRow, int iCol) {
    int visible = isVisibleOneDirection(iRow, iCol, 0, iRow - 1, iCol, iCol);
    if (1 == visible) {return visible;}

    visible = isVisibleOneDirection(iRow, iCol, iRow + 1, nRow - 1, iCol, iCol);
    if (1 == visible) {return visible;}

    visible = isVisibleOneDirection(iRow, iCol, iRow, iRow, 0, iCol - 1);
    if (1 == visible) {return visible;}

    visible = isVisibleOneDirection(iRow, iCol, iRow, iRow, iCol + 1, nCol - 1);
    return visible;
}

// Determine whether tree at specified row and colum in grid is visible
// from an individual direction, delimited by row and column coordinates.
int Forest::isVisibleOneDirection(
    int iRow, int iCol, int jRow1, int jRow2, int jCol1, int jCol2) {
    int visible = 1;
    for (int jRow = jRow1; jRow <= jRow2; jRow++) {
        for (int jCol = jCol1; jCol <= jCol2; jCol++) {
            if (trees[jRow][jCol] >= trees[iRow][iCol]) {
                visible = 0;
                break;
            }
        }
    }
    return visible;
}

// Determine maximum scenic score among trees of forest.
int Forest::getMaxScenicScore() {
    int maxScenicScore = 0;
    for (int iRow = 1; iRow < nRow - 1; iRow++) {
        for (int iCol = 1; iCol < nCol - 1; iCol++) { 
            maxScenicScore = max(maxScenicScore, getScenicScore(iRow, iCol));
        }
    }
    return maxScenicScore;
}

// Determine scenic score (product of viewing distances)
// for tree at specified row and colum in grid
int Forest::getScenicScore(int iRow, int iCol) {
    int scenicScore = 1;
    scenicScore *= getViewingDistance(iRow, iCol, iRow - 1, 0, iCol, iCol);
    if (scenicScore == 0) {return scenicScore;}

    scenicScore *= getViewingDistance(
        iRow, iCol, iRow + 1, nRow - 1, iCol, iCol);
    if (scenicScore == 0) {return scenicScore;}

    scenicScore *= getViewingDistance(iRow, iCol, iRow, iRow, iCol - 1, 0);
    if (scenicScore == 0) {return scenicScore;}

    scenicScore *= getViewingDistance(
        iRow, iCol, iRow, iRow, iCol + 1, nCol - 1);
    return scenicScore;
}

// Determine unobstructed view in an individual direction
// from tree at specified row and colum in grid.
int Forest::getViewingDistance(
    int iRow, int iCol, int jRow1, int jRow2, int jCol1, int jCol2) {
    int jRowDelta = jRow2 >= jRow1 ? 1 : -1;
    int jColDelta = jCol2 >= jCol1 ? 1 : -1;
    int viewingDistance = 0;
    for (int jRow = jRow1; (jRow >= min(jRow1, jRow2)
        && jRow <= max(jRow1, jRow2)); jRow += jRowDelta) {
        for (int jCol = jCol1; (jCol >= min(jCol1, jCol2)
            && jCol <= max(jCol1, jCol2)); jCol += jColDelta) {
            viewingDistance++;
            if (trees[jRow][jCol] >= trees[iRow][iCol]) {
                return viewingDistance;
            }
        }
    }
    return viewingDistance;
}
