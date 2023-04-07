#pragma once

#include "../../common.h"

class BattleMenu
{
public:
    uintptr_t* vTable;
    char padding[157];
    char** mapNamesCapitalizedStart;
    char** mapNamesCapitalizedEnd;
    char** unknown1;
    char padding2[4];
    char** mapNamesLowerCaseStart;
    char** mapNamesLowerCaseEnd;
    char** unknown2;
};