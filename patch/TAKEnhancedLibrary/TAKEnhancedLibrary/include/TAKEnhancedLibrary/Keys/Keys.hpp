#pragma once
#include "TAKEnhancedLibrary/common.hpp"
#include <TAKEnhancedLibrary/Keys/Key.hpp>
#include "Utils/VirtualKeys.h"

class Keys
{
public:
    std::vector<Key> keys;

    Keys();

    static Key None;

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

    static Key Esc;
    static Key F1;
    static Key F2;
    static Key F3;
    static Key F4;
    static Key F5;
    static Key F6;
    static Key F7;
    static Key F8;
    static Key F9;
    static Key F10;
    static Key F11;
    static Key F12;

    static Key Backspace;
    static Key Return;

    static Key SingleQuotes;
    static Key DoubleQuotes;
    static Key Tab;
    static Key CapsLock;
    static Key Minus;
    static Key Plus;
    static Key Equals;
    static Key Comma;
    static Key Dot;
    static Key Tilde;
    static Key Accent;
    static Key AcuteAccent;
    static Key Asterisk;
    static Key Cedilla;
    static Key Slash;
    static Key Backslash;

    static Key LParenthesis;
    static Key RParenthesis;

    static Key LBracket;
    static Key RBracket;

    static Key LBrace;
    static Key RBrace;

    static Key Colon;
    static Key Semicolon;

    static Key Shift;
    static Key LShift;
    static Key RShift;
    static Key Ctrl;
    static Key LCtrl;
    static Key RCtrl;
    static Key Alt;
    static Key LAlt;
    static Key RAlt;

    static Key PrintScreen;
    static Key ScrollLock;
    static Key PauseBreak;

    static Key Insert;
    static Key Del;

    static Key Home;
    static Key End;

    static Key PageUp;
    static Key PageDown;

    static Key ArrowUp;
    static Key ArrowRight;
    static Key ArrowDown;
    static Key ArrowLeft;

    static Key NumLock;

    std::optional<Key> get(short vk);
    std::optional<Key> find(std::function<bool(const Key&)> predicate);
};

extern Keys keys;
