#include "Utils/Console.hpp"

void StartConsole(uint width, uint height, HWND zOrder, bool borderless) {
    AllocConsole();
    freopen_s((FILE**)stdin, "CONIN$", "r", stdin);
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
    std::cout.clear();
    std::cin.clear();

    ConfigureConsole(width, height, zOrder, borderless);
}

void CloseConsole()
{
    fclose(stdin);
    fclose(stdout);
    fclose(stderr);
    FreeConsole();
}

int titleBarHeight = 40;

void ConfigureConsole(uint width, uint height, HWND zOrder, bool borderless)
{
    SetConsoleBufferSize(256, 400);

    RECT desktopWndRect;

    HWND desktopWnd = GetDesktopWindow();

    GetWindowRect(desktopWnd, &desktopWndRect);

    int consoleWidth = width;
    int consoleHeight = titleBarHeight + height;
    int xConsolePosition;
    int yConsolePosition;

    xConsolePosition = ((desktopWndRect.right - desktopWndRect.left) / 2) - (consoleWidth / 2);

    yConsolePosition = ((desktopWndRect.bottom - desktopWndRect.top) / 2) - (consoleHeight / 2);

    /*if (isFullscreen)
    {
        yConsolePosition = ((desktopWndRect.bottom - desktopWndRect.top) / 2) - 385;
    }*/

    HWND consoleWindow = GetConsoleWindow();

    if (borderless) {
        SetWindowLongPtr(consoleWindow, GWL_STYLE, WS_POPUPWINDOW);
        consoleHeight -= titleBarHeight;
    }

    // SetWindowPos(consoleWindow, zOrder, xConsolePosition, yConsolePosition, consoleWidth, consoleHeight, SWP_NOACTIVATE | SWP_NOOWNERZORDER);
    SetWindowPos(consoleWindow, zOrder, xConsolePosition, yConsolePosition, consoleWidth, consoleHeight, SWP_SHOWWINDOW);
}
