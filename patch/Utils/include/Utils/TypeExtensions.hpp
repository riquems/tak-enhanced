#pragma once

template<typename T, typename U>
bool is(U& widget) {
    return dynamic_cast<T*>(&widget) != nullptr;
}
