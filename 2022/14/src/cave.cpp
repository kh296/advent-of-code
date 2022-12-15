// Implementation of class representing a cave.

#include <algorithm>
#include <fstream>
#include <iostream>
#include "cave.h"
#include "utils.h"

using namespace std;

// Read data, and simulate cave filling with sand.
Cave::Cave(string path_, int ddx_, int ddy_, bool floor_, bool showMap_) {
    x0 = 500;
    y0 = 0;
    ifstream inFile(path_);
    string line;
    while (getline(inFile, line)) {
	inLines.push_back(line);
    }
    getLimits(ddx_, ddy_);
    createMap(floor_);
    dropSand();
    if (showMap_) {
        showMap();
    }
}

// Determine cave limits from input data.
// Optionally extend by ddx to left and right, and by ddy at bottom.
void Cave::getLimits(int ddx, int ddy) {
    int idx;
    vector<string> elements;
    vector<string> xy;
    for (idx = 0; idx < 2; idx++) {
        xlims[idx] = x0;
	ylims[idx] = y0;
    }
    for (auto line : inLines) {
	elements = splitString(line, delim1);
	for (idx = 0; idx < elements.size(); idx++) {
	    xy = splitString(elements[idx], delim2);
            xlims[0] = min(stoi(xy[0]), xlims[0]);
            xlims[1] = max(stoi(xy[0]), xlims[1]);
            ylims[0] = min(stoi(xy[1]), ylims[0]);
            ylims[1] = max(stoi(xy[1]), ylims[1]);
	}
    }
    xlims[0] -= ddx;
    xlims[1] += ddx;
    ylims[1] += ddy;
    dx = 1 + xlims[1] - xlims[0];
    dy = 1 + ylims[1] - ylims[0];
}

// Map from cave x-coordinate and array column number.
int Cave::getCol(int x) {
    return (x - xlims[0]);
}

// Map from cave y-coordinate and array row number.
int Cave::getRow(int y) {
    return (y - ylims[0]);
}

// Create 2D map of cave, from information on rock structures.
void Cave::createMap(bool floor) {
    string row(dx, '.');
    for (int y = ylims[0]; y <= ylims[1]; y++) {
	cells.push_back(row);
    }
    if (floor) {
        string floorRow(dx, '#');
	cells[ylims[1]] = floorRow;
    }
    cells[getRow(y0)][getCol(x0)] = '+';

    int idx1;
    int idx2;
    vector<string> elements;
    vector<string> xy;
    int cols[2];
    int rows[2];
    for (auto line : inLines) {
	elements = splitString(line, delim1);
	for (idx1 = 0; idx1 < elements.size() - 1; idx1++) {
	    for (idx2 = 0; idx2 < 2; idx2++) {
                xy = splitString(elements[idx1 + idx2], delim2);
		cols[idx2] = getCol(stoi(xy[0]));
		rows[idx2] = getRow(stoi(xy[1]));
	    }

	    if (cols[0] > cols[1]) {swap(cols[0], cols[1]);}
	    if (rows[0] > rows[1]) {swap(rows[0], rows[1]);}

	    for (int row = rows[0]; row <= rows[1]; row++) {
		for (int col = cols[0]; col <= cols[1]; col++) {
		    cells[row][col] = '#';
		}
	    }
	}
    }
}

// Display map of cave.
void Cave::showMap() {
    for (auto row : cells) {
        cout << row << endl;
    }
}

// Determine rest locations of sand dropped from source.
void Cave::dropSand() {
    int row;
    int col;
    bool inScope = true;
    bool tracking;
    while (inScope) {
        row = getRow(y0);
        col = getCol(x0);
	tracking = true;
        while (tracking) {
	    if (cells[row + 1][col] == '.') {
		row++;
            }
	    else if (col - 1 < 0) {
		tracking = false;
		inScope = false;
		break;
            }
	    else if (cells[row + 1][col - 1] == '.') {
		row++;
		col--;
	    }  
	    else if (col + 1 >= dx) {
		tracking = false;
		inScope = false;
		break;
            }
	    else if (cells[row + 1][col + 1] == '.') {
		row++;
		col++;
	    }  
	    else if (cells[row + 1][col] != '.') {
		if (cells[row][col] == '+') {
		    inScope = false;
		}
                cells[row][col] = 'o';
		tracking = false;
            }
	}
    }
}

// Determine number of units of sand in cave, once equilibrium is reached.
int Cave::unitsOfSand() {
    int n = 0;
    for (auto cell : cells) {
        n += count(cell.begin(), cell.end(), 'o');
    }
    return n;
}
