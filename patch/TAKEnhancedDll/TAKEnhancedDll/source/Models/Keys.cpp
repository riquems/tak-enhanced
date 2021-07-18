#pragma once
#include "TAKEnhancedDll/Models/Keys.hpp"

std::unordered_map<int, std::string> keyToStr = {
    std::pair<int, std::string>(VK_NONE, "None"),
    std::pair<int, std::string>(VK_CTRL, "CTRL"),
    std::pair<int, std::string>(VK_SHIFT, "SHIFT"),
    std::pair<int, std::string>(VK_BACKSPACE, "BACKSPACE"),

    std::pair<int, std::string>(VK_1, "1"),
    std::pair<int, std::string>(VK_2, "2"),
    std::pair<int, std::string>(VK_3, "3"),
    std::pair<int, std::string>(VK_4, "4"),
    std::pair<int, std::string>(VK_5, "5"),
    std::pair<int, std::string>(VK_6, "6"),
    std::pair<int, std::string>(VK_7, "7"),
    std::pair<int, std::string>(VK_8, "8"),
    std::pair<int, std::string>(VK_9, "9"),
    std::pair<int, std::string>(VK_0, "0"),
    std::pair<int, std::string>(VK_A, "A"),
    std::pair<int, std::string>(VK_B, "B"),
    std::pair<int, std::string>(VK_C, "C"),
    std::pair<int, std::string>(VK_D, "D"),
    std::pair<int, std::string>(VK_E, "E"),
    std::pair<int, std::string>(VK_F, "F"),
    std::pair<int, std::string>(VK_G, "G"),
    std::pair<int, std::string>(VK_H, "H"),
    std::pair<int, std::string>(VK_I, "I"),
    std::pair<int, std::string>(VK_J, "J"),
    std::pair<int, std::string>(VK_K, "K"),
    std::pair<int, std::string>(VK_L, "L"),
    std::pair<int, std::string>(VK_M, "M"),
    std::pair<int, std::string>(VK_N, "N"),
    std::pair<int, std::string>(VK_O, "O"),
    std::pair<int, std::string>(VK_P, "P"),
    std::pair<int, std::string>(VK_Q, "Q"),
    std::pair<int, std::string>(VK_R, "R"),
    std::pair<int, std::string>(VK_S, "S"),
    std::pair<int, std::string>(VK_T, "T"),
    std::pair<int, std::string>(VK_U, "U"),
    std::pair<int, std::string>(VK_V, "V"),
    std::pair<int, std::string>(VK_W, "W"),
    std::pair<int, std::string>(VK_X, "X"),
    std::pair<int, std::string>(VK_Y, "Y"),
    std::pair<int, std::string>(VK_Z, "Z"),
};

std::unordered_map<std::string, int> strToKey;

template <typename T1, typename T2>
std::unordered_map<T2, T1> build_reversed_map(const std::unordered_map<T1, T2>& map1)
{
    std::unordered_map<T2, T1> map2;

    std::for_each(map1.begin(), map1.end(), [&](std::pair<T1, T2> elem) {
        map2.insert(std::pair<T2, T1>(elem.second, elem.first));
        });

    return map2;
}

void initializeKeys()
{
    strToKey = build_reversed_map(keyToStr);
}

Keys::Keys() {}
Keys::Keys(std::initializer_list<int> init_list) : values(init_list) {}

std::string Keys::to_string() const {
    std::string keysStr;

    for (size_t i = 0; i < values.size(); i++) {
        keysStr.append(keyToStr[values.at(i)]);

        if (i < values.size() - 1) {
            keysStr.append(" + ");
        }
    }

    return keysStr;
}

bool Keys::operator==(const Keys& keys) const
{
    for (int i = 0; i < keys.values.size(); i++) {
        if (this->values[i] != keys.values[i]) {
            return false;
        }
    }

    return true;
}

std::size_t KeysHashFunction::operator()(const Keys& keys) const
{
    std::size_t hf = 0;

    for (int i = 0; i < keys.values.size(); i++) {
        hf = hf ^ std::hash<int>()(keys.values[i]);
    }

    return hf;
}

Keys strToKeys(std::string str) {
    Keys keys;

    char* keyStrBuffer = _strdup(str.c_str());

    char* keyStr = strtok(keyStrBuffer, " + ");
    while (keyStr != NULL) {
        int key = strToKey[keyStr];

        keys.values.push_back(key);

        keyStr = strtok(NULL, " + ");
    }

    return keys;
}
