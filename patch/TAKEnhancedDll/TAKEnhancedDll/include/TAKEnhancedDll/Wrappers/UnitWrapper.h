#pragma once
#include "TAKCore/Models/Unit.h"

class UnitWrapper
{
public:
    Unit* unit = nullptr;

    UnitWrapper();
    UnitWrapper(Unit* unit);

    inline bool isInitialized() {
        return this->unit != nullptr;
    }

    inline std::string name() {
        return this->unit->unitInfo->name;
    }

    inline Player* player() {
        return this->unit->player;
    }

    inline bool isABuilding() {
        return this->unit->movementHandler == nullptr;
    }

    inline bool isBeingBuilt() {
        return this->unit->buildTimeLeft != 0;
    }

    inline uint16_t direction() {
        return this->unit->direction;
    }

    inline uint16_t direction(uint16_t direction) {
        return this->unit->direction = direction;
    }

    inline bool isFlying() {
        return this->unit->walking & 0b10;
    }

    inline int16_t getXpos() {
        return this->unit->xMapPosition.mapPosition;
    }

    inline int16_t getYpos() {
        return this->unit->yMapPosition.mapPosition;
    }

    inline int16_t getZpos() {
        return this->unit->zMapPosition.mapPosition;
    }

    inline void setXpos(int16_t value) {
        this->unit->xMapPosition.mapPosition = value;
    }

    inline void setYpos(int16_t value) {
        this->unit->yMapPosition.mapPosition = value;
    }

    inline void setZpos(int16_t value) {
        this->unit->zMapPosition.mapPosition = value;
    }
};
