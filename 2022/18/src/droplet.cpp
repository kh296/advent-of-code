// Implementation of class representing a droplet.

#include <fstream>
#include <iostream>
#include <stack>
#include "droplet.h"
#include "utils.h"

// Read and store centroid coordinates of cubes forming (voxelised) droplet.
Droplet::Droplet(std::string path_) {
    std::ifstream inFile(path_);
    std::string line;
    while (getline(inFile, line)) {
	std::vector<std::string> elements = splitString(line, ",");
	std::vector<int> cube = {
		stoi(elements[0]), stoi(elements[1]), stoi(elements[2])};
	// Store coordinates in vector for use in loops.
	cubes.push_back(cube);
	// Store coordinates in map for identification of neighbours.
	coordinates[cube[0]][cube[1]][cube[2]] = true;
    }
    setLimits();
}

// Calculate surface area: loop over cubes, and add 1 for each
// surface with a neighbour that is lava.
int Droplet::surfaceArea() {
    int area = 0;
    for (auto cube : cubes) {
	for (auto neighbour : getNeighbours(cube)) {
            area += 1 - isLava(neighbour);
	}
    }
    return area;
}

// Test whether a cube is lava.
int Droplet::isLava(std::vector<int> cube) {
    int lava= 0;
    try {
        coordinates.at(cube[0]).at(cube[1]).at(cube[2]);
        lava= 1;
    }
    catch (std::out_of_range exception) {
    }
    return lava;
}

// Identify the six cubes in contact with the surfaces of the input cube.
std::vector<std::vector<int>> Droplet::getNeighbours(std::vector<int> cube) {
    std::vector<std::vector<int>> neighbours {
        {cube[0] - 1, cube[1], cube[2]},
        {cube[0] + 1, cube[1], cube[2]},
        {cube[0], cube[1] - 1, cube[2]},
        {cube[0], cube[1] + 1, cube[2]},
        {cube[0], cube[1], cube[2] - 1},
        {cube[0], cube[1], cube[2] + 1}
    };
    return neighbours;
}

// Determine bounding box of region occupied by lava, plus one cube border.
void Droplet::setLimits() {
    for (int idx = 0; idx < 6; idx++) {
	limits[idx % 3][idx / 3] = cubes[0][idx % 3]
	    + ((idx / 3 == 0) ? -1 : 1);
    }
    for (int idx1 = 1; idx1 < cubes.size(); idx1++) {
        for (int idx2 = 0; idx2 < 3; idx2++) {
	    limits[idx2][0] = std::min(limits[idx2][0], cubes[idx1][idx2] - 1);
	    limits[idx2][1] = std::max(limits[idx2][1], cubes[idx1][idx2] + 1);
        }
    }
}

// Determine whether a cube is inside the bounding box of the lava region.
int Droplet::inLimits(std::vector<int> cube) {
    int inside = 1;
    for (int idx = 0; idx < 3; idx++) {
	if (cube[idx] < limits[idx][0] || cube[idx] > limits[idx][1] ) {
	    inside = 0;
	    break;
	}
    }
    return inside;
}

// Calculate external surface area: work through cubes outside the
// lava region, and add 1 for each cube surface with a neighbour in lava.
int Droplet::externalSurfaceArea() {
    int area = 0;

    // Initiate stack of test cubes and map of known coordinates
    // with a cube external to the lava region.
    std::vector<int> cube {limits[0][0], limits[1][0], limits[2][0]};
    std::stack<std::vector<int>> testCubes;
    testCubes.push(cube);
    std::map<int, std::map<int, std::map<int, bool>>> knownCoordinates;
    knownCoordinates[cube[0]][cube[1]][cube[2]] = true;

    // Test cubes in stack.
    while (testCubes.size() > 0) {
	cube = testCubes.top();
	testCubes.pop();

	// Loop over neighbours of current cube.
	for (auto neighbour : getNeighbours(cube)) {

	    // Disregard neighbour if outside bounding box of lava region,
	    // or if already known.
            if (!inLimits(neighbour)) {continue;}
	    int knownNeighbour = 0;
            try {
                knownCoordinates.at(
	            neighbour[0]).at(neighbour[1]).at(neighbour[2]);
		knownNeighbour = 1;
            }
	    catch (std::out_of_range exception) {
	    }
            if (knownNeighbour) {continue;}

	    if (isLava(neighbour)) {
		// External cube borders cube in lava:
		// add one to external surface area.
	        area++;
	    } else {
		// Neighbour is external to the lava region:
		// add to the stack of test cubes,
		// and to the map of know coordinates.
	        testCubes.push(neighbour);
                knownCoordinates[
		    neighbour[0]][neighbour[1]][neighbour[2]] = true;
	    }
	}
    }
    return area;
}
