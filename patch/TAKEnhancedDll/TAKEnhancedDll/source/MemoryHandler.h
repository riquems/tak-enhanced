#pragma once
#include "Context.h"

class Memory
{
public:
    DWORD startAddress = 0;
    DWORD endAddress = 0;
    DWORD length = 0;

    Memory() {}
    Memory(DWORD _startAddress, DWORD _endAddress)
    {
        startAddress = baseAddress + _startAddress;
        endAddress = baseAddress + _endAddress;

        length = endAddress - startAddress;
    }
};

class ShellCode
{
public:
    std::vector<BYTE> shellCode;
    Memory place;

    ShellCode() {}
    ShellCode(std::string shellCodeStr, DWORD startAddress)
    {
        shellCode = stringToShellCode(shellCodeStr);
        place = Memory(startAddress, startAddress + shellCode.size());
    }
    ShellCode(std::string shellCodeStr, Memory _place)
    {
        place = _place;

        DWORD unusedSpace = (place.length - (DWORD) (shellCodeStr.size() / 2));

        for (unsigned int i = 0; i < unusedSpace; i++) {
            shellCodeStr.append("90");
        }

        shellCode = stringToShellCode(shellCodeStr);
    }

    static std::vector<BYTE> stringToShellCode(std::string shellCodeStr)
    {
        std::vector<BYTE> shellCode;

        for (unsigned int i = 0; i < shellCodeStr.size(); i += 2) {
            std::string byteStr(shellCodeStr.substr(i, 2));

            BYTE byte = (BYTE) strtoul(byteStr.c_str(), NULL, 16);

            shellCode.push_back(byte);
        }

        return shellCode;
    }

    BYTE* data()
    {
        return shellCode.data();
    }

    DWORD startAddress()
    {
        return place.startAddress;
    }

    DWORD endAddress()
    {
        return place.endAddress;
    }

    DWORD placeLength()
    {
        return place.length;
    }
    
    unsigned int size()
    {
        return shellCode.size() * sizeof(BYTE);
    }
};

namespace MemoryHandler
{
    enum class OpCode {
        RETN = 0xC3,
        PUSH_EAX = 0x50,
        PUSH_ECX = 0x51,
        PUSH_EDX = 0x52,
        PUSH_EBX = 0x53,
        PUSH_ESP = 0x54,
        PUSH_EBP = 0x55,
        PUSH_ESI = 0x56,
        PUSH_EDI = 0x57,
        POP_EBX = 0x5B,
        POP_EBP = 0x5D,
        POP_ESI = 0x5E,
        POP_EDI = 0x5F,
        NOP = 0x90
    };

    template <typename T>
    void write(T value, DWORD offset)
    {
        DWORD targetAddress = baseAddress + offset;

        DWORD oldProtect;
        VirtualProtectEx(hProcess, (LPVOID) targetAddress, sizeof(value), PAGE_READWRITE, &oldProtect);

        WriteProcessMemory(hProcess, (LPVOID) targetAddress, &value, sizeof(value), NULL);

        VirtualProtectEx(hProcess, (LPVOID) targetAddress, sizeof(value), oldProtect, nullptr);
    }

    template <typename T>
    T getRelativeAddress(DWORD first, DWORD second)
    {
        return second - first - sizeof(T) - sizeof(BYTE);
    }

    template <typename T>
    T getRelativeAddress(DWORD first, DWORD second, DWORD instructionSize)
    {
        DWORD operandSize = sizeof(T);
        return second - first - operandSize - instructionSize;
    }

    void debugShellCode(ShellCode shellCode)
    {
        logger.log("ShellCode data: ");
        for (size_t i = 0; i < shellCode.shellCode.size(); i++) {
            logger.log("%x", shellCode.shellCode.at(i));
        }

        logger.log("ShellCode place length: %lu", shellCode.placeLength());
        logger.log("ShellCode size: %lu", shellCode.size());
    }

    void writeShellCode(ShellCode shellCode)
    {
        DWORD oldProtect;
        VirtualProtectEx(hProcess, (LPVOID) shellCode.startAddress(), shellCode.placeLength(), PAGE_READWRITE, &oldProtect);

        WriteProcessMemory(hProcess, (LPVOID) shellCode.startAddress(), shellCode.data(), shellCode.size(), NULL);

        VirtualProtectEx(hProcess, (LPVOID) shellCode.startAddress(), shellCode.placeLength(), oldProtect, nullptr);
    }

    unsigned int toLittleEndian(unsigned int hex)
    {
        return ((hex << 24) & 0xFF000000) |
            ((hex << 8) & 0x00FF0000) |
            ((hex >> 8) & 0x0000FF00) |
            ((hex >> 24) & 0x000000FF);
    }

    std::string DWORDtoStr(DWORD hex)
    {
        std::stringstream ss;
        ss << std::hex << std::setfill('0') << std::setw(8) << toLittleEndian(hex);

        return ss.str();
    }

    std::string BYTEtoStr(BYTE hex)
    {
        std::stringstream ss;
        ss << std::hex << std::setfill('0') << std::setw(2) << (DWORD) hex;

        return ss.str();
    }

    void writeJMP(Memory at, DWORD jumpTo)
    {
        jumpTo += baseAddress;
        std::string relativeAddressStr = DWORDtoStr(getRelativeAddress<DWORD>(at.startAddress, jumpTo));

        ShellCode JMP_ShellCode("E9" + relativeAddressStr, at);
        writeShellCode(JMP_ShellCode);
    }

    void writeShortJMP(Memory at, DWORD jumpTo)
    {
        jumpTo += baseAddress;
        std::string relativeAddressStr = BYTEtoStr(getRelativeAddress<BYTE>(at.startAddress, jumpTo));

        ShellCode ShortJMP_ShellCode("EB" + relativeAddressStr, at);
        writeShellCode(ShortJMP_ShellCode);
    }

    void insertFunctionCall(DWORD functionAddress, DWORD startAddressOffSet)
    {
        DWORD relativeAddress = getRelativeAddress<DWORD>(startAddressOffSet + baseAddress, functionAddress);

        ShellCode shellCode("E8" + DWORDtoStr(relativeAddress), startAddressOffSet);

        writeShellCode(shellCode);
    }

    void insertOpCode(OpCode opCode, DWORD at)
    {
        ShellCode shellCode(BYTEtoStr(static_cast<BYTE>(opCode)), at);
        writeShellCode(shellCode);
    }

    void writeJZ(Memory at, DWORD jumpTo)
    {
        jumpTo += baseAddress;
        std::string relativeAddressStr = DWORDtoStr(getRelativeAddress<DWORD>(at.startAddress, jumpTo, 2));

        ShellCode JMP_ShellCode("0F84" + relativeAddressStr, at);
        writeShellCode(JMP_ShellCode);
    }

    void fillWithNOPs(Memory memory)
    {
        std::string shellCodeStr("");

        for (DWORD i = memory.startAddress; i < memory.endAddress; i++)
        {
            shellCodeStr.append("90");
        }

        ShellCode NOPsShellCode(shellCodeStr, memory);
        writeShellCode(NOPsShellCode);
    }

    void fillWithNOPs(DWORD startAddress, DWORD endAddress)
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
}