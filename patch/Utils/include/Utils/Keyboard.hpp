#pragma once
#include "common.h"

enum KeyState
{
    Pressed,
    JustPressed,
    Released,
    JustReleased
};

NLOHMANN_JSON_SERIALIZE_ENUM(KeyState, {
    { Pressed, "Pressed" },
    { JustPressed, "JustPressed" },
    { Released, "Released" },
    { JustReleased, "JustReleased" }
});

struct KeyboardState
{
    std::unordered_map<short, KeyState> keys;
};

std::shared_ptr<KeyboardState> MyGetKeyboardState();
