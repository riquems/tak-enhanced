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
    cb_enableDevMode = std::make_shared<nana::checkbox>(*this, "Enable Developer Mode");
    this->add_widget(cb_enableDevMode, "checkboxes");
    this->add_binding(create_checkbox_binding(cb_enableDevMode, this->gameConfig->developerMode.enabled));

    cb_enableMods = std::make_shared<nana::checkbox>(*this, "Enable Mods");
    this->add_widget(cb_enableMods, "checkboxes");
    this->add_binding(create_checkbox_binding(cb_enableMods, this->gameConfig->mods.enabled));

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
}

void tab_page_main::commit()
{
    e_panel::commit();
    this->mod_loader->commit();
}

void tab_page_main::draw()
{
    this->layout->div(
        "margin=15   \
        <horizontal \
            <vert arrange=[30, repeated] vert weight=30% checkboxes>\
            |                           \
            <mod_loader>                \
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
