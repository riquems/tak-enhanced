#pragma once

#include <algorithm>
#include <unordered_map>

template <typename T1, typename T2>
std::unordered_map<T2, T1> build_reversed_map(const std::unordered_map<T1, T2>& map1);
