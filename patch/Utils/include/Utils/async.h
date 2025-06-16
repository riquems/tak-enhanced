#pragma once

#include <Windows.h>
#include <iostream>

void runAsync(LPTHREAD_START_ROUTINE fn) {
    HANDLE threadHandle;
    DWORD threadId;

    threadHandle = CreateThread(NULL, 0, fn, NULL, 0, &threadId);
    if (threadHandle == NULL) {
        std::cout << "Failed to create thread.\n";
        return;
    }

    CloseHandle(threadHandle);
}
