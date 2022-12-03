#include <fstream>
#include <iostream>
#include <map>
#include <string>

using namespace std;

class Scorer {
    private:
    const int rock= 1 ;
    const int paper = 2;
    const int scissors = 3;
    const int loss = 0;
    const int draw = 3;
    const int win = 6;
    const int scores[3][3] = {
        {rock + draw, paper + win, scissors + loss},
        {rock + loss, paper + draw, scissors + win},
        {rock + win, paper + loss, scissors + draw}
    };
    const int fix_results[3][3] = {
        {2, 0, 1},
        {0, 1, 2},
        {1, 2, 0},
    };

    public:
    int total1 = 0;
    int total2 = 0;
    Scorer(string path) {
        string line;
        ifstream inFile(path);
        map<char, int> choices1{{'A', 0}, {'B', 1}, {'C', 2}};
        map<char, int> choices2{{'X', 0}, {'Y', 1}, {'Z', 2}};

        while (getline (inFile, line)) {
            if (3 == line.length()) {
            int choice1 = choices1[line[0]];
            int choice2 = choices2[line[2]];
            total1 += scores[choice1][choice2];
            int choice3 = fix_results[choice1][choice2];
            total2 += scores[choice1][choice3];
            }
        }

        inFile.close();
    }
};

int main(int argc, char *argv[])
{
    string path;
    if (argc > 1) {
        path = argv[1];
    }
    else {
        path = "example.txt";
    }

    Scorer scorer = Scorer(path);
    std::cout << "Strategy 1: " << scorer.total1 << std::endl;
    std::cout << "Strategy 2: " << scorer.total2 << std::endl;

    return 0;
};
