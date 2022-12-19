// Implementation of class representing a network of valves.

#include <algorithm>
#include <fstream>
#include <iostream>
#include "network.h"
#include "utils.h"

// Read data, define valves in network, calculate distances between valves.
Network::Network(std::string path_) {
    std::ifstream inFile(path_);
    std::string line;
    while (getline(inFile, line)) {
        addValve(line);
    }
    setDistances();
}

// Parse input data, and create vector of valve objects.
void Network::addValve(std::string line) {
    int bit;
    for (auto delimiter : delimiters) {
	if ('=' == delimiter) {
            std::replace(line.begin(), line.end(), delimiter, ' ');
	} else {
            line.erase(remove(line.begin(), line.end(), delimiter), line.end());
	}
    }
    std::vector<std::string> elements = splitString(line, " ");
    std::string id = elements[1];
    int flowRate = stoi(elements[5]);
    valveIds.push_back(id);
    if (flowRate > 0) {
	bit = pressureValveIds.size();
	pressureValveIds.push_back(id);
    } else {
	bit = -1;
    }
    Valve* valve = new Valve(id, flowRate, bit);
    valves[id] = valve;
    for (int idx = 10; idx < elements.size(); idx++) {
        valve->distances[elements[idx]] = 1;
    }
}

// Calcuate and store distances between valves.
void Network::setDistances() {
    // Initialise distances to non-adjoining valves to big number.
    for (auto id1 : valveIds) {
        for (auto id2 : valveIds) {
	    if (valves[id1]->distances.find(id2)
	        == valves[id1]->distances.end()) {
		valves[id1]->distances[id2] = bigNumber;
	    }   
	}	
    }

    // Determine minimum distances.
    for (auto id3 : valveIds) {
        for (auto id1 : valveIds) {
            if (valves[id1]->distances[id3] == bigNumber) {continue;}
            for (auto id2 : valveIds) {
                if (valves[id3]->distances[id2] == bigNumber) {continue;}
		valves[id1]->distances[id2] = std::min(
		    valves[id1]->distances[id2],
		valves[id1]->distances[id3] + valves[id3]->distances[id2]);
	    }
	}	
    }
}

// Calculate cumulative flows, given valves visited.
void Network::visitValve(std::string id1, int time,
    int visited, int flow, std::map<int, int> & flows) {
    int flowVisited = (flows.find(visited) != flows.end()) ? flows[visited] : 0;
    flows[visited] = std::max(flowVisited, flow);
    for (auto id2 : pressureValveIds) {
	int timeLeft = time - valves[id1]->distances[id2] - 1;
	if ((valves[id2]->bit & visited) || timeLeft <= 0) {continue;}
	visitValve(id2, timeLeft, visited | valves[id2]->bit,
            flow + timeLeft * valves[id2]->flowRate, flows);
    }
}

// Calculate maximum pressure release for one individual opening valves.
int Network::maxPressureRelease1(std::string id, int time) {
    std::map<int, int> flows;
    visitValve(id, time, 0, 0, flows);
    int maxFlow = 0;
    for (auto flow : flows) {
        maxFlow = std::max(maxFlow, flow.second);
    }
    return maxFlow;
}

// Calculate maximum pressure release for two individuals opening valves.
int Network::maxPressureRelease2(std::string id, int time) {

    std::map<int, int> flows;
    visitValve(id, time, 0, 0, flows);
    int maxFlow = 0;
    for (auto flow1 : flows) {
	for (auto flow2 : flows) {
	    if (!(flow1.first & flow2.first)) {
                maxFlow = std::max(maxFlow, flow1.second + flow2.second);
	    }
	}
    }
    return maxFlow;
}
