#include "TAKEnhancedDll/Wrappers/ChooseMapMenuWrapper.h"

ChooseMapMenuWrapper::ChooseMapMenuWrapper(ChooseMapMenu* chooseMapMenu)
{
    this->chooseMapMenu = chooseMapMenu;

    loadMapVector(
        this->mapNamesCapitalized,
        this->chooseMapMenu->mapNamesCapitalizedStart,
        this->chooseMapMenu->mapNamesCapitalizedEnd
    );

    loadMapVector(
        this->mapNamesLowerCase,
        this->chooseMapMenu->mapNamesLowerCaseStart,
        this->chooseMapMenu->mapNamesLowerCaseEnd
    );
}

void ChooseMapMenuWrapper::loadMapVector(std::vector<std::string>& v, char** begin, char** end)
{
    for (int i = 0; begin[i] != *end; i++) {
        v.push_back(std::string(begin[i]));
    }
}
