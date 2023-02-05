#include "TAKEnhancedDll/Changes/ToggleUnitsAuras.hpp"

#include <unordered_map>
#include <TAKCore/Models/Unit.h>
#include <TAKEnhancedDll/Wrappers/GameWrapper.h>

std::unordered_map<Unit*, UnitInfo*> unitsWithDisabledAura;

void ToggleSelectedUnitAura()
{
    /*Unit* unit = gameWrapper->getSelectedUnit(baseAddress);

    if (unitsWithDisabledAura.find(unit)) {
        

        unitsWithDisabledAura.erase(unit);

        return;
    }

    UnitInfo* oldUnitInfo = unit->unitInfo;

    UnitInfo* unitInfoWithDisabledAura;


    unit->unitInfo = unitInfoWithDisabledAura;

    unitsWithDisabledAura.push_back(std::pair<Unit*, UnitInfo*>(unit, oldUnitInfo));*/
}