#include "TAKEnhancedLauncher/tab_pages/tab_page_game_options.hpp"
#include <TAKEnhancedLauncher/binding.hpp>

tab_page_game_options::tab_page_game_options(
    nana::window parent,
    std::shared_ptr<GameConfig> gameConfig,
    std::shared_ptr<Logger> logger
) : e_panel(parent), gameConfig(gameConfig), logger(logger)
{
    initialize();
    draw();
    load();
    update();
}

void tab_page_game_options::initialize()
{
    this->bgcolor(default_bgcolor);

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

    lbl_forcedMinRangeForMelees = std::make_shared<nana::label>(*this, "Forced minrange for Melees:");
    sb_forcedMinRangeForMelees = std::make_shared<nana::spinbox>(*this);
    sb_forcedMinRangeForMelees->range(0, INT_MAX, 1);
    this->add_widget(lbl_forcedMinRangeForMelees, "forcedMinRangeForMelees");
    this->add_widget(sb_forcedMinRangeForMelees, "forcedMinRangeForMelees");
    this->add_binding(create_spinbox_binding(sb_forcedMinRangeForMelees, this->gameConfig->meleeStuckFix.forcedMinRangeForMelees));

    this->hp_bars_options = std::make_shared<hp_bars_options_component>(*this, this->gameConfig, this->logger);
    this->add_widget(this->hp_bars_options, "hp_bars_options");

    // Friendly Fire Options
    this->friendly_fire_options_group = std::make_shared<e_group>(*this, "Friendly Fire");
    this->friendly_fire_options_group->bgcolor(default_bgcolor);
    this->add_widget(this->friendly_fire_options_group, "friendly_fire_options");

    this->friendly_fire_options_group->div("margin=[5, 10] vert friendly_fire_options arrange=[30, repeated]");

    this->cb_selfDamage = std::make_shared<nana::checkbox>(*this->friendly_fire_options_group, "Self Damage");
    this->friendly_fire_options_group->add_widget(this->cb_selfDamage, "");
    this->friendly_fire_options_group->add_binding(create_checkbox_binding(this->cb_selfDamage, this->gameConfig->friendlyFire.selfDamage));
    (*this->friendly_fire_options_group)["friendly_fire_options"] << *this->cb_selfDamage;

    this->cb_allyDamage = std::make_shared<nana::checkbox>(*this->friendly_fire_options_group, "Ally Damage");
    this->friendly_fire_options_group->add_widget(this->cb_allyDamage, "");
    this->friendly_fire_options_group->add_binding(create_checkbox_binding(this->cb_allyDamage, this->gameConfig->friendlyFire.allyDamage));
    (*this->friendly_fire_options_group)["friendly_fire_options"] << *this->cb_allyDamage;

    this->cb_allyProjectileCollision = std::make_shared<nana::checkbox>(*this->friendly_fire_options_group, "Ally Projectile Collision");
    this->friendly_fire_options_group->add_widget(this->cb_allyProjectileCollision, "");
    this->friendly_fire_options_group->add_binding(create_checkbox_binding(this->cb_allyProjectileCollision, this->gameConfig->friendlyFire.allyProjectileCollision));
    (*this->friendly_fire_options_group)["friendly_fire_options"] << *this->cb_allyProjectileCollision;
}

void tab_page_game_options::draw()
{
    layout->div(
    "margin=15                                                                                                                              \
    <vert gap=20                                                                                                                            \
        <weight=200 gap=20                                                                                                                  \
            <margin=5 weight=180 friendly_fire_options> | <margin=5 weight=450 hp_bars_options> | <vert margin=5 min=120 forcedMinRangeForMelees arrange=[25, 35, 25]> \
        >                                                                                                                                   \
    >");

    e_panel::draw();
}

void tab_page_game_options::update()
{
    if (cb_meleeStuckFix->checked()) {
        sb_forcedMinRangeForMelees->enabled(true);
    }
    else {
        sb_forcedMinRangeForMelees->enabled(false);
    }
}

void tab_page_game_options::load() {
    this->friendly_fire_options_group->load();

    e_panel::load();
}

void tab_page_game_options::reload() {
    this->friendly_fire_options_group->reload();

    e_panel::reload();
}

void tab_page_game_options::make_readonly() {
    this->friendly_fire_options_group->make_readonly();

    e_panel::make_readonly();
}

void tab_page_game_options::make_editable() {
    this->friendly_fire_options_group->make_editable();

    e_panel::make_editable();
}
