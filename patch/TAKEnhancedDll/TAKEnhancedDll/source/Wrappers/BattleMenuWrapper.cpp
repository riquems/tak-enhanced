#include "TAKEnhancedDll/Wrappers/BattleMenuWrapper.h"

BattleMenuWrapper::BattleMenuWrapper(BattleMenu* battleMenu)
{
    this->battleMenu = battleMenu;

    loadMapVector(
        this->mapNamesCapitalized,
        this->battleMenu->mapNamesCapitalizedStart,
        this->battleMenu->mapNamesCapitalizedEnd
    );

    loadMapVector(
        this->mapNamesLowerCase,
        this->battleMenu->mapNamesLowerCaseStart,
        this->battleMenu->mapNamesLowerCaseEnd
    );
}

void BattleMenuWrapper::loadMapVector(std::vector<std::string>& v, char** begin, char** end)
{
    for (int i = 0; begin[i] != *end; i++) {
        v.push_back(std::string(begin[i]));
    }
}