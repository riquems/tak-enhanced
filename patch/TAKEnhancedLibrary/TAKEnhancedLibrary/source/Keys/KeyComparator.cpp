#include "TAKEnhancedLibrary/Keys/KeyComparator.hpp"
#include "TAKEnhancedLibrary/Keys/Keys.hpp"

bool KeyComparator::isLike(const Key& k1, const Key& k2) {
    return isLike(k1, k2.vk);
}

bool KeyComparator::isLike(const Key& k1, const short& k2) {
    if (k1 == k2)
        return true;

    static std::unordered_map<short, std::vector<Key>> keyNormalization = {
        { Keys::Shift.vk, { Keys::LShift, Keys::RShift } },
        { Keys::LShift.vk, { Keys::Shift, Keys::LShift } },
        { Keys::RShift.vk, { Keys::Shift, Keys::RShift } },
        { Keys::Ctrl.vk, { Keys::LCtrl, Keys::RCtrl } },
        { Keys::LCtrl.vk, { Keys::Ctrl, Keys::LCtrl } },
        { Keys::RCtrl.vk, { Keys::Ctrl, Keys::RCtrl } },
        { Keys::Alt.vk, { Keys::LAlt, Keys::RAlt } },
        { Keys::LAlt.vk, { Keys::Alt, Keys::LAlt } },
        { Keys::RAlt.vk, { Keys::Alt, Keys::RAlt } }
    };

    if (keyNormalization.contains(k1.vk)) {
        auto& keys = keyNormalization[k1.vk];

        return dky::contains(keys, [&](const Key& x) {
            return x == k2;
        });
    }

    return false;
}

bool KeyComparator::isLike(const short& k1, const Key& k2) {
    return isLike(k2, k1);
}
