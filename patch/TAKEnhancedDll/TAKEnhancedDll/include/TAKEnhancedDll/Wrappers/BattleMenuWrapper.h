#pragma once
#include "TAKEnhancedDll/common.hpp"

#include "TAKCore/Models/UI/BattleMenu.h"

class BattleMenuWrapper
{
public:
    BattleMenu* _battleMenu;

    std::vector<std::string> _mapNamesCapitalized;
    std::vector<std::string> _mapNamesLowerCase;

    BattleMenuWrapper(BattleMenu* battleMenu);

    void loadMapVector(std::vector<std::string>& v, char** mapNames);
};
