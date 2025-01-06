#include "TAKCore/Units/Units.hpp"
#include "TAKCore/GlobalPointers/GlobalPointers.h"

using namespace TAKCore;

namespace TAKCore
{
    Unit* GetUnits() {
        return *(Unit**)(*GlobalPointers::ptr_22D55C + TAKCore::UnitsOffset);
    }
}
