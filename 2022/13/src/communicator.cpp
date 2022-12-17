// Implementation of class representing a communicator.

#include <fstream>
#include <iostream>
#include "communicator.h"
#include "utils.h"

// Read data.
Communicator::Communicator(std::string path_) {
    std::ifstream inFile(path_);
    std::string message;
    while (std::getline(inFile, message)) {
	if (message.length()) {
            messages.push_back(message);
	}
    }
}

// Split item into its component items.
std::vector<std::string> Communicator::splitItem(std::string inItem) {
    // Strip away item's open and close brackets.
    std::string item = inItem.substr(1, inItem.length() - 2);

    // Substitute space for comma, if not inside parentheses.
    int level = 0;
    for (int idx = 0; idx < item.length(); idx++) {
        if ('[' == item[idx]) {
            level++;
	} else if (']' == item[idx]) {
            level--;
	} else if (',' == item[idx] && 0 == level) {
            item[idx] = ' ';
	}
    }

    // Split at spaces.
    std::vector<std::string> items;
    if (item.find(" ") == std::string::npos) {
	if (item.length() > 0) {
            items.push_back(item);
	}
    } else {
        items = splitString(item, " ");
    }
    return items;
}

// Determine whether message msg1 comes before (false)
// or after (true) message msg2.
// (In contrast with compareItems(), this doesn't allow for order undetermined.)
bool Communicator::compareMessages(std::string msg1, std::string msg2) {
    return (compareItems(msg1, msg2) == 1);
}

// Determine whether inItem1 comes before inItem2 (return value 0),
// after inItem2 (return value 1), or whether order is undetermined
// (return value -1).
int Communicator::compareItems(std::string inItem1, std::string inItem2) {
	std::vector<std::string> items1 = splitItem(inItem1);
	std::vector<std::string> items2 = splitItem(inItem2);

	for (int idx = 0; idx < items1.size(); idx++) {
	    if (idx >= items2.size()) {
	        return 0;
	    }

	    std::string item1 = items1[idx];
	    std::string item2 = items2[idx];

	    // Both items are integers.
	    if ('[' != item1[0] && '[' != item2[0]) {
                int val1 = stoi(item1);
		int val2 = stoi(item2);
		if (val1 < val2) {
		    return 1;
		} else if (val1 > val2) {
		    return 0;
		} else {
		    continue;
		}
	    }

	    // At least one item is a list.
	    if ('[' != item1[0]) {
		item1 = "[" + item1 + "]";
	    }
	    if ('[' != item2[0]) {
		item2 = "[" + item2 + "]";
	    }

	    // Compare the lists.
            int comparison = compareItems(item1, item2);
            if (-1 != comparison) {
		return comparison;
            }
	}

	if (items1.size() < items2.size()) {
	    return 1;
	}

    return -1;
}

// Count number of message pairs in right order.
int Communicator::rightOrder() {
    int sum = 0;
    for (int idx = 0; idx < messages.size() / 2; idx++) {
        sum += (idx + 1) * compareItems(
	    messages[2 * idx], messages[2 * idx + 1]);
    }
    return sum;
}

// Add dividers, sort messages, then determine decoderKey
// (product of divider indicies).
int Communicator::decoderKey() {
    for (auto divider : dividers) {
        messages.push_back(divider);
    }

    sort(messages.begin(), messages.end(), compareMessages);

    int decoderKey = 1;
    int idx = 0;
    int nDivider = 0;
    for (auto message: messages) {
	idx++;
        for (auto divider : dividers) {
	    if (divider == message) {
                decoderKey *= idx;
		nDivider++;
	    }
	}
        if (nDivider == sizeof(dividers)) {
            break;
	}
    }
    return decoderKey;
}
