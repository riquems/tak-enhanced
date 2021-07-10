#pragma once

#include "Command.h"
#include "Keys.h"

struct KeyBinding
{
    Command command;
    Keys keys;
};