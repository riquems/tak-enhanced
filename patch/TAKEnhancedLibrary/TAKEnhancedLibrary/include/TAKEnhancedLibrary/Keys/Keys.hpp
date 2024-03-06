#pragma once
#include "TAKEnhancedLibrary/common.hpp"
#include <TAKEnhancedLibrary/Keys/Key.hpp>
#include <Utils/VirtualKeys.h>

class Keys
{
public:
    std::vector<Key> keys;

    Keys();

    static Key None;
    static Key Backspace;

    static Key Key_1;
    static Key Key_2;
    static Key Key_3;
    static Key Key_4;
    static Key Key_5;
    static Key Key_6;
    static Key Key_7;
    static Key Key_8;
    static Key Key_9;
    static Key Key_0;

    static Key A;
    static Key B;
    static Key C;
    static Key D;
    static Key E;
    static Key F;
    static Key G;
    static Key H;
    static Key I;
    static Key J;
    static Key K;
    static Key L;
    static Key M;
    static Key N;
    static Key O;
    static Key P;
    static Key Q;
    static Key R;
    static Key S;
    static Key T;
    static Key U;
    static Key V;
    static Key W;
    static Key X;
    static Key Y;
    static Key Z;

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
