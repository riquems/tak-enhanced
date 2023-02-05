#pragma once
#include "TAKEnhancedDll/common.hpp"
#include <TAKEnhancedDll/Keys/Key.hpp>
#include <Utils/VirtualKeys.h>

class Keys
{
    std::vector<Key> keys = {
        Key { VK_NONE, "None" },
        Key { VK_CTRL, "CTRL" },
        Key { VK_SHIFT, "SHIFT" },
        Key { VK_BACKSPACE, "BACKSPACE" },
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

public:
    std::optional<Key> get(uint vk);
    std::optional<Key> find(std::function<bool(const Key&)> predicate);
};

extern Keys keys;
