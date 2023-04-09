#pragma once
#include "TAKEnhancedLauncher/nana_common.hpp"
#include "TAKEnhancedLauncher/tab_pages/e_panel.hpp"
#include "TAKEnhancedLauncher/Components/e_mod_loader.hpp"
#include "TAKEnhancedDll/Configs/GameConfig.hpp"
#include "TAKEnhancedDll/Configs/LauncherConfig.hpp"
#include "TAKEnhancedDll/Utils.hpp"
#include "Utils/Logger.h"
#include "TAKEnhancedDll/Wrappers/Defs.h"

class tab_page_general : public e_panel
{
    std::shared_ptr<LauncherConfig> launcherConfig;
    std::shared_ptr<GameConfig> gameConfig;
    std::shared_ptr<Logger> logger;

    std::vector<std::string> modFiles;

    std::shared_ptr<nana::checkbox> cb_enableDevMode;
    std::shared_ptr<nana::checkbox> cb_enableMods;

    std::shared_ptr<nana::checkbox> cb_useMapScript;
    std::shared_ptr<nana::checkbox> cb_skipLogo;
    std::shared_ptr<nana::checkbox> cb_showNetworkStats;
    std::shared_ptr<nana::checkbox> cb_disableCavedogVerification;
    std::shared_ptr<nana::checkbox> cb_pretendNoExpansion;
    std::shared_ptr<nana::checkbox> cb_fixCursor;
    std::shared_ptr<nana::checkbox> cb_disableUiPreload;
    std::shared_ptr<nana::checkbox> cb_noSideCulling;

    std::shared_ptr<e_mod_loader> mod_loader;

public:
    tab_page_general(
        nana::window parent,
        std::shared_ptr<LauncherConfig> launcherConfig,
        std::shared_ptr<GameConfig> gameConfig,
        std::shared_ptr<Logger> logger
    );

    void initialize();

    void commit();
    void draw();
    void reset();
    void reload();
};
