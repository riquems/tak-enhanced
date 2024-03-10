#include "TAKEnhancedLibrary/Units/Units.hpp"
#include "TAKEnhancedLibrary/Players/Players.hpp"
#include "TAKEnhancedDll/Commands/RotateBuildingCommandHandler.hpp"
#include "TAKEnhancedDll/GlobalState.hpp"

RotateBuildingCommandHandler::RotateBuildingCommandHandler() {
    this->disabledUnits = { "Gate", "Lodestone", "Divine Lodestone", "Mana Refinery", "Mana Amplifier" };
}

void RotateBuildingCommandHandler::_handle(const Command& command) {
    handle(dynamic_cast<const RotateBuildingCommand&>(command));
}

void RotateBuildingCommandHandler::handle(const RotateBuildingCommand& command) {
    if (gameWrapper->isInWriteMode())
        return;

    auto& step = command.params.step;
    auto& orientation = command.params.orientation;

    auto unit = TAKEnhancedLibrary::GetMouseHoveredUnit();

    if (unit == nullptr)
        return;

    if (!currentGameConfig->developerMode.enabled) {
        if (!TAKEnhancedLibrary::IsMe(unit->player())) {
            return;
        }

        if (!unit->isABuilding()) {
            return;
        }

        if (!unit->isBeingBuilt()) {
            return;
        }

        bool disabledUnit = dky::contains(this->disabledUnits,
            [&](const std::string& disabledUnit) {
                return unit->name() == disabledUnit;
            }
        );

        if (disabledUnit) {
            return;
        }
    }

    if (orientation == RotateOrientation::Clockwise) {
        unit->direction(unit->direction() - (step * 182.045));
    }
    else {
        unit->direction(unit->direction() + (step * 182.045));
    }
}
