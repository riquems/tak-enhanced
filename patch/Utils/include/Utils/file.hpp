#pragma once

#include "common.h"

namespace file
{
     std::optional<std::string> readString(std::string path, uint offset) {
         std::ifstream fs(path);

         if (!fs.is_open()) {
             return std::optional<std::string>();
         }

         std::string str;

         fs.seekg(offset);
         std::getline(fs, str, '\0');
         fs.close();

         return str;
    }
}
