#include "Utils/Console.hpp"

void StartConsole()
{
    AllocConsole();
    freopen_s((FILE**)stdin, "CONIN$", "r", stdin);
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
    std::cout.clear();
    std::cin.clear();

    ConfigureConsole(600, 300, HWND_TOPMOST, false);
}

void CloseConsole()
{
    fclose(stdin);
    fclose(stdout);
    fclose(stderr);
    FreeConsole();
}

void ConfigureConsole(uint width, uint height, HWND zOrder, bool borderless)
{
    SetConsoleBufferSize(256, 400);

    RECT desktopWndRect;

    HWND desktopWnd = GetDesktopWindow();

    GetWindowRect(desktopWnd, &desktopWndRect);

    int consoleWidth = width;
    int consoleHeight = height;
    int xConsolePosition;
    int yConsolePosition;

    xConsolePosition = ((desktopWndRect.right - desktopWndRect.left) / 2) - (consoleWidth / 2);

    yConsolePosition = ((desktopWndRect.bottom - desktopWndRect.top) / 2) - (consoleHeight / 2);

    /*if (isFullscreen)
    {
        yConsolePosition = ((desktopWndRect.bottom - desktopWndRect.top) / 2) - 385;
    }*/

    HWND consoleWindow = GetConsoleWindow();

    if (borderless)
        SetWindowLongPtr(consoleWindow, GWL_STYLE, WS_POPUPWINDOW);

    // SetWindowPos(consoleWindow, zOrder, xConsolePosition, yConsolePosition, consoleWidth, consoleHeight, SWP_NOACTIVATE | SWP_NOOWNERZORDER);
    SetWindowPos(consoleWindow, zOrder, xConsolePosition, yConsolePosition, consoleWidth, consoleHeight, SWP_SHOWWINDOW);
}
