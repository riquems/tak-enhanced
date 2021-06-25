#pragma once
#include "MapPosition.h"



class Unit;
class NavGoal;

class Mission
{
	// members                   // offsets
public:
	char padding[14];			 // 0x000
	Unit* unit;					 // 0x00E
	char padding2[4];			 // 0x012
	Unit* targetUnit;			 // 0x016
	char padding3[4];			 // 0X01A
	Mission* mission;			 // 0x01E
	MapPosition xDestination;	 // 0X022
	char padding4[4];			 // 0x026
	MapPosition zDestination;	 // 0X02A
	char padding5[32];			 // 0x02E
	uint32_t distanceFromTarget; // 0x04E
	char padding6[28];			 // 0x052
	NavGoal* navGoal;			 // 0x06E
};


