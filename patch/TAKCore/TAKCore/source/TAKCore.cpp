#include "TAKCore/TAKCore.h"
#include "TAKCore/Config.h"
#include "TAKCore/Functions/Functions.h"
#include "TAKCore/Functions/FunctionsOffsets.h"

void TAKCore::init(unsigned int baseAddress) {
    TAKCore::Functions::executeCommand = (executeCommand_t) (baseAddress + FunctionsOffsets::executeCommand);

    TAKCore::Config::useMapScript = (bool*)(TAKCore::Config::useMapScriptAddress + baseAddress);
    TAKCore::Config::skipLogo = (bool*)(TAKCore::Config::skipLogoAddress + baseAddress);
    TAKCore::Config::showNetworkStats = (bool*)(TAKCore::Config::showNetworkStatsAddress + baseAddress);
    TAKCore::Config::disableCavedogVerification = (bool*)(TAKCore::Config::disableCavedogVerificationAddress + baseAddress);
    TAKCore::Config::pretendNoExpansion = (bool*)(TAKCore::Config::pretendNoExpansionAddress + baseAddress);
    TAKCore::Config::fixCursor = (bool*)(TAKCore::Config::fixCursorAddress + baseAddress);
    TAKCore::Config::disableUiPreload = (bool*)(TAKCore::Config::disableUiPreloadAddress + baseAddress);
    TAKCore::Config::noSideCulling = (bool*)(TAKCore::Config::noSideCullingAddress + baseAddress);
}
