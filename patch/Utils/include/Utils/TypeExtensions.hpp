#pragma once

template<typename T, typename U>
bool is(U& widget) {
    return dynamic_cast<T*>(&widget) != nullptr;
}

template<typename T, typename U>
bool is_not(U& widget) {
    return dynamic_cast<T*>(&widget) == nullptr;
}
