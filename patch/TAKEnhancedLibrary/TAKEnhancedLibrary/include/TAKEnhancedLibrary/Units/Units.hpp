#include "TAKEnhancedLibrary/common.hpp"
#include "TAKEnhancedLibrary/Units/Unit.hpp"

namespace TAKEnhancedLibrary
{
    std::shared_ptr<Unit> GetMouseHoveredUnit();
    std::vector<std::shared_ptr<Unit>> GetSelectedUnits();
}
