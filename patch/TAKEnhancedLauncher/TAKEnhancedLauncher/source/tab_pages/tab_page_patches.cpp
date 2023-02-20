#include "TAKEnhancedLauncher/tab_pages/tab_page_patches.hpp"
#include <TAKEnhancedLauncher/binding.hpp>

tab_page_patches::tab_page_patches(nana::window parent, std::shared_ptr<GameConfig> gameConfig)
    : e_panel(parent), gameConfig(gameConfig)
{
    initialize();
    draw();
    load();
    update();
}

void tab_page_patches::initialize()
{
    cb_noCD = std::make_shared<nana::checkbox>(*this, "No CD");
    this->add_widget(cb_noCD, "options");
    this->add_binding(create_checkbox_binding(cb_noCD, this->gameConfig->noCD.enabled));

    cb_pauseWhenUnfocused = std::make_shared<nana::checkbox>(*this, "Pause when Unfocused");
    this->add_widget(cb_pauseWhenUnfocused, "options");
    this->add_binding(create_checkbox_binding(cb_pauseWhenUnfocused, this->gameConfig->pauseWhenUnfocused.enabled));

    cb_offscreenFix = std::make_shared<nana::checkbox>(*this, "Offscreen Fix");
    this->add_widget(cb_offscreenFix, "options");
    this->add_binding(create_checkbox_binding(cb_offscreenFix, this->gameConfig->offscreenFix.enabled));

    lbl_maxUnits = std::make_shared<nana::label>(*this, "Max Units:");
    this->add_widget(lbl_maxUnits, "maxUnits");

    sb_maxUnits = std::make_shared<nana::spinbox>(*this);
    sb_maxUnits->range(20, INT_MAX, 1);
    this->add_widget(sb_maxUnits, "maxUnits");
    this->add_binding(create_spinbox_binding(sb_maxUnits, this->gameConfig->maxUnits));

    cb_meleeStuckFix = std::make_shared<nana::checkbox>(*this, "Melee Stuck Fix");
    cb_meleeStuckFix->events().checked(
        [&](nana::arg_checkbox args) {
            if (cb_meleeStuckFix->checked()) {
                sb_forcedMinRangeForMelees->enabled(true);
            }
            else {
                sb_forcedMinRangeForMelees->enabled(false);
            }

        }
    );
    this->add_widget(cb_meleeStuckFix, "forcedMinRangeForMelees");
    this->add_binding(create_checkbox_binding(cb_meleeStuckFix, this->gameConfig->meleeStuckFix.enabled));

    lbl_pathfindingCycles = std::make_shared<nana::label>(*this, "Pathfinding Cycles:");
    sb_pathfindingCycles = std::make_shared<nana::spinbox>(*this);
    sb_pathfindingCycles->range(0, INT_MAX, 1);
    this->add_widget(lbl_pathfindingCycles, "pathfindingCycles");
    this->add_widget(sb_pathfindingCycles, "pathfindingCycles");
    this->add_binding(create_spinbox_binding(sb_pathfindingCycles, this->gameConfig->pathfindingCycles));

    lbl_forcedMinRangeForMelees = std::make_shared<nana::label>(*this, "Forced minrange for Melees:");
    sb_forcedMinRangeForMelees = std::make_shared<nana::spinbox>(*this);
    sb_forcedMinRangeForMelees->range(0, INT_MAX, 1);
    this->add_widget(lbl_forcedMinRangeForMelees, "forcedMinRangeForMelees");
    this->add_widget(sb_forcedMinRangeForMelees, "forcedMinRangeForMelees"); 
    this->add_binding(create_spinbox_binding(sb_forcedMinRangeForMelees, this->gameConfig->meleeStuckFix.forcedMinRangeForMelees));

}

void tab_page_patches::draw()
{
    layout->div("margin=15                                                                                                                                                                \
                <vert                                                                                                                                                                     \
                    <weight=90                                                                                                                                                            \
                        <vert options arrange=[30, 30, 30]><vert weight=140 margin=[0, 20] <vert maxUnits arrange=[20, 25]>                                                               \
                                                            <vert margin=[5] pathfindingCycles arrange=[20, 25]>><vert margin=[10] weight=120 forcedMinRangeForMelees arrange=[25, 35, 25] \
                        >                                                                                                                                                                 \
                >                                                                                                                                                                         ");
    
    e_panel::draw();
}

void tab_page_patches::update()
{
    if (cb_meleeStuckFix->checked()) {
        sb_forcedMinRangeForMelees->enabled(true);
    }
    else {
        sb_forcedMinRangeForMelees->enabled(false);
    }
}
