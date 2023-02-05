#include "Utils/Keyboard.hpp"
#include "Utils/Windows.hpp"

int _mykbhit() {
    for (int keyCode = 0x11; keyCode <= 254; keyCode++) {
        if (GetAsyncKeyState(keyCode) & 0x8000) {
            return keyCode;
        }
    }

    return 0;
}
