#pragma once
#include "common.h"

#include "BattleMenu.h"

class BattleMenuWrapper
{
public:
	BattleMenu* _battleMenu;

	std::vector<std::string> _mapNamesCapitalized;
	std::vector<std::string> _mapNamesLowerCase;

	BattleMenuWrapper(BattleMenu* battleMenu)
	{
		_battleMenu = battleMenu;
		loadMapVector(_mapNamesCapitalized, _battleMenu->mapNamesCapitalizedStart);
		loadMapVector(_mapNamesLowerCase, _battleMenu->mapNamesLowerCaseStart);
	}

	void loadMapVector(std::vector<std::string>& v, char** mapNames)
	{
		char** firstMap = mapNames;

		char** nextMap = firstMap;
		while (nextMap != nullptr)
		{
			v.push_back(std::string(*nextMap));
			nextMap++;
		}
	}
};