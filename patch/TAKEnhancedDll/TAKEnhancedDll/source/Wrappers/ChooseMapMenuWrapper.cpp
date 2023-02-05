#include "TAKEnhancedDll/Wrappers/ChooseMapMenuWrapper.h"

ChooseMapMenuWrapper::ChooseMapMenuWrapper(ChooseMapMenu* chooseMapMenu)
{
    _chooseMapMenu = chooseMapMenu;
    loadMapVector(_mapNamesCapitalized, _chooseMapMenu->mapNamesCapitalizedStart);
    loadMapVector(_mapNamesLowerCase, _chooseMapMenu->mapNamesLowerCaseStart);
}

void ChooseMapMenuWrapper::loadMapVector(std::vector<std::string>& v, char** mapNames)
{
    char** firstMap = mapNames;

    char** nextMap = firstMap;
    while (*nextMap != nullptr)
    {
        v.push_back(std::string(*nextMap));
        nextMap++;
    }
}
