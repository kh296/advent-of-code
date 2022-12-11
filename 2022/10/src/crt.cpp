// Implementation of class representing a video display
// based around a cathode-ray tube (CRT.)

#include <fstream>
#include <iostream>
#include "crt.h"

using namespace std;

// Read and apply instructions relative to CRT operation.
CRT::CRT(string inPath){
    xRegister = 1;
    ifstream inFile(inPath);
    string instruction;
    while (getline(inFile, instruction)) {
        applyInstruction(instruction);
	}
}

// Apply a single instruction.
void CRT::applyInstruction(string instruction) {
    int nCycle = 1;
    int dx = 0;
    string command = instruction.substr(0, 4);

    if ("addx" == command) {
        nCycle = 2;
	dx = stoi(instruction.substr(5, instruction.length() - 4));
    }

    for (int iCycle=0; iCycle < nCycle; iCycle++) {
        cycles.push_back(xRegister);
    }
    xRegister += dx;
}

// Return signal strength for a specified cycle.
int CRT::signalStrength(int cycle) {
    return cycle * cycles[cycle - 1];
}

// Sum signal strengths over subset of cycles.
int CRT::summedSignalStrengths() {
    const int cycle1 = 20;
    const int delta = 40;
    int total = 0;
    for (int cycle = cycle1; cycle < cycles.size(); cycle += delta) {
        total += signalStrength(cycle);
    }
    return total;
}

// Return string representing lit (#) and unlit (.) image pixels.
string CRT::renderImage() {
    string image = "\n";
    int col = 0;
    for (int iCycle = 0; iCycle < cycles.size(); iCycle++) {
	image += (abs(cycles[iCycle] - col) <= 1) ? "#" : ".";
	if (0 == (iCycle + 1) % lineLength) {
		image += "\n";
		col = 0;
	}
	else {
	    col++;
	}
    }
    return image;
}