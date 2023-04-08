#include "TAKEnhancedLauncher/tab_pages/tab_page_mods.hpp"

tab_page_mods::tab_page_mods(nana::window parent, std::shared_ptr<GameConfig> gameConfig, std::shared_ptr<Logger> logger) :
    e_panel(parent), gameConfig(gameConfig), logger(logger)
{
    initialize();
    draw();
    load();
}

void tab_page_mods::initialize()
{
    cb_enableDevMode = std::make_shared<nana::checkbox>(*this, "Enable Developer Mode");
    this->add_widget(cb_enableDevMode, "checkboxes");
    this->add_binding(create_checkbox_binding(cb_enableDevMode, this->gameConfig->developerMode.enabled));

    cb_enableMods = std::make_shared<nana::checkbox>(*this, "Enable Mods");
    this->add_widget(cb_enableMods, "checkboxes");
    this->add_binding(create_checkbox_binding(cb_enableMods, this->gameConfig->mods.enabled));

    this->mod_loader = std::make_shared<e_mod_loader>(
        *this, this->gameConfig, this->logger
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

void tab_page_mods::commit()
{
    e_panel::commit();
    this->mod_loader->commit();
}

void tab_page_mods::draw()
{
    this->layout->div(
        "margin=15 vert   \
        <weight=30 checkboxes>    \
        <                         \
            mod_loader            \
        >"
    );

    e_panel::draw();
}

void tab_page_mods::reset()
{
    this->mod_loader->reset();
}

void tab_page_mods::reload()
{
    this->reset();
    this->load();
    this->mod_loader->load();
}
