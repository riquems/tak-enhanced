#pragma once
#include "TAKEnhancedDll/Launcher/nana_common.hpp"

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
    
    void initialize_checkboxes()
    {
        cb_noCD = std::make_shared<nana::checkbox>(*this, "No CD");
        cb_pauseWhenUnfocused = std::make_shared<nana::checkbox>(*this, "Pause when Unfocused");
        cb_offscreenFix = std::make_shared<nana::checkbox>(*this, "Offscreen Fix");

        cb_noCD->bgcolor(default_bgcolor);
        cb_pauseWhenUnfocused->bgcolor(default_bgcolor);
        cb_offscreenFix->bgcolor(default_bgcolor);
    }

    void initialize_textboxes()
    {
        lbl_maxUnits = std::make_shared<nana::label>(*this, "Max Units:");
        sb_maxUnits = std::make_shared<nana::spinbox>(*this);
        sb_maxUnits->range(20, INT_MAX, 1);

        lbl_pathfindingCycles = std::make_shared<nana::label>(*this, "Pathfinding Cycles:");
        sb_pathfindingCycles = std::make_shared<nana::spinbox>(*this);
        sb_pathfindingCycles->range(0, INT_MAX, 1);

        lbl_forcedMinRangeForMelees = std::make_shared<nana::label>(*this, "Forced minrange for Melees:");
        lbl_forcedMinRangeForMelees->bgcolor(default_bgcolor);
        sb_forcedMinRangeForMelees = std::make_shared<nana::spinbox>(*this);
        sb_forcedMinRangeForMelees->range(0, INT_MAX, 1);

        cb_meleeStuckFix = std::make_shared<nana::checkbox>(*this, "Melee Stuck Fix");
        cb_meleeStuckFix->bgcolor(default_bgcolor);

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

        lbl_maxUnits->bgcolor(default_bgcolor);
        lbl_pathfindingCycles->bgcolor(default_bgcolor);
    }

    tab_page_patches(nana::window parent, std::shared_ptr<GameConfig> gameConfig)
        : nana::panel<false>(parent), gameConfig(gameConfig)
    {
        initialize();
        draw();
        load();
        update();
    }

    void initialize()
    {
        initialize_checkboxes();
        initialize_textboxes();
    }

    void draw()
    {
        layout = std::make_unique<nana::place>(*this);

        layout->div("margin=15                                                                                                                                                                \
                    <vert                                                                                                                                                                     \
                        <weight=90                                                                                                                                                            \
                            <vert options arrange=[30, 30, 30]><vert weight=140 margin=[0, 20] <vert maxUnits arrange=[20, 25]>                                                               \
                                                               <vert margin=[5] pathfindingCycles arrange=[20, 25]>><vert margin=[10] weight=120 forcedMinRangeForMelees arrange=[25, 35, 25] \
                            >                                                                                                                                                                 \
                    >                                                                                                                                                                         ");
    
    
        layout->field("options") << *cb_noCD
                                 << *cb_offscreenFix
                                 << *cb_pauseWhenUnfocused;

        layout->field("maxUnits") << *lbl_maxUnits << *sb_maxUnits;
        layout->field("pathfindingCycles") << *lbl_pathfindingCycles << *sb_pathfindingCycles;
        layout->field("forcedMinRangeForMelees") << *cb_meleeStuckFix << *lbl_forcedMinRangeForMelees << *sb_forcedMinRangeForMelees;

        layout->collocate();
    }

    void load()
    {
        cb_noCD              ->check(this->gameConfig->noCD.enabled);
        cb_pauseWhenUnfocused->check(this->gameConfig->pauseWhenUnfocused.enabled);
        cb_offscreenFix->check(this->gameConfig->offscreenFix.enabled);

        sb_maxUnits->value(std::to_string(this->gameConfig->maxUnits));
        sb_pathfindingCycles->value(std::to_string(this->gameConfig->pathfindingCycles));

        cb_meleeStuckFix->check(this->gameConfig->meleeStuckFix.enabled);
        sb_forcedMinRangeForMelees->value(std::to_string(this->gameConfig->meleeStuckFix.forcedMinRangeForMelees));
    }

    void update()
    {
        if (cb_meleeStuckFix->checked()) {
            sb_forcedMinRangeForMelees->enabled(true);
        }
        else {
            sb_forcedMinRangeForMelees->enabled(false);
        }
    }

    void save()
    {
        this->gameConfig->maxUnits = sb_maxUnits->to_int();
        this->gameConfig->pathfindingCycles = sb_pathfindingCycles->to_int();
        this->gameConfig->meleeStuckFix.forcedMinRangeForMelees = sb_forcedMinRangeForMelees->to_int();

        this->gameConfig->noCD.enabled = cb_noCD->checked();
        this->gameConfig->meleeStuckFix.enabled = cb_meleeStuckFix->checked();
        this->gameConfig->offscreenFix.enabled = cb_offscreenFix->checked();
        this->gameConfig->pauseWhenUnfocused.enabled = cb_pauseWhenUnfocused->checked();
    }

    void reload()
    {
        load();
    }

    void make_editable()
    {
        // Checkboxes
        cb_noCD              ->enabled(true);
        cb_pauseWhenUnfocused->enabled(true);
        cb_offscreenFix      ->enabled(true);

        // Textboxes
        sb_maxUnits         ->enabled(true);
        sb_pathfindingCycles->enabled(true);

        // Melee Stuck Fix
        cb_meleeStuckFix          ->enabled(true);
        sb_forcedMinRangeForMelees->enabled(true);
    }

    void make_readonly()
    {
        // Checkboxes
        cb_noCD              ->enabled(false);
        cb_pauseWhenUnfocused->enabled(false);
        cb_offscreenFix      ->enabled(false);

        // Textboxes
        sb_maxUnits         ->enabled(false);
        sb_pathfindingCycles->enabled(false);

        // Melee Stuck Fix
        cb_meleeStuckFix          ->enabled(false);
        sb_forcedMinRangeForMelees->enabled(false);
    }
};