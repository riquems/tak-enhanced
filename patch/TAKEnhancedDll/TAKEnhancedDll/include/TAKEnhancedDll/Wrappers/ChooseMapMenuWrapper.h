#pragma once
#include "TAKEnhancedDll/common.hpp"
#include "TAKCore/Models/UI/ChooseMapMenu.h"

class ChooseMapMenuWrapper
{
public:
    ChooseMapMenu* chooseMapMenu;

    std::vector<std::string> mapNamesCapitalized;
    std::vector<std::string> mapNamesLowerCase;

    ChooseMapMenuWrapper(ChooseMapMenu* chooseMapMenu);

    void loadMapVector(std::vector<std::string>& v, char** begin, char** end);
};
