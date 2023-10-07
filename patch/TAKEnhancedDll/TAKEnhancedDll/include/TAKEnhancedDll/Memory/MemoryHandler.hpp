#pragma once
#include <TAKEnhancedDll/common.hpp>
#include <TAKEnhancedDll/Memory/Memory.hpp>
#include <TAKEnhancedDll/Memory/ShellCode.hpp>
#include "TAKEnhancedDll/GlobalState.hpp"

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
        VirtualProtectEx(hProcess, (LPVOID)targetAddress, sizeof(value), PAGE_READWRITE, &oldProtect);

        WriteProcessMemory(hProcess, (LPVOID)targetAddress, &value, sizeof(value), NULL);

        VirtualProtectEx(hProcess, (LPVOID)targetAddress, sizeof(value), oldProtect, &oldProtect);
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

    void debugShellCode(ShellCode shellCode);

    void writeShellCode(ShellCode shellCode);

    unsigned int toLittleEndian(unsigned int hex);

    std::string DWORDtoStr(DWORD hex);

    std::string BYTEtoStr(BYTE hex);

    void writeJMP(Memory at, DWORD jumpTo);

    void writeShortJMP(Memory at, DWORD jumpTo);

    void insertFunctionCall(DWORD functionAddress, DWORD startAddressOffSet);

    void insertOpCode(OpCode opCode, DWORD at);

    void writeJZ(Memory at, DWORD jumpTo);

    void fillWithNOPs(Memory memory);
    void fillWithNOPs(DWORD startAddress, DWORD endAddress);
}
