#pragma once
#include "TAKEnhancedLauncher/nana_common.hpp"
#include "TAKEnhancedLauncher/tab_pages/e_panel.hpp"
#include "TAKEnhancedDll/Configs/GameConfig.hpp"

class tab_page_patches : public e_panel
{
    std::shared_ptr<GameConfig> gameConfig;

public:
    const std::string name = "Patches";

    // Checkboxes
    std::shared_ptr<nana::checkbox> cb_noCD;
    std::shared_ptr<nana::checkbox> cb_pauseWhenUnfocused;
    std::shared_ptr<nana::checkbox> cb_offscreenFix;

    std::shared_ptr<nana::checkbox> cb_meleeStuckFix;

    // Textboxes
    std::shared_ptr<nana::label> lbl_maxUnits;
    std::shared_ptr<nana::spinbox> sb_maxUnits;

    std::shared_ptr<nana::label> lbl_pathfindingCycles;
    std::shared_ptr<nana::spinbox> sb_pathfindingCycles;

    std::shared_ptr<nana::label> lbl_forcedMinRangeForMelees;
    std::shared_ptr<nana::spinbox> sb_forcedMinRangeForMelees;
    
    tab_page_patches(nana::window parent, std::shared_ptr<GameConfig> gameConfig);

    void initialize();
    void draw();
    void update();
};
