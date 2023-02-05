#pragma once
#include "Windows.h"
#include "TAKCore/GlobalPointers/GlobalPointers.h"
#include "TAKCore/Models/Player.h"
#include "TAKCore/Models/HapiFile.h"
#include "TAKEnhancedDll/GlobalState.hpp"

DWORD GetAbsoluteAddress(DWORD);

namespace GameFunctionsExtensions
{
    std::vector<HapiFile*> GetLoadedHapiFiles();
}

