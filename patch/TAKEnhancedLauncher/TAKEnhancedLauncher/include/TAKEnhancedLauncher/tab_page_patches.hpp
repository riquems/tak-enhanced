#pragma once
#include "TAKEnhancedLauncher/nana_common.hpp"
#include "TAKEnhancedDll/Configs/GameConfig.hpp"

class tab_page_patches : public nana::panel<false>
{
    std::shared_ptr<GameConfig> gameConfig;

public:
    std::unique_ptr<nana::place> layout;

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
    
    void initialize_checkboxes();

    void initialize_textboxes();

    tab_page_patches(nana::window parent, std::shared_ptr<GameConfig> gameConfig);

    void initialize();

    void draw();
    void load();
    void update();
    void save();
    void reload();

    void make_editable();
    void make_readonly();
};
