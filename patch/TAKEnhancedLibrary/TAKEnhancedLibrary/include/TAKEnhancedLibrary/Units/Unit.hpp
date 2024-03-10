#pragma once
#include "TAKEnhancedLibrary/common.hpp"
#include "TAKCore/Models/Unit.h"
#include "TAKEnhancedLibrary/Players/Player.hpp"

namespace TAKEnhancedLibrary
{
    struct Unit
    {
        TAKCore::Unit* raw;

        Unit(TAKCore::Unit*);

        inline bool isInitialized() {
            return this->raw != nullptr;
        }

        inline std::string name() {
            return this->raw->unitInfo->name;
        }

        inline uint16_t hp() {
            return this->raw->currentHealth;
        }

        inline uint32_t maxHp() {
            return this->raw->unitInfo->maxDamage;
        }

        inline std::shared_ptr<Player> player() {
            return std::make_shared<Player>(this->raw->player);
        }

        inline bool selected() {
            return this->raw->walking && 0b00010000;
        }

        inline bool isABuilding() {
            return this->raw->movementHandler == nullptr;
        }

        inline bool isBeingBuilt() {
            return this->raw->buildTimeLeft != 0;
        }

        inline uint16_t direction() {
            return this->raw->direction;
        }

        inline uint16_t direction(uint16_t direction) {
            return this->raw->direction = direction;
        }

        inline bool isFlying() {
            return this->raw->walking & 0b10;
        }

        inline int16_t getXpos() {
            return this->raw->xMapPosition.mapPosition;
        }

        inline int16_t getYpos() {
            return this->raw->yMapPosition.mapPosition;
        }

        inline int16_t getZpos() {
            return this->raw->zMapPosition.mapPosition;
        }

        inline void setXpos(int16_t value) {
            this->raw->xMapPosition.mapPosition = value;
        }

        inline void setYpos(int16_t value) {
            this->raw->yMapPosition.mapPosition = value;
        }

        inline void setZpos(int16_t value) {
            this->raw->zMapPosition.mapPosition = value;
        }
    };
}
