#include "TAKEnhancedLibrary/Keys/Keys.hpp"

Keys::Keys() {
    this->keys = {
       Key { VK_NONE, "None" },
       Shift,
       LShift,
       RShift,
       Ctrl,
       RCtrl,
       LCtrl,
       Alt,
       RAlt,
       LAlt,
       Key { VK_BACKSPACE, "BACKSPACE" },
       Return,
       Key { VK_1, "1" },
       Key { VK_2, "2" },
       Key { VK_3, "3" },
       Key { VK_4, "4" },
       Key { VK_5, "5" },
       Key { VK_6, "6" },
       Key { VK_7, "7" },
       Key { VK_8, "8" },
       Key { VK_9, "9" },
       Key { VK_0, "0" },
       Key { VK_A, "A" },
       Key { VK_B, "B" },
       Key { VK_C, "C" },
       Key { VK_D, "D" },
       Key { VK_E, "E" },
       Key { VK_F, "F" },
       Key { VK_G, "G" },
       Key { VK_H, "H" },
       Key { VK_I, "I" },
       Key { VK_J, "J" },
       Key { VK_K, "K" },
       Key { VK_L, "L" },
       Key { VK_M, "M" },
       Key { VK_N, "N" },
       Key { VK_O, "O" },
       Key { VK_P, "P" },
       Key { VK_Q, "Q" },
       Key { VK_R, "R" },
       Key { VK_S, "S" },
       Key { VK_T, "T" },
       Key { VK_U, "U" },
       Key { VK_V, "V" },
       Key { VK_W, "W" },
       Key { VK_X, "X" },
       Key { VK_Y, "Y" },
       Key { VK_Z, "Z" }
    };
}

Key Keys::Shift = Key { .vk = VK_SHIFT, .name = "Shift" };
Key Keys::LShift = Key { .vk = VK_LSHIFT, .name = "LShift" };
Key Keys::RShift = Key { .vk = VK_RSHIFT, .name = "RShift" };
Key Keys::Ctrl = Key { .vk = VK_CTRL, .name = "Ctrl" };
Key Keys::LCtrl = Key { .vk = VK_LCTRL, .name = "LCtrl" };
Key Keys::RCtrl = Key { .vk = VK_RCTRL, .name = "RCtrl" };
Key Keys::Alt = Key { .vk = VK_ALT, .name = "Alt" };
Key Keys::LAlt = Key { .vk = VK_LALT, .name = "LAlt" };
Key Keys::RAlt = Key { .vk = VK_RALT, .name = "RAlt" };
Key Keys::Return = Key { .vk = VK_RETURN, .name = "Return" };

std::optional<Key> Keys::get(short vk) {
    return dky::find(this->keys, [&](const Key& key) {
        return key == vk;
    });
}

std::optional<Key> Keys::find(std::function<bool(const Key&)> predicate) {
    return dky::find(this->keys, predicate);
}
