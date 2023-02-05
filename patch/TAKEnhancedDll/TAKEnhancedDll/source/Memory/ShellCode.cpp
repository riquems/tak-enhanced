#include "TAKEnhancedDll/Memory/ShellCode.hpp"

ShellCode::ShellCode() {}
ShellCode::ShellCode(std::string shellCodeStr, DWORD startAddress)
{
    shellCode = stringToShellCode(shellCodeStr);
    place = Memory(startAddress, startAddress + shellCode.size());
}
ShellCode::ShellCode(std::string shellCodeStr, Memory _place)
{
    place = _place;

    DWORD unusedSpace = (place.length - (DWORD)(shellCodeStr.size() / 2));

    for (unsigned int i = 0; i < unusedSpace; i++) {
        shellCodeStr.append("90");
    }

    shellCode = stringToShellCode(shellCodeStr);
}

std::vector<BYTE> ShellCode::stringToShellCode(std::string shellCodeStr)
{
    std::vector<BYTE> shellCode;

    for (unsigned int i = 0; i < shellCodeStr.size(); i += 2) {
        std::string byteStr(shellCodeStr.substr(i, 2));

        BYTE byte = (BYTE)strtoul(byteStr.c_str(), NULL, 16);

        shellCode.push_back(byte);
    }

    return shellCode;
}

BYTE* ShellCode::data()
{
    return shellCode.data();
}

DWORD ShellCode::startAddress()
{
    return place.startAddress;
}

DWORD ShellCode::endAddress()
{
    return place.endAddress;
}

DWORD ShellCode::placeLength()
{
    return place.length;
}

unsigned int ShellCode::size()
{
    return shellCode.size() * sizeof(BYTE);
}
