#pragma once
#include "../../common.h"

class Gadget;

class KingdomsPanel
{
public:
    uintptr_t* vTable;
    char padding[28];
    Gadget* children;
};


