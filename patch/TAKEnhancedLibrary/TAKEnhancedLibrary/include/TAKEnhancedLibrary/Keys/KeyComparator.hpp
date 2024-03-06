#pragma once
#include "TAKEnhancedLibrary/common.hpp"
#include "TAKEnhancedLibrary/Keys/Key.hpp"

namespace KeyComparator
{
    bool isLike(const Key& k1, const Key& k2);
    bool isLike(const Key& k1, const short& k2);
    bool isLike(const short& k1, const Key& k2);
};
