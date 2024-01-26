#pragma once

#include "TAKEnhancedLibrary/Commands/Command.hpp"

class CommandHandler
{
    virtual void _handle(const Command& command) = 0;

public:
    CommandHandler() {}

    void handle(const Command& command) { return _handle(command); }
};
