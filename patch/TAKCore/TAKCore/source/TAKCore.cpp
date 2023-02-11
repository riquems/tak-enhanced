#include "TAKCore/TAKCore.h"
#include "TAKCore/Functions/Functions.h"
#include "TAKCore/Functions/FunctionsOffsets.h"

void TAKCore::init(unsigned int baseAddress) {
    TAKCore::Functions::executeCommand = (executeCommand_t) (baseAddress + FunctionsOffsets::executeCommand);
}
