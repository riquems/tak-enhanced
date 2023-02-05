#pragma once

#include <algorithm>
#include <unordered_map>
#include <filesystem>
#include <regex>

#include "Utils/HelperFunctions.hpp"

template <typename T1, typename T2>
std::unordered_map<T2, T1> build_reversed_map(const std::unordered_map<T1, T2>& map1);
std::vector<std::string> get_files_from_path(std::filesystem::path& path, const char* extension);
std::pair<std::string, std::string> getKeyValue(std::string line);
