#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <string>
#include <vector>

class Communicator{
    private:
    std::vector<std::string> messages;
    const std::string dividers[2] = {"[[2]]", "[[6]]"};
    public:
    Communicator(std::string);
    static std::vector<std::string> splitItem(std::string);
    static int compareItems(std::string, std::string);
    static bool compareMessages(std::string, std::string);
    int rightOrder();
    int decoderKey();
};

#endif
