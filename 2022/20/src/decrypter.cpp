// Implementation of class representing a decryption device.

#include <fstream>
#include <iostream>
#include <numeric>
#include "decrypter.h"

// Read numbers, and push to vector.
Decrypter::Decrypter(std::string path_) {
    std::ifstream inFile(path_);
    std::string line;
    while (getline(inFile, line)) {
	numbers.push_back(stoi(line));
    }
}

// Mix numbers.
std::vector<long> Decrypter::mix(int nmix, long key) {

    // Create copy of input numbers, and vector of indices.
    std::vector<long> numbers1(numbers);
    std::vector<long> numbers2(numbers1.size());
    std::iota(numbers2.begin(), numbers2.end(), 0);

    // Multiply numbers by key, if this is different from 1.
    if (key != 1) {
        for (auto iter = numbers1.begin(); iter != numbers1.end(); iter++) {
	    *iter *= key;
	}
    }

    // Mix indices required number of times,
    // following mixing order given by original input.
    // Use modular arithmetic to move indices around circular array.
    int divisor = numbers2.size() - 1;
    for (int imix = 0; imix < nmix; imix++) {
        for (int idx1 = 0; idx1 < numbers2.size(); idx1++) {
            auto iter = std::find(numbers2.begin(), numbers2.end(), idx1);
	    auto idx2 = iter - numbers2.begin() + numbers1[idx1];
	    auto idx3 = idx2 % divisor;
	    if (idx3 < 0) {
		idx3 = divisor + idx3;
	    }
	    numbers2.erase(iter);
	    numbers2.insert(numbers2.begin() + idx3, idx1);
        }
    }

    // Replaces indices by corresponding values.
    for (auto iter = numbers2.begin(); iter != numbers2.end(); iter++) {
        *iter = numbers1[*iter];
    }

    return numbers2;
}

// Apply puzzle logic to determine grove coordinates.
long Decrypter::getCoordinates(int nmix, int key) {

    std::vector<long> values = mix(nmix, key);
    int idx0 = std::find(values.begin(), values.end(), 0) - values.begin();

    long coordinates = 0;
    for (int idx = 1000; idx <= 3000; idx += 1000) {
	coordinates += values[(idx0 + idx) % values.size()];
    }

    return coordinates;
}
