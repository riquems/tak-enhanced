#pragma once

extern "C" bool isFullscreen = false;

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

int _mykbhit()
{
    for (int keyCode = 1; keyCode <= 254; keyCode++) {
        if (GetAsyncKeyState(keyCode) & 0x8000) {
            return keyCode;
        }
    }

    return 0;
}
