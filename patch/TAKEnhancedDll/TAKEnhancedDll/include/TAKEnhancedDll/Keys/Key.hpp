#pragma once
#include "TAKEnhancedDll/common.hpp"

struct Key
{
    uint vk;
    std::string name;

    bool operator==(const Key& keyCombination) const {
        return this->vk == keyCombination.vk;
    }

    bool operator!=(const Key& keyCombination) const {
        return !(*this == keyCombination);
    }

    bool operator==(const uint vk) const {
        return this->vk == vk;
    }

    bool operator!=(const uint vk) const {
        return !(*this == vk);
    }
};
