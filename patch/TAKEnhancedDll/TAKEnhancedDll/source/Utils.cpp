#include "TAKEnhancedDll/Utils.hpp"

template <typename T1, typename T2>
std::unordered_map<T2, T1> build_reversed_map(const std::unordered_map<T1, T2>& map1)
{
    std::unordered_map<T2, T1> map2;

    std::for_each(map1.begin(), map1.end(), [&](std::pair<T1, T2> elem) {
        map2.insert(std::pair<T2, T1>(elem.second, elem.first));
        });

    return map2;
}
