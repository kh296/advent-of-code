#include <fstream>
#include <iostream>
#include <string>
#include<vector> 
  
class Elf {
    public:
    int id;
    int calCount;
    Elf(int idx, int calCountx) {
        id = idx;
        calCount = calCountx;
    };
};

class ElfCollection {
    public:
    std::vector<Elf> elves;
    ElfCollection(std::string path) {
        std::string line;
        std::ifstream inFile(path);

        int id = 1;
        int calCount = 0;

        while (getline (inFile, line)) {
        if (line.empty()) {
            elves.push_back(Elf(id, calCount));
            calCount = 0;
            id++;
        }
        else {
            calCount += std::stoi(line);
        }
        }
        if (calCount > 0) {
            elves.push_back(Elf(id, calCount));
        }

        inFile.close();

        std::sort(elves.begin(), elves.end(),
		       	[](const Elf& lhs, const Elf& rhs) {
		       	return lhs.calCount > rhs.calCount;
		       	});
    };
};

int main(int argc, char *argv[])
{
    std::vector<Elf> elves = ElfCollection(argv[1]).elves;
    std::cout << "Elf " << elves[0].id << " carries "
        << elves[0].calCount << " calories.\n";
    std::cout << "Elves " << elves[0].id << ", " << elves[1].id << ", "
        << elves[2].id << " carry "
	<< elves[0].calCount + elves[1].calCount + elves[2].calCount
       	<< " calories.\n";
    return 0;
}
