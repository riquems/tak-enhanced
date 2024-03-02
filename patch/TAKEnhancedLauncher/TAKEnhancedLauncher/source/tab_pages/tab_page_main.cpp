#include "TAKEnhancedLauncher/tab_pages/tab_page_main.hpp"

tab_page_main::tab_page_main(
    nana::window parent,
    std::shared_ptr<LauncherConfig> launcherConfig,
    std::shared_ptr<GameConfig> gameConfig,
    std::shared_ptr<Logger> logger
) : e_panel(parent),
    launcherConfig(launcherConfig),
    gameConfig(gameConfig),
    logger(logger)
{
    initialize();
    draw();
    load();
}

void tab_page_main::initialize()
{
    this->bgcolor(default_bgcolor);

    cb_enableDevMode = std::make_shared<nana::checkbox>(*this, "Enable Developer Mode");
    this->add_widget(cb_enableDevMode, "checkboxes");
    this->add_binding(create_checkbox_binding(cb_enableDevMode, this->gameConfig->developerMode.enabled));

    cb_enableMods = std::make_shared<nana::checkbox>(*this, "Enable Mods");
    this->add_widget(cb_enableMods, "checkboxes");
    this->add_binding(create_checkbox_binding(cb_enableMods, this->gameConfig->mods.enabled));

    cb_noCD = std::make_shared<nana::checkbox>(*this, "No CD");
    this->add_widget(cb_noCD, "checkboxes");
    this->add_binding(create_checkbox_binding(cb_noCD, this->gameConfig->noCD.enabled));

    cb_testMultiScript = std::make_shared<nana::checkbox>(*this, "Test Multi Script (Offline only)");
    cb_skipLogo = std::make_shared<nana::checkbox>(*this, "Skip Logo");
    cb_showNetworkStats = std::make_shared<nana::checkbox>(*this, "Show Network Stats");
    cb_disableCavedogVerification = std::make_shared<nana::checkbox>(*this, "Disable Cavedog Verification");
    cb_pretendNoExpansion = std::make_shared<nana::checkbox>(*this, "Pretend No Expansion");
    cb_fixCursor = std::make_shared<nana::checkbox>(*this, "Fix Cursor");
    cb_disableUiPreload = std::make_shared<nana::checkbox>(*this, "Disable UI Preload");
    cb_noSideCulling = std::make_shared<nana::checkbox>(*this, "No Side Culling");

    this->add_widget(cb_testMultiScript, "checkboxes");
    this->add_widget(cb_skipLogo, "checkboxes");
    this->add_widget(cb_showNetworkStats, "checkboxes");
    this->add_widget(cb_disableCavedogVerification, "checkboxes");
    this->add_widget(cb_pretendNoExpansion, "checkboxes");
    this->add_widget(cb_fixCursor, "checkboxes");
    this->add_widget(cb_disableUiPreload, "checkboxes");
    this->add_widget(cb_noSideCulling, "checkboxes");

    this->add_binding(create_checkbox_binding(cb_testMultiScript, this->gameConfig->testMultiScript.enabled));
    this->add_binding(create_checkbox_binding(cb_skipLogo, this->gameConfig->skipLogo.enabled));
    this->add_binding(create_checkbox_binding(cb_showNetworkStats, this->gameConfig->showNetworkStats.enabled));
    this->add_binding(create_checkbox_binding(cb_disableCavedogVerification, this->gameConfig->disableCavedogVerification.enabled));
    this->add_binding(create_checkbox_binding(cb_pretendNoExpansion, this->gameConfig->pretendNoExpansion.enabled));
    this->add_binding(create_checkbox_binding(cb_fixCursor, this->gameConfig->fixCursor.enabled));
    this->add_binding(create_checkbox_binding(cb_disableUiPreload, this->gameConfig->disableUiPreload.enabled));
    this->add_binding(create_checkbox_binding(cb_noSideCulling, this->gameConfig->noSideCulling.enabled));

    cb_pauseWhenUnfocused = std::make_shared<nana::checkbox>(*this, "Pause when Unfocused");
    this->add_widget(cb_pauseWhenUnfocused, "checkboxes");
    this->add_binding(create_checkbox_binding(cb_pauseWhenUnfocused, this->gameConfig->pauseWhenUnfocused.enabled));

    cb_offscreenFix = std::make_shared<nana::checkbox>(*this, "Offscreen Fix");
    this->add_widget(cb_offscreenFix, "checkboxes");
    this->add_binding(create_checkbox_binding(cb_offscreenFix, this->gameConfig->offscreenFix.enabled));

    this->mod_loader = std::make_shared<e_mod_loader>(
        *this,
        this->launcherConfig,
        this->gameConfig,
        this->logger
    );
    mod_loader->on_state_changed_callback = [&]() {
        this->on_state_changed();
    };
    this->add_widget(this->mod_loader, "mod_loader");

    cb_enableMods->events().checked(
        [&](nana::arg_checkbox args) {
            if (args.widget->checked()) {
                this->mod_loader->make_editable();
            } else {
                this->mod_loader->make_readonly();
            }
        }
    );

    lbl_maxUnits = std::make_shared<nana::label>(*this, "Max Units:");
    this->add_widget(lbl_maxUnits, "maxUnits");
    sb_maxUnits = std::make_shared<nana::spinbox>(*this);
    sb_maxUnits->range(20, INT_MAX, 1);
    this->add_widget(sb_maxUnits, "maxUnits");
    this->add_binding(create_spinbox_binding(sb_maxUnits, this->gameConfig->maxUnits));

    lbl_pathfindingCycles = std::make_shared<nana::label>(*this, "Pathfinding Cycles:");
    sb_pathfindingCycles = std::make_shared<nana::spinbox>(*this);
    sb_pathfindingCycles->range(0, INT_MAX, 1);
    this->add_widget(lbl_pathfindingCycles, "pathfindingCycles");
    this->add_widget(sb_pathfindingCycles, "pathfindingCycles");
    this->add_binding(create_spinbox_binding(sb_pathfindingCycles, this->gameConfig->pathfindingCycles));

    this->grp_modifiers = std::make_shared<e_group>(*this, "Modifiers");
    this->grp_modifiers->bgcolor(default_bgcolor);
    this->add_widget(this->grp_modifiers, "modifiers");

    this->grp_modifiers->div("margin=[5, 10] vert modifiers gap=5 arrange=[15, 25, repeated]");

    lbl_manaStorage = std::make_shared<nana::label>(*this->grp_modifiers, "Mana Storage:");

    this->grp_modifiers->add_widget(this->lbl_manaStorage, "");
    (*this->grp_modifiers)["modifiers"] << *this->lbl_manaStorage;

    sb_manaStorage = std::make_shared<nana::spinbox>(*this->grp_modifiers);
    sb_manaStorage->range(0.0, FLT_MAX, 0.1);

    this->grp_modifiers->add_widget(this->sb_manaStorage, "");
    this->grp_modifiers->add_binding(create_spinbox_binding(this->sb_manaStorage, this->gameConfig->modifiers.manaStorage));
    (*this->grp_modifiers)["modifiers"] << *this->sb_manaStorage;

    lbl_manaIncome = std::make_shared<nana::label>(*this->grp_modifiers, "Mana Income:");

    this->grp_modifiers->add_widget(this->lbl_manaIncome, "");
    (*this->grp_modifiers)["modifiers"] << *this->lbl_manaIncome;

    sb_manaIncome = std::make_shared<nana::spinbox>(*this->grp_modifiers);
    sb_manaIncome->range(0.0, FLT_MAX, 0.1);

    this->grp_modifiers->add_widget(this->sb_manaIncome, "");
    this->grp_modifiers->add_binding(create_spinbox_binding(this->sb_manaIncome, this->gameConfig->modifiers.manaIncome));
    (*this->grp_modifiers)["modifiers"] << *this->sb_manaIncome;

    lbl_unitSight = std::make_shared<nana::label>(*this->grp_modifiers, "Unit Sight:");

    this->grp_modifiers->add_widget(this->lbl_unitSight, "");
    (*this->grp_modifiers)["modifiers"] << *this->lbl_unitSight;

    sb_unitSight = std::make_shared<nana::spinbox>(*this->grp_modifiers);
    sb_unitSight->range(0.0, FLT_MAX, 0.1);

    this->grp_modifiers->add_widget(this->sb_unitSight, "");
    this->grp_modifiers->add_binding(create_spinbox_binding(this->sb_unitSight, this->gameConfig->modifiers.unitSight));
    (*this->grp_modifiers)["modifiers"] << *this->sb_unitSight;

    lbl_workerTime = std::make_shared<nana::label>(*this->grp_modifiers, "Worker Time:");

    this->grp_modifiers->add_widget(this->lbl_workerTime, "");
    (*this->grp_modifiers)["modifiers"] << *this->lbl_workerTime;

    sb_workerTime = std::make_shared<nana::spinbox>(*this->grp_modifiers);
    sb_workerTime->range(0.0, FLT_MAX, 0.1);

    this->grp_modifiers->add_widget(this->sb_workerTime, "");
    this->grp_modifiers->add_binding(create_spinbox_binding(this->sb_workerTime, this->gameConfig->modifiers.workerTime));
    (*this->grp_modifiers)["modifiers"] << *this->sb_workerTime;

    this->grp_modifiers->load();
}

void tab_page_main::commit()
{
    e_panel::commit();
    this->grp_modifiers->commit();
    this->mod_loader->commit();
}

void tab_page_main::draw()
{
    this->layout->div(
        "margin=15   \
        <horizontal \
            <vert weight=200 arrange=[30, repeated] checkboxes>\
            |                           \
            <margin=[0, 15] mod_loader> \
            |\
            <vert weight=140 gap=20                                \
                <vert weight=90 \
                    <vert maxUnits arrange=[20, 25]>                                          \
                    <vert margin=[5] pathfindingCycles arrange=[20, 25]>                      \
                >\
                <vert margin=[20] modifiers>\
            >\
        >"
    );

    e_panel::draw();
}

void tab_page_main::reset()
{
    this->mod_loader->reset();
}

void tab_page_main::reload()
{
    this->reset();
    this->load();
    this->mod_loader->load();
}
