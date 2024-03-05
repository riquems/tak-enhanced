#include "TAKEnhancedLibrary/Keys/KeyCombination.hpp"

KeyCombination::KeyCombination() {}
KeyCombination::KeyCombination(std::initializer_list<Key> init_list) : keys(init_list) {}

bool KeyCombination::operator==(const KeyCombination& keyCombination) const
{
    for (int i = 0; i < keyCombination.keys.size(); i++) {
        if (this->keys[i].vk != keyCombination.keys[i].vk) {
            return false;
        }
    }

    return true;
}

std::size_t KeyCombinationHashFunction::operator()(const KeyCombination& keyCombination) const
{
    std::size_t hf = 0;

    for (int i = 0; i < keyCombination.keys.size(); i++) {
        hf = hf ^ std::hash<int>()(keyCombination.keys[i].vk);
    }

    return hf;
}
