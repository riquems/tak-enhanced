#include "TAKEnhancedLibrary/Keys/Keys.hpp"

Keys::Keys() {
    this->keys = {
        None,
        Key_1,
        Key_2,
        Key_3,
        Key_4,
        Key_5,
        Key_6,
        Key_7,
        Key_8,
        Key_9,
        Key_0,
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,
        Esc,
        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,
        Backspace,
        Return,
        SingleQuotes,
        DoubleQuotes,
        Tab,
        CapsLock,
        Minus,
        Equals,
        Cedilla,
        Comma,
        Dot,
        AcuteAccent,
        Tilde,
        Asterisk,
        Slash,
        Backslash,
        LBracket,
        RBracket,
        LBrace,
        RBrace,
        Colon,
        Semicolon,
        Shift,
        LShift,
        RShift,
        Ctrl,
        LCtrl,
        RCtrl,
        Alt,
        LAlt,
        RAlt,
        PrintScreen,
        ScrollLock,
        PauseBreak,
        Insert,
        Del,
        Home,
        End,
        PageUp,
        PageDown,
        ArrowUp,
        ArrowRight,
        ArrowDown,
        ArrowLeft,
        NumLock
    };
}

Key Keys::None = Key { .vk = VK_NONE, .name = "None" };

Key Keys::Key_1 = Key { .vk = VK_1, .name = "1" };
Key Keys::Key_2 = Key { .vk = VK_2, .name = "2" };
Key Keys::Key_3 = Key { .vk = VK_3, .name = "3" };
Key Keys::Key_4 = Key { .vk = VK_4, .name = "4" };
Key Keys::Key_5 = Key { .vk = VK_5, .name = "5" };
Key Keys::Key_6 = Key { .vk = VK_6, .name = "6" };
Key Keys::Key_7 = Key { .vk = VK_7, .name = "7" };
Key Keys::Key_8 = Key { .vk = VK_8, .name = "8" };
Key Keys::Key_9 = Key { .vk = VK_9, .name = "9" };
Key Keys::Key_0 = Key { .vk = VK_0, .name = "0" };

Key Keys::A = Key { .vk = VK_A, .name = "A" };
Key Keys::B = Key { .vk = VK_B, .name = "B" };
Key Keys::C = Key { .vk = VK_C, .name = "C" };
Key Keys::D = Key { .vk = VK_D, .name = "D" };
Key Keys::E = Key { .vk = VK_E, .name = "E" };
Key Keys::F = Key { .vk = VK_F, .name = "F" };
Key Keys::G = Key { .vk = VK_G, .name = "G" };
Key Keys::H = Key { .vk = VK_H, .name = "H" };
Key Keys::I = Key { .vk = VK_I, .name = "I" };
Key Keys::J = Key { .vk = VK_J, .name = "J" };
Key Keys::K = Key { .vk = VK_K, .name = "K" };
Key Keys::L = Key { .vk = VK_L, .name = "L" };
Key Keys::M = Key { .vk = VK_M, .name = "M" };
Key Keys::N = Key { .vk = VK_N, .name = "N" };
Key Keys::O = Key { .vk = VK_O, .name = "O" };
Key Keys::P = Key { .vk = VK_P, .name = "P" };
Key Keys::Q = Key { .vk = VK_Q, .name = "Q" };
Key Keys::R = Key { .vk = VK_R, .name = "R" };
Key Keys::S = Key { .vk = VK_S, .name = "S" };
Key Keys::T = Key { .vk = VK_T, .name = "T" };
Key Keys::U = Key { .vk = VK_U, .name = "U" };
Key Keys::V = Key { .vk = VK_V, .name = "V" };
Key Keys::W = Key { .vk = VK_W, .name = "W" };
Key Keys::X = Key { .vk = VK_X, .name = "X" };
Key Keys::Y = Key { .vk = VK_Y, .name = "Y" };
Key Keys::Z = Key { .vk = VK_Z, .name = "Z" };

Key Keys::Esc = Key { .vk = VK_ESCAPE, .name = "Esc" };
Key Keys::F1 = Key { .vk = VK_F1, .name = "F1" };
Key Keys::F2 = Key { .vk = VK_F2, .name = "F2" };
Key Keys::F3 = Key { .vk = VK_F3, .name = "F3" };
Key Keys::F4 = Key { .vk = VK_F4, .name = "F4" };
Key Keys::F5 = Key { .vk = VK_F5, .name = "F5" };
Key Keys::F6 = Key { .vk = VK_F6, .name = "F6" };
Key Keys::F7 = Key { .vk = VK_F7, .name = "F7" };
Key Keys::F8 = Key { .vk = VK_F8, .name = "F8" };
Key Keys::F9 = Key { .vk = VK_F9, .name = "F9" };
Key Keys::F10 = Key { .vk = VK_F10, .name = "F10" };
Key Keys::F11 = Key { .vk = VK_F11, .name = "F11" };
Key Keys::F12 = Key { .vk = VK_F12, .name = "F12" };

Key Keys::Backspace = Key { .vk = VK_BACKSPACE, .name = "Backspace" };
Key Keys::Return = Key { .vk = VK_RETURN, .name = "Return" };

Key Keys::SingleQuotes = Key { .vk = VK_OEM_7, .name = "'" };
Key Keys::DoubleQuotes = Key { .vk = VK_OEM_7, .name = "\"" };
Key Keys::Tab = Key { .vk = VK_TAB, .name = "Tab" };
Key Keys::CapsLock = Key { .vk = VK_CAPITAL, .name = "CapsLock" };
Key Keys::Minus = Key { .vk = VK_MINUS, .name = "-" };
Key Keys::Equals = Key { .vk = VK_OEM_PLUS, .name = "=" }; 
Key Keys::Cedilla = Key { .vk = VK_OEM_1, .name = "Ç" };
Key Keys::Comma = Key { .vk = VK_OEM_COMMA, .name = "," };
Key Keys::Dot = Key { .vk = VK_OEM_PERIOD, .name = "." };
Key Keys::AcuteAccent = Key { .vk = VK_OEM_3, .name = "`" };
Key Keys::Tilde = Key { .vk = VK_OEM_3, .name = "~" };
Key Keys::Asterisk = Key { .vk = VK_MULTIPLY, .name = "*" };
Key Keys::Slash = Key { .vk = VK_OEM_2, .name = "/" };
Key Keys::Backslash = Key { .vk = VK_OEM_5, .name = "\\" };

Key Keys::LBracket = Key { .vk = VK_OEM_4, .name = "[" };
Key Keys::RBracket = Key { .vk = VK_OEM_6, .name = "]" };

Key Keys::LBrace = Key { .vk = VK_OEM_4, .name = "{" };
Key Keys::RBrace = Key { .vk = VK_OEM_6, .name = "}" };

Key Keys::Colon = Key { .vk = VK_OEM_1, .name = ":" };
Key Keys::Semicolon = Key { .vk = VK_OEM_1, .name = ";" };

Key Keys::Shift = Key { .vk = VK_SHIFT, .name = "Shift" };
Key Keys::LShift = Key { .vk = VK_LSHIFT, .name = "LShift" };
Key Keys::RShift = Key { .vk = VK_RSHIFT, .name = "RShift" };
Key Keys::Ctrl = Key { .vk = VK_CTRL, .name = "Ctrl" };
Key Keys::LCtrl = Key { .vk = VK_LCTRL, .name = "LCtrl" };
Key Keys::RCtrl = Key { .vk = VK_RCTRL, .name = "RCtrl" };
Key Keys::Alt = Key { .vk = VK_ALT, .name = "Alt" };
Key Keys::LAlt = Key { .vk = VK_LALT, .name = "LAlt" };
Key Keys::RAlt = Key { .vk = VK_RALT, .name = "RAlt" };

Key Keys::PrintScreen = Key { .vk = VK_SNAPSHOT, .name = "PrintScreen" };
Key Keys::ScrollLock = Key { .vk = VK_SCROLL, .name = "ScrollLock" };
Key Keys::PauseBreak = Key { .vk = VK_PAUSE, .name = "PauseBreak" };

Key Keys::Insert = Key { .vk = VK_INSERT, .name = "Insert" };
Key Keys::Del = Key { .vk = VK_DELETE, .name = "Del" };

Key Keys::Home = Key { .vk = VK_HOME, .name = "Home" };
Key Keys::End = Key { .vk = VK_END, .name = "End" };

Key Keys::PageUp = Key { .vk = VK_PRIOR, .name = "PageUp" };
Key Keys::PageDown = Key { .vk = VK_NEXT, .name = "PageDown" };

Key Keys::ArrowUp = Key { .vk = VK_UP, .name = "ArrowUp" };
Key Keys::ArrowRight = Key { .vk = VK_RIGHT, .name = "ArrowRight" };
Key Keys::ArrowDown = Key { .vk = VK_DOWN, .name = "ArrowDown" };
Key Keys::ArrowLeft = Key { .vk = VK_LEFT, .name = "ArrowLeft" };

Key Keys::NumLock = Key { .vk = VK_NUMLOCK, .name = "NumLock" };

std::optional<Key> Keys::get(short vk) {
    return dky::find(this->keys, [&](const Key& key) {
        return key == vk;
    });
}

std::optional<Key> Keys::find(std::function<bool(const Key&)> predicate) {
    return dky::find(this->keys, predicate);
}
