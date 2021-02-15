#pragma once
#include "common.h"

#include "Unit.h"
#include "Player.h"

class PlayerWrapper
{
public:
	Player* _player;
	std::vector<Unit*> units;

	PlayerWrapper(Player* player)
	{
		_player = player;

		Unit* firstUnit = _player->firstUnit;

		Unit* nextUnit = firstUnit;
		while (nextUnit != _player->lastUnit)
		{
			units.push_back(nextUnit);
			nextUnit++;
		}
	}
};