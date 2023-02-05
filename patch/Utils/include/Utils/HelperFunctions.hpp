#pragma once
#pragma pack(push, 8)
#include <Windows.h>
#pragma pack(pop)
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
#include "openssl/aes.h"
#include "openssl/md5.h"

DWORD getProcessId(std::string processName);
DWORD getProcessBaseAddress(std::string processName);

bool isKeyDown(int keyCode);

void SetConsoleBufferSize(SHORT x, SHORT y);

namespace HelperFunctions
{
    long long GetMilliseconds();
}

void toggleBoolean(bool& boolean);

bool str_contains_str(const std::string& str1,const std::string& str2);
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

std::vector<std::string> split_str(char* str, const char* token);
std::vector<std::string> split_str(std::string str, const char* token);
/* DWORD GetMainThreadId(); */
