#include "TAKEnhancedLibrary/Keys/Keys.hpp"

Keys::Keys() {
    this->keys = {
       None,
       Shift,
       LShift,
       RShift,
       Ctrl,
       RCtrl,
       LCtrl,
       Alt,
       RAlt,
       LAlt,
       Backspace,
       Return,
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
    };
}

Key Keys::None = Key { VK_NONE, "None" };
Key Keys::Backspace = Key { VK_BACKSPACE, "BACKSPACE" };

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
