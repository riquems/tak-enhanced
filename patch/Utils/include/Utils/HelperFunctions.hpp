#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <chrono>
#include <unordered_map>
#include <algorithm>

DWORD getProcessId(std::string processName);
DWORD getProcessBaseAddress(std::string processName);

bool isKeyDown(int keyCode);
void StartConsole();

void SetConsoleBufferSize(SHORT x, SHORT y);

namespace HelperFunctions
{
    long long GetMilliseconds();
}

void toggleBoolean(bool& boolean);

bool str_contains_str(std::string& str1, std::string& str2);
bool str_equals_str(const char* str1, const char* str2);
bool str_equals_str(std::string& str1, std::string& str2);
bool str_equals_str(std::string& str1, const std::string& str2);
bool str_equals_str(const std::string& str1, const std::string& str2);

const char* boolean_to_str(bool& boolean);

bool str_to_boolean(const char* str);
bool str_to_boolean(std::string str);

unsigned int str_to_uint(const char* str);
unsigned int str_to_uint(std::string str);

bool vector_has_str(std::vector<std::string>& vector, std::string str);

/* DWORD GetMainThreadId(); */
