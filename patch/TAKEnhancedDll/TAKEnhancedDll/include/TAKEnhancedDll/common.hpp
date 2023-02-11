#pragma once
#include <exception>
#include <any>
#include <regex>

#include <map>
#include <unordered_map>
#include <string>

#include <fstream>
#include <filesystem>

#include "dky/std.hpp"
#include "Utils/json.hpp"
#include "TAKCore/TAKCore.h"

typedef unsigned int uint;

using json = nlohmann::json;
namespace TAK = TAKCore;
