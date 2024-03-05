#pragma once
#include "TAKEnhancedLibrary/common.hpp"
#include <TAKEnhancedLibrary/Keys/Key.hpp>
#include <Utils/VirtualKeys.h>

class Keys
{
public:
    std::vector<Key> keys;

    Keys();

    static Key Shift;
    static Key LShift;
    static Key RShift;
    static Key Ctrl;
    static Key LCtrl;
    static Key RCtrl;
    static Key Alt;
    static Key LAlt;
    static Key RAlt;
    static Key Return;

    std::optional<Key> get(short vk);
    std::optional<Key> find(std::function<bool(const Key&)> predicate);
};

extern Keys keys;
