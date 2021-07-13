#pragma once

#include "../Context.h"

#include <map>
#include "Models/Unit.h"
#include "Models/UnitInfo.h"

std::unordered_map<Unit*, UnitInfo*> unitsWithDisabledAura;

void ToggleSelectedUnitAura()
{
    Unit* unit = gameWrapper->getSelectedUnit(baseAddress);

    if (unitsWithDisabledAura.find(unit)) {
        

        unitsWithDisabledAura.erase(unit);

        return;
    }

    UnitInfo* oldUnitInfo = unit->unitInfo;

    UnitInfo* unitInfoWithDisabledAura;


    unit->unitInfo = unitInfoWithDisabledAura;

    unitsWithDisabledAura.push_back(std::pair<Unit*, UnitInfo*>(unit, oldUnitInfo));
}