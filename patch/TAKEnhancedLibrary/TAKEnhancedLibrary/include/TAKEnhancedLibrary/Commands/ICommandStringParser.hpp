#pragma once
#include "TAKEnhancedLibrary/common.hpp"
#include "TAKEnhancedLibrary/Commands/Command.hpp"

class ICommandStringParser
{
protected:
    virtual std::unique_ptr<Command> _fromString(std::string str) = 0;

public:
    Command ofCommand;

    ICommandStringParser(Command ofCommand) : ofCommand(ofCommand) {}

    static std::vector<std::string> getCommandParts(std::string str) {
        std::regex regex("[^\\s\"']+|\"([^\"]*)\"|'([^']*)'");

        std::sregex_iterator it = std::sregex_iterator(
            str.begin(),
            str.end(),
            regex
        );

        std::vector<std::string> matches;

        while (it != std::sregex_iterator()) {
            std::smatch m = *it;
            matches.push_back(m.str());
            it++;
        }

        return matches;
    }

    bool canParse(const std::string& str) {
        auto cmdParts = getCommandParts(str);

        return cmdParts.at(0) == this->ofCommand.name;
    };

    virtual std::string toString(const Command& command) = 0;
    std::unique_ptr<Command> fromString(std::string str) { return this->_fromString(str); };
};

