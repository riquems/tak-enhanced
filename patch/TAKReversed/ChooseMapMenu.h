#pragma once
#include "common.h"

#include "KingdomsDialog.h"

class ChooseMapMenu
{
public:
	DWORD* vTable;
	char padding[314];
	char** mapNamesCapitalizedStart;
	char** mapNamesCapitalizedMid;
	char** mapNamesCapitalizedEnd;
	char padding2[4];
	char** mapNamesLowerCaseStart;
	char** mapNamesLowerCaseMid;
	char** mapNamesLowerCaseEnd;
};


