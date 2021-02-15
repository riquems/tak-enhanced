#pragma once

class PlayerViewModel;
class Unit;

class Player
{
public:
	bool initialized;
	char padding[3];
	uint8_t playerId;
	char padding2[3];
	char padding3[72];
	PlayerViewModel* playerViewModel;
	char name[32];
	Unit* firstUnit;
	Unit* lastUnit;
	char padding4[36];
	uint16_t kills;
	uint16_t losses;
	uint32_t score;
	char padding5[64];
	uint16_t unitsCount;
	char padding6[1];
	uint8_t byte_004E4F7B;
	char padding7[36];
};