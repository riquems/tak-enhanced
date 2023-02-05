#pragma once
#include "TAKEnhancedDll/common.hpp"
#include "TAKCore/Models/UI/ChooseMapMenu.h"

class ChooseMapMenuWrapper
{
public:
    ChooseMapMenu* _chooseMapMenu;

    std::vector<std::string> _mapNamesCapitalized;
    std::vector<std::string> _mapNamesLowerCase;

    ChooseMapMenuWrapper(ChooseMapMenu* chooseMapMenu);

    void loadMapVector(std::vector<std::string>& v, char** mapNames);
};
