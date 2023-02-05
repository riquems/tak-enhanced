#include "Utils/CopyToClipboard.hpp"
#pragma pack(push, 8)
#include <Windows.h>
#pragma pack(pop)

void copyToClipboard(const std::string& text) {
    OpenClipboard(GetDesktopWindow());
    EmptyClipboard();
    HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, text.size() + 1);
    memcpy(GlobalLock(hg), text.c_str(), text.size() + 1);
    GlobalUnlock(hg);
    SetClipboardData(CF_TEXT, hg);
    CloseClipboard();
    GlobalFree(hg);
}
