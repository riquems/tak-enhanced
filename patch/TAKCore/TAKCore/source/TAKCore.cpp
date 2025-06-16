#include "TAKCore/TAKCore.h"
#include "TAKCore/Config.h"
#include "TAKCore/Functions/Functions.h"
#include "TAKCore/Functions/FunctionsOffsets.h"
#include "TAKCore/GlobalPointers/GlobalPointers.h"
#include "TAKCore/Players/Players.hpp"
#include "TAKCore/Graphics/Graphics.hpp"

void TAKCore::init(unsigned int baseAddress) {
    TAKCore::Functions::executeCommand = (executeCommand_t) (baseAddress + FunctionsOffsets::executeCommand);
    TAKCore::Functions::GetMouseHoveredUnit = (GetMouseHoveredUnit_t) (FunctionsOffsets::getMouseHoveredUnit + baseAddress);

    TAKCore::Config::testMultiScript = (bool*)(TAKCore::Config::testMultiScriptAddress + baseAddress);
    TAKCore::Config::skipLogo = (bool*)(TAKCore::Config::skipLogoAddress + baseAddress);
    TAKCore::Config::showNetworkStats = (bool*)(TAKCore::Config::showNetworkStatsAddress + baseAddress);
    TAKCore::Config::disableCavedogVerification = (bool*)(TAKCore::Config::disableCavedogVerificationAddress + baseAddress);
    TAKCore::Config::pretendNoExpansion = (bool*)(TAKCore::Config::pretendNoExpansionAddress + baseAddress);
    TAKCore::Config::fixCursor = (bool*)(TAKCore::Config::fixCursorAddress + baseAddress);
    TAKCore::Config::disableUiPreload = (bool*)(TAKCore::Config::disableUiPreloadAddress + baseAddress);
    TAKCore::Config::noSideCulling = (bool*)(TAKCore::Config::noSideCullingAddress + baseAddress);
}

void TAKCore::initGameState(unsigned int baseAddress) {
    GlobalPointers::ptr_22D55C = (uintptr_t*)(baseAddress + GlobalPointers::ptr_22D55C_Offset);

    TAKCore::Players = (Player*)(*GlobalPointers::ptr_22D55C + TAKCore::PlayersOffset);
    TAKCore::CreateGraphicObjectFromJPG = (CreateGraphicObjectFromJPG_t)(TAKCore::CreateGraphicObjectFromJPG_Offset + baseAddress);
    TAKCore::HpBarGraphicObj = (uintptr_t*)(*GlobalPointers::ptr_22D55C + TAKCore::HpBarGraphicObj_Offset);
    TAKCore::RendererDevice = (uintptr_t*)(GlobalPointers::RendererDevice + baseAddress);
}
