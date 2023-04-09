#pragma once

namespace TAKCore
{
    namespace Config
    {
        constexpr unsigned int useMapScriptAddress = 0x24185D;
        extern bool* useMapScript;

        constexpr unsigned int skipLogoAddress = 0x24181E;
        extern bool* skipLogo;

        constexpr unsigned int showNetworkStatsAddress = 0x241826;
        extern bool* showNetworkStats;

        constexpr unsigned int disableCavedogVerificationAddress = 0x241828;
        extern bool* disableCavedogVerification;

        constexpr unsigned int pretendNoExpansionAddress = 0x241829;
        extern bool* pretendNoExpansion;

        constexpr unsigned int fixCursorAddress = 0x241A4C;
        extern bool* fixCursor;

        constexpr unsigned int disableUiPreloadAddress = 0x21A036;
        extern bool* disableUiPreload;

        constexpr unsigned int noSideCullingAddress = 0x21A035;
        extern bool* noSideCulling;
    }
}
