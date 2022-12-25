#ifndef DROPLET_H
#define DROPLET_H

#include <map>
#include <string>
#include <vector>

class Droplet {
    private:
    int limits[3][2];
    std::vector<std::vector<int>> cubes;
    std::map<int, std::map<int, std::map<int, bool>>> coordinates;
    public:
    Droplet(std::string);
    int surfaceArea();
    int isLava(std::vector<int>);
    std::vector<std::vector<int>> getNeighbours(std::vector<int>);
    void setLimits();
    int inLimits(std::vector<int>);
    int externalSurfaceArea();
};

#endif
