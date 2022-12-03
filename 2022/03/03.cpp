#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

string getCommonLetters(string str1, string str2) {
    string commonLetters = "";
    map<char, bool> letters;
    for (int i = 0; i < str1.size(); ++i) {
        letters.insert({str1[i], true});
    }
    for (int i = 0; i < str2.size(); ++i) {
        if (letters.find(str2[i]) != letters.end()
            && commonLetters.find(str2[i]) == string::npos) {
            commonLetters += str2[i];
        }
    }
    return commonLetters;
};

class BagSearcher {
    private:
    const int offsetLower = (int) 'a' - 1;
    const int offsetUpper = (int) 'A' - 27;
    vector<string> rucksacks;
    public:
    int priority1 = 0;
    int priority2 = 0;
    BagSearcher(string path) {
        string line;
        string common;
        ifstream inFile(path);

        while (getline (inFile, line)) {
            int halfLength = line.length() / 2;
            string compartment1 = line.substr(0, halfLength);
            string compartment2 = line.substr(halfLength, string::npos);
            common = getCommonLetters(compartment1, compartment2);
            if (common.length() != 1) {
                cout << "Items in both compartments different from 1: " << common << endl;
            }
            else {
                int offset = islower(common[0]) ? offsetLower : offsetUpper;
                priority1 += (int) common[0] - offset;
            }

            rucksacks.push_back(line);

            if (rucksacks.size() == 3) {
                common = getCommonLetters(rucksacks[0], rucksacks[1]);
                common = getCommonLetters(common, rucksacks[2]);
                if (common.length() != 1) {
                    cout << "Shared items different from 1: " << common << endl;
                }
                else {
                    int offset = islower(common[0]) ? offsetLower : offsetUpper;
                    priority2 += (int) common[0] - offset;
                    }
                rucksacks.clear();
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

    BagSearcher bagSearcher = BagSearcher(path);
    std::cout << "Priority 1: " << bagSearcher.priority1 << endl;
    std::cout << "Priority 2: " << bagSearcher.priority2 << endl;

    return 0;
};