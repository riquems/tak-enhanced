#include "TAKEnhancedDll/Keys/Keys.hpp"

Key Keys::ENTER = Key { VK_RETURN, "ENTER" };

std::optional<Key> Keys::get(uint vk) {
    return dky::find(this->keys, [&](const Key& key) {
        return key.vk == vk;
    });
}

std::optional<Key> Keys::find(std::function<bool(const Key&)> predicate) {
    return dky::find(this->keys, predicate);
}
