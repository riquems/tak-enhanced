#pragma once
#include "nana_common.h"

class tab_page_patches : public nana::panel<false>
{
    std::unique_ptr<nana::place> layout;

    // Checkboxes
    std::shared_ptr<nana::checkbox> cb_noCD;
    std::shared_ptr<nana::checkbox> cb_pauseWhenUnfocused;
    std::shared_ptr<nana::checkbox> cb_offscreenFix;

    std::shared_ptr<nana::label> lbl_hpBarOptions;
    std::shared_ptr<nana::checkbox> cb_showPlayerHpBar;
    std::shared_ptr<nana::checkbox> cb_showAlliesHpBar;
    std::shared_ptr<nana::checkbox> cb_showEnemiesHpBar;
    std::shared_ptr<nana::checkbox> cb_showHpBarOnlyIfDamaged;

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

        lbl_hpBarOptions    = std::make_shared<nana::label>(*this, "HP Bar Options");
        cb_showPlayerHpBar  = std::make_shared<nana::checkbox>(*this, "Show Player");
        cb_showAlliesHpBar  = std::make_shared<nana::checkbox>(*this, "Show Allies");
        cb_showEnemiesHpBar = std::make_shared<nana::checkbox>(*this, "Show Enemies");
        cb_showHpBarOnlyIfDamaged = std::make_shared<nana::checkbox>(*this, "Only if damaged");

        cb_noCD->bgcolor(default_bgcolor);
        cb_pauseWhenUnfocused->bgcolor(default_bgcolor);
        cb_offscreenFix->bgcolor(default_bgcolor);

        lbl_hpBarOptions->bgcolor(default_bgcolor);
        cb_showPlayerHpBar->bgcolor(default_bgcolor);
        cb_showAlliesHpBar->bgcolor(default_bgcolor);
        cb_showEnemiesHpBar->bgcolor(default_bgcolor);
        cb_showHpBarOnlyIfDamaged->bgcolor(default_bgcolor);

        if (settings.NoCD) {
            cb_noCD->check(true);
        }

        if (settings.PauseWhenUnfocused) {
            cb_pauseWhenUnfocused->check(true);
        }

        if (settings.OffscreenFix) {
            cb_offscreenFix->check(true);
        }

        if (settings.showHpOptions & SHOW_PLAYER) {
            cb_showPlayerHpBar->check(true);
        }

        if (settings.showHpOptions & SHOW_ALLIES) {
            cb_showAlliesHpBar->check(true);
        }

        if (settings.showHpOptions & SHOW_ENEMIES) {
            cb_showEnemiesHpBar->check(true);
        }

        if (settings.showHpOptions & SHOW_ONLY_IF_DAMAGED) {
            cb_showHpBarOnlyIfDamaged->check(true);
        }

        layout->field("options") << *cb_noCD
                                 << *cb_offscreenFix
                                 << *cb_pauseWhenUnfocused
                                 << *lbl_hpBarOptions
                                 << *cb_showPlayerHpBar
                                 << *cb_showAlliesHpBar
                                 << *cb_showEnemiesHpBar
                                 << *cb_showHpBarOnlyIfDamaged;
        
    }

    void initialize_textboxes()
    {
        lbl_maxUnits = std::make_shared<nana::label>(*this, "Max Units:");
        sb_maxUnits = std::make_shared<nana::spinbox>(*this);
        sb_maxUnits->range(20, INT_MAX, 1);
        sb_maxUnits->value(std::to_string(settings.MaxUnits));

        lbl_pathfindingCycles = std::make_shared<nana::label>(*this, "Pathfinding Cycles:");
        sb_pathfindingCycles = std::make_shared<nana::spinbox>(*this);
        sb_pathfindingCycles->range(0, INT_MAX, 1);
        sb_pathfindingCycles->value(std::to_string(settings.PathFindingCycles));

        lbl_forcedMinRangeForMelees = std::make_shared<nana::label>(*this, "Forced minrange for Melees:");
        lbl_forcedMinRangeForMelees->bgcolor(default_bgcolor);
        sb_forcedMinRangeForMelees = std::make_shared<nana::spinbox>(*this);
        sb_forcedMinRangeForMelees->range(0, INT_MAX, 1);
        sb_forcedMinRangeForMelees->value(std::to_string(settings.ForcedMinRangeForMelees));
        sb_forcedMinRangeForMelees->enabled(false);

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

        if (settings.MeleeStuckFix) {
            cb_meleeStuckFix->check(true);
            sb_forcedMinRangeForMelees->enabled(true);
        }

        lbl_maxUnits->bgcolor(default_bgcolor);
        lbl_pathfindingCycles->bgcolor(default_bgcolor);

        layout->field("maxUnits") << *lbl_maxUnits << *sb_maxUnits;
        layout->field("pathfindingCycles") << *lbl_pathfindingCycles << *sb_pathfindingCycles;
        layout->field("forcedMinRangeForMelees") << *cb_meleeStuckFix << *lbl_forcedMinRangeForMelees << *sb_forcedMinRangeForMelees;
    }

public:
    tab_page_patches(nana::window parent) : nana::panel<false>(parent)
    {
        layout = std::make_unique<nana::place>(*this);

        layout->div("margin=15                                                                             \
                    <vert                                                                                  \
                        <weight=60                                                                         \
                            <vert options arrange=[30, 30, 30, 30, 30, 30, 30, 30]><>                      \
                        >                                                                                  \
                    >                                                                                      \
                    <weight=120 vert                                                                       \
                        <weight=150 vert                                                                   \
                            <vert maxUnits arrange=[20, 25]>                                               \
                            <vert margin=[20] pathfindingCycles arrange=[20, 25]>                          \
                            <vert margin=[35] forcedMinRangeForMelees arrange=[30, 35, 25]                 \
                            <>                                                                             \
                        >                                                                                  \
                    >");

        initialize_checkboxes();
        initialize_textboxes();

        layout->collocate();
    }

    int get_max_units()
    {
        return sb_maxUnits->to_int();
    }

    int get_pathfinding_cycles()
    {
        return sb_pathfindingCycles->to_int();
    }

    bool get_meleeStuckFix()
    {
        return cb_meleeStuckFix->checked();
    }

    int get_forced_minrange_for_melees()
    {
        return sb_forcedMinRangeForMelees->to_int();
    }

    bool get_noCD()
    {
        return cb_noCD->checked();
    }

    bool get_showPlayerHpBar()
    {
        return cb_showPlayerHpBar->checked();
    }

    bool get_showAlliesHpBar()
    {
        return cb_showAlliesHpBar->checked();
    }

    bool get_showEnemiesHpBar()
    {
        return cb_showEnemiesHpBar->checked();
    }

    bool get_showHpBarOnlyIfDamaged()
    {
        return cb_showHpBarOnlyIfDamaged->checked();
    }

    bool get_pauseWhenUnfocused()
    {
        return cb_pauseWhenUnfocused->checked();
    }

    bool get_offscreenFix()
    {
        return cb_offscreenFix->checked();
    }
};