#pragma once

#include "MapPosition.h"

class MapPositionWrapper
{
public:
	MapPosition _mapPosition;

	MapPositionWrapper(MapPosition mapPosition) : _mapPosition(mapPosition) {}

	inline int16_t value() {
		return _mapPosition.mapPosition;
	}
};