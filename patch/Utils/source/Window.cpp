#include "Utils/Window.hpp"
#include "Utils/Windows.hpp"

bool isFullscreen = false;

HWND GetThisWindow(std::string name) {
    HWND nextWindow = FindWindowA(NULL, name.c_str());
    HWND window = nullptr;

    DWORD processId;
    while (nextWindow != NULL) {
        GetWindowThreadProcessId(nextWindow, &processId);

        if (processId == GetCurrentProcessId()) {
            window = nextWindow;
            break;
        }

        nextWindow = FindWindowExA(NULL, nextWindow, NULL, name.c_str());
    }

    return window;
}

void ToggleFullscreen()
{
    HWND handle = FindWindowA(NULL, "Kingdoms");

    if (!isFullscreen)
    {
        RECT desktopWndRect;

        HWND desktopWnd = GetDesktopWindow();

        GetWindowRect(desktopWnd, &desktopWndRect);

        int width = desktopWndRect.right;
        int height = desktopWndRect.bottom;

        SetWindowPos(handle, 0, 0, 0, width, height, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

        isFullscreen = true;
    }
    else {
        int width = 640;
        int height = 480;

        SetWindowPos(handle, 0, 0, 0, width, height, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

        isFullscreen = false;
    }
}
