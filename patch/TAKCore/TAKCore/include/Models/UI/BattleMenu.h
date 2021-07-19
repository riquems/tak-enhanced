#pragma once

#include "../../common.h"

class BattleMenu
{
public:
    uintptr_t* vTable;
    char padding[157];
    char** mapNamesCapitalizedStart;
    char** mapNamesCapitalizedMid;
    char** mapNamesCapitalizedEnd;
    char padding2[4];
    char** mapNamesLowerCaseStart;
    char** mapNamesLowerCaseMid;
    char** mapNamesLowerCaseEnd;
};