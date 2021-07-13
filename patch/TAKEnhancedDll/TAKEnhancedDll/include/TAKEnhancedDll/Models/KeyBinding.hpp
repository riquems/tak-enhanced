#pragma once

#include "Command.hpp"
#include "Keys.hpp"

struct KeyBinding
{
    Command command;
    Keys keys;
};