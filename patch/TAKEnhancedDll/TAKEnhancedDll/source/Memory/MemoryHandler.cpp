#include "TAKEnhancedDll/Memory/MemoryHandler.hpp"

void MemoryHandler::debugShellCode(ShellCode shellCode)
{
    logger->debug("ShellCode data: ");
    for (size_t i = 0; i < shellCode.shellCode.size(); i++) {
        logger->debug("%x", shellCode.shellCode.at(i));
    }

    logger->debug("ShellCode place length: %lu", shellCode.placeLength());
    logger->debug("ShellCode size: %lu", shellCode.size());
}

void MemoryHandler::writeShellCode(ShellCode shellCode)
{
    DWORD oldProtect;
    VirtualProtectEx(hProcess, (LPVOID)shellCode.startAddress(), shellCode.placeLength(), PAGE_READWRITE, &oldProtect);

    WriteProcessMemory(hProcess, (LPVOID)shellCode.startAddress(), shellCode.data(), shellCode.size(), NULL);

    VirtualProtectEx(hProcess, (LPVOID)shellCode.startAddress(), shellCode.placeLength(), oldProtect, &oldProtect);
}

unsigned int MemoryHandler::toLittleEndian(unsigned int hex)
{
    return ((hex << 24) & 0xFF000000) |
        ((hex << 8) & 0x00FF0000) |
        ((hex >> 8) & 0x0000FF00) |
        ((hex >> 24) & 0x000000FF);
}

std::string MemoryHandler::DWORDtoStr(DWORD hex)
{
    std::stringstream ss;
    ss << std::hex << std::setfill('0') << std::setw(8) << toLittleEndian(hex);

    return ss.str();
}

std::string MemoryHandler::BYTEtoStr(BYTE hex)
{
    std::stringstream ss;
    ss << std::hex << std::setfill('0') << std::setw(2) << (DWORD)hex;

    return ss.str();
}

void MemoryHandler::writeJMP(DWORD at, DWORD jumpTo)
{
    std::string relativeAddressStr = DWORDtoStr(getRelativeAddress<DWORD>(at + baseAddress, jumpTo));

    ShellCode JMP_ShellCode("E9" + relativeAddressStr, at);
    writeShellCode(JMP_ShellCode);
}

void MemoryHandler::writeJMP(Memory at, DWORD jumpTo)
{
    jumpTo += baseAddress;
    std::string relativeAddressStr = DWORDtoStr(getRelativeAddress<DWORD>(at.startAddress, jumpTo));

    ShellCode JMP_ShellCode("E9" + relativeAddressStr, at);
    writeShellCode(JMP_ShellCode);
}

void MemoryHandler::writeShortJMP(Memory at, DWORD jumpTo)
{
    jumpTo += baseAddress;
    std::string relativeAddressStr = BYTEtoStr(getRelativeAddress<BYTE>(at.startAddress, jumpTo));

    ShellCode ShortJMP_ShellCode("EB" + relativeAddressStr, at);
    writeShellCode(ShortJMP_ShellCode);
}

void MemoryHandler::insertFunctionCall(DWORD functionAddress, DWORD startAddressOffSet)
{
    DWORD relativeAddress = getRelativeAddress<DWORD>(startAddressOffSet + baseAddress, functionAddress);

    ShellCode shellCode("E8" + DWORDtoStr(relativeAddress), startAddressOffSet);

    writeShellCode(shellCode);
}

void MemoryHandler::insertOpCode(OpCode opCode, DWORD at)
{
    ShellCode shellCode(BYTEtoStr(static_cast<BYTE>(opCode)), at);
    writeShellCode(shellCode);
}

void MemoryHandler::writeJZ(DWORD at, DWORD jumpTo)
{
    jumpTo += baseAddress;
    std::string relativeAddressStr = DWORDtoStr(getRelativeAddress<DWORD>(at, jumpTo, 2));

    ShellCode JMP_ShellCode("0F84" + relativeAddressStr, at);
    writeShellCode(JMP_ShellCode);
}

void MemoryHandler::writeShortJNZ(DWORD at, DWORD jumpTo)
{
    jumpTo += baseAddress;
    std::string relativeAddressStr = BYTEtoStr(getRelativeAddress<BYTE>(at, jumpTo));

    ShellCode JMP_ShellCode("75" + relativeAddressStr, at);
    writeShellCode(JMP_ShellCode);
}

void MemoryHandler::fillWithNOPs(Memory memory)
{
    std::string shellCodeStr("");

    for (DWORD i = memory.startAddress; i < memory.endAddress; i++)
    {
        shellCodeStr.append("90");
    }

    ShellCode NOPsShellCode(shellCodeStr, memory);
    writeShellCode(NOPsShellCode);
}

void MemoryHandler::fillWithNOPs(DWORD startAddress, DWORD endAddress)
{
    Memory memory(startAddress, endAddress);

    std::string shellCodeStr("");

    for (DWORD i = memory.startAddress; i < memory.endAddress; i++)
    {
        shellCodeStr.append("90");
    }

    ShellCode NOPsShellCode(shellCodeStr, memory);
    writeShellCode(NOPsShellCode);
}
