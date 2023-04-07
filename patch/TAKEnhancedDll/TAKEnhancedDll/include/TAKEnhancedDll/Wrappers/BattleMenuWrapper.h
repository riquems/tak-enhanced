#pragma once
#include "TAKEnhancedDll/common.hpp"

#include "TAKCore/Models/UI/BattleMenu.h"

class BattleMenuWrapper
{
public:
    BattleMenu* battleMenu;

    std::vector<std::string> mapNamesCapitalized;
    std::vector<std::string> mapNamesLowerCase;

    BattleMenuWrapper(BattleMenu* battleMenu);

    void loadMapVector(std::vector<std::string>& v, char** begin, char** end);
};
