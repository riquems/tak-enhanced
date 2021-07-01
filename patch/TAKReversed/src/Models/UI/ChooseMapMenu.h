#pragma once
#include "../../common.h"

class ChooseMapMenu
{
public:
    uintptr_t* vTable;
    char padding[314];
    char** mapNamesCapitalizedStart;
    char** mapNamesCapitalizedMid;
    char** mapNamesCapitalizedEnd;
    char padding2[4];
    char** mapNamesLowerCaseStart;
    char** mapNamesLowerCaseMid;
    char** mapNamesLowerCaseEnd;
};


