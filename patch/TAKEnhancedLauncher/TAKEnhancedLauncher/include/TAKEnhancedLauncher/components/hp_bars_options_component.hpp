#pragma once
#include "TAKEnhancedLauncher/nana_common.hpp"
#include "TAKEnhancedLauncher/components/e_panel.hpp"
#include "TAKEnhancedDll/Configs/GameConfig.hpp"
#include "Utils/Logger.h"

class hp_bars_options_component : public e_panel
{
    std::shared_ptr<GameConfig> gameConfig;
    std::shared_ptr<Logger> logger;

public:
    const std::string name = "HP Bars";

    // Hp Bar Options
    std::shared_ptr<nana::checkbox> cb_enableHpBarOptions;
    std::shared_ptr<nana::label> lbl_hpBarOptions;
    std::shared_ptr<nana::label> lbl_myHpBarOptions;
    std::shared_ptr<nana::label> lbl_allyHpBarOptions;
    std::shared_ptr<nana::label> lbl_enemyHpBarOptions;

    std::shared_ptr<nana::label> lbl_showHpMode;
    std::shared_ptr<nana::label> lbl_hpBarColorMode;
    std::shared_ptr<nana::label> lbl_hpBarColor;

    std::shared_ptr<nana::combox> cbb_myShowHpMode;
    std::shared_ptr<nana::combox> cbb_myHpBarColorMode;
    std::shared_ptr<nana::combox> cbb_myHpBarColor;

    std::shared_ptr<nana::combox> cbb_allyShowHpMode;
    std::shared_ptr<nana::combox> cbb_allyHpBarColorMode;
    std::shared_ptr<nana::combox> cbb_allyHpBarColor;

    std::shared_ptr<nana::combox> cbb_enemyShowHpMode;
    std::shared_ptr<nana::combox> cbb_enemyHpBarColorMode;
    std::shared_ptr<nana::combox> cbb_enemyHpBarColor;

    hp_bars_options_component(nana::window parent, std::shared_ptr<GameConfig> gameConfig, std::shared_ptr<Logger> logger);

    void initialize();

    void draw();
    void update();

    void update_hpBarColorMode_combox(std::shared_ptr<nana::combox>& showMode, std::shared_ptr<nana::combox>& colorMode);
    void update_hpBarColor_combox(std::shared_ptr<nana::combox>& mode, std::shared_ptr<nana::combox>& color);
};
