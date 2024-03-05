#include "Utils/Keyboard.hpp"
#include "Utils/Windows.hpp"

std::shared_ptr<KeyboardState> previousKeyboardState = nullptr;

std::shared_ptr<KeyboardState> MyGetKeyboardState() {
    auto keyboardState = std::make_shared<KeyboardState>();

    for (int keyCode = 0x08; keyCode <= 254; keyCode++) {
        short keyState = GetAsyncKeyState(keyCode);

        if (keyState & 0x8000) {
            if (previousKeyboardState != nullptr && previousKeyboardState->keys[keyCode] == KeyState::Released) {
                keyboardState->keys[keyCode] = KeyState::JustPressed;
            }
            else {
                keyboardState->keys[keyCode] = KeyState::Pressed;
            }
        }
        else {
            if (previousKeyboardState != nullptr && previousKeyboardState->keys[keyCode] == KeyState::Pressed) {
                keyboardState->keys[keyCode] = KeyState::JustReleased;
            }
            else {
                keyboardState->keys[keyCode] = KeyState::Released;
            }
        }
    }

    previousKeyboardState = keyboardState;

    return keyboardState;
}
