#pragma once
#include "TAKEnhancedLibrary/common.hpp"

struct Key
{
    short vk;
    std::string name;

    bool operator==(const Key& key) const {
        return this->vk == key.vk;
    }

    bool operator!=(const Key& key) const {
        return !(*this == key);
    }

    bool operator==(const short& vk) const {
        return this->vk == vk;
    }

    bool operator!=(const short& vk) const {
        return !(*this == vk);
    }
};
