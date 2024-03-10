#include "TAKEnhancedLibrary/Units/Units.hpp"
#include "TAKEnhancedLibrary/Players/Players.hpp"
#include "TAKCore/Functions/Functions.h"
#include <ranges>

using namespace TAKEnhancedLibrary;

std::shared_ptr<Unit> TAKEnhancedLibrary::GetMouseHoveredUnit() {
    auto unit = TAKCore::Functions::GetMouseHoveredUnit();

    if (unit == nullptr)
        return nullptr;

    return std::make_shared<Unit>(unit);
}

std::vector<std::shared_ptr<Unit>> TAKEnhancedLibrary::GetSelectedUnits() {
    auto currentPlayer = GetCurrentPlayer();

    auto units = currentPlayer->units();

    auto result = units | std::ranges::views::filter(
        [](const std::shared_ptr<Unit>& unit) {
            return unit->selected();
        }
    );

    return std::vector<std::shared_ptr<Unit>>(result.begin(), result.end());
}
