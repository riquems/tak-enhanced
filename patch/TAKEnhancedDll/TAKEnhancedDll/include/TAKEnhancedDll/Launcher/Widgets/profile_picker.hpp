#pragma once

#include "../nana_common.h"
#include "TAKEnhancedDll/Settings.hpp"

class profile_picker : public nana::combox
{

public:
    profile_picker(std::shared_ptr<Settings>);
};