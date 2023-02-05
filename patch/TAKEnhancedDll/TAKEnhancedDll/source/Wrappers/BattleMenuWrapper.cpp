#include "TAKEnhancedDll/Wrappers/BattleMenuWrapper.h"

BattleMenuWrapper::BattleMenuWrapper(BattleMenu* battleMenu)
{
    _battleMenu = battleMenu;
    loadMapVector(_mapNamesCapitalized, _battleMenu->mapNamesCapitalizedStart);
    loadMapVector(_mapNamesLowerCase, _battleMenu->mapNamesLowerCaseStart);
}

void BattleMenuWrapper::loadMapVector(std::vector<std::string>& v, char** mapNames)
{
    char** firstMap = mapNames;

    char** nextMap = firstMap;
    while (*nextMap != nullptr)
    {
        v.push_back(std::string(*nextMap));
        nextMap++;
    }
}
