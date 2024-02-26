#pragma once
#include "TAKEnhancedLauncher/nana_common.hpp"
#include "TAKEnhancedLauncher/components/e_panel.hpp"
#include "TAKEnhancedLauncher/components/hp_bars_options_component.hpp"
#include "TAKEnhancedDll/Configs/GameConfig.hpp"
#include "TAKEnhancedLauncher/components/e_group.hpp"

class tab_page_game_options : public e_panel
{
    std::shared_ptr<GameConfig> gameConfig;
    std::shared_ptr<Logger> logger;

public:
    const std::string name = "Game Options";

    // Checkboxes
    std::shared_ptr<nana::checkbox> cb_meleeStuckFix;

    // Textboxes
    std::shared_ptr<nana::label> lbl_forcedMinRangeForMelees;
    std::shared_ptr<nana::spinbox> sb_forcedMinRangeForMelees;

    std::shared_ptr<hp_bars_options_component> hp_bars_options;

    std::shared_ptr<e_group> friendly_fire_options_group;
    std::shared_ptr<nana::checkbox> cb_selfDamage;
    std::shared_ptr<nana::checkbox> cb_allyDamage;
    std::shared_ptr<nana::checkbox> cb_allyProjectileCollision;

    std::shared_ptr<nana::group> nana_group;

    tab_page_game_options(
        nana::window parent,
        std::shared_ptr<GameConfig> gameConfig,
        std::shared_ptr<Logger> logger
    );

    void initialize();
    void draw();
    void update();
};
