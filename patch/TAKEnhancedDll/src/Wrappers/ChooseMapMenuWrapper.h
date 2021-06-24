#pragma once
#include "common.h"

#include "ChooseMapMenu.h"

class ChooseMapMenuWrapper
{
public:
	ChooseMapMenu* _chooseMapMenu;

	std::vector<std::string> _mapNamesCapitalized;
	std::vector<std::string> _mapNamesLowerCase;

	ChooseMapMenuWrapper(ChooseMapMenu* chooseMapMenu)
	{
		_chooseMapMenu = chooseMapMenu;
		loadMapVector(_mapNamesCapitalized, _chooseMapMenu->mapNamesCapitalizedStart);
		loadMapVector(_mapNamesLowerCase, _chooseMapMenu->mapNamesLowerCaseStart);
	}

	void loadMapVector(std::vector<std::string>& v, char** mapNames)
	{
		char** firstMap = mapNames;

		char** nextMap = firstMap;
		while (*nextMap != nullptr)
		{
			v.push_back(std::string(*nextMap));
			nextMap++;
		}
	}
};