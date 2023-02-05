#pragma once
#include "TAKCore/Models/MapPosition.h"

class MapPositionWrapper
{
public:
    MapPosition _mapPosition;

    MapPositionWrapper(MapPosition mapPosition);

    inline int16_t value() {
        return _mapPosition.mapPosition;
    }
};
