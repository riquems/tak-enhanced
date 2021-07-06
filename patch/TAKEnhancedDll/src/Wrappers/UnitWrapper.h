#pragma once

#include "Models/Unit.h"

class UnitWrapper
{
public:
    Unit* _unit = nullptr;

    UnitWrapper() {}
    UnitWrapper(Unit* unit) : _unit(unit) {}

    inline bool isInitialized() {
        return _unit != nullptr;
    }

    inline bool isFlying() {
        return _unit->walking & 0b10;
    }

    inline int16_t getXpos() {
        return _unit->xMapPosition.mapPosition;
    }

    inline int16_t getYpos() {
        return _unit->yMapPosition.mapPosition;
    }

    inline int16_t getZpos() {
        return _unit->zMapPosition.mapPosition;
    }

    inline void setXpos(int16_t value) {
        _unit->xMapPosition.mapPosition = value;
    }

    inline void setYpos(int16_t value) {
        _unit->yMapPosition.mapPosition = value;
    }

    inline void setZpos(int16_t value) {
        _unit->zMapPosition.mapPosition = value;
    }
};
