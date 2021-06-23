#pragma once
#include "common.h"

#include "UnitWrapper.h"
#include "Player.h"

class PlayerWrapper
{
public:
	Player* _player;
	std::vector<UnitWrapper> units;

	PlayerWrapper(Player* player)
	{
		_player = player;

		Unit* firstUnit = _player->firstUnit;

		Unit* nextUnit = firstUnit;
		while (nextUnit != _player->lastUnit)
		{
			units.push_back(UnitWrapper(nextUnit));
			nextUnit++;
		}
	}
};