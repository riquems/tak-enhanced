#include "TAKEnhancedLauncher/components/hp_bars_options_component.hpp"

hp_bars_options_component::hp_bars_options_component(
    nana::window parent,
    std::shared_ptr<GameConfig> gameConfig,
    std::shared_ptr<Logger> logger
) : e_panel(parent), gameConfig(gameConfig), logger(logger)
{
    this->initialize();
    this->draw();
    this->load();
    this->update();
}

template<typename T>
void addComboxOptions(
    std::shared_ptr<nana::combox>& combox, std::unordered_map<T, std::string> toString)
{
    for (auto& entry : toString) {
        combox->push_back(entry.second);
    }
}

void hp_bars_options_component::initialize()
{
    this->bgcolor(default_bgcolor);

    // Hp Bar Options Group Box
    cb_enableHpBarOptions = std::make_shared<nana::checkbox>(*this, nana::rectangle(0, 6, 15, 15));

    cb_enableHpBarOptions->events().checked(
        [&](nana::arg_checkbox args) {
            if (args.widget->checked()) {
                this->make_editable();
            }
            else {
                this->make_readonly();
                cb_enableHpBarOptions->enabled(true);
            }
        }
    );

    this->add_widget(cb_enableHpBarOptions);
    this->add_binding(create_checkbox_binding(cb_enableHpBarOptions, this->gameConfig->customizableHpBars.enabled));

    lbl_hpBarOptions = std::make_shared<nana::label>(*this, nana::rectangle(20, 0, 75, 30));
    lbl_hpBarOptions->caption("<bold>Hp Bar Options</>");
    lbl_hpBarOptions->format(true);
    this->add_widget(lbl_hpBarOptions);

    // Left labels
    lbl_myHpBarOptions = std::make_shared<nana::label>(*this, "Me: ");
    lbl_allyHpBarOptions = std::make_shared<nana::label>(*this, "Ally: ");
    lbl_enemyHpBarOptions = std::make_shared<nana::label>(*this, "Enemy: ");
    this->add_widget(lbl_myHpBarOptions, "leftLabels");
    this->add_widget(lbl_allyHpBarOptions, "leftLabels");
    this->add_widget(lbl_enemyHpBarOptions, "leftLabels");

    // Top labels
    lbl_showHpMode = std::make_shared<nana::label>(*this, "Show Mode");
    lbl_hpBarColorMode = std::make_shared<nana::label>(*this, "HP Color Mode");
    lbl_hpBarColor = std::make_shared<nana::label>(*this, "Color");

    this->add_widget(lbl_showHpMode, "topLabels");
    this->add_widget(lbl_hpBarColorMode, "topLabels");
    this->add_widget(lbl_hpBarColor, "topLabels");

    // Mine

    cbb_myShowHpMode = std::make_shared<nana::combox>(*this);
    cbb_myHpBarColorMode = std::make_shared<nana::combox>(*this);
    cbb_myHpBarColor = std::make_shared<nana::combox>(*this);

    cbb_myShowHpMode->events().selected(
        [&](nana::arg_combox args) {
            update_hpBarColorMode_combox(cbb_myShowHpMode, cbb_myHpBarColorMode);
        }
    );

    cbb_myHpBarColorMode->events().selected(
        [&](nana::arg_combox args) {
            update_hpBarColor_combox(cbb_myHpBarColorMode, cbb_myHpBarColor);
        }
    );

    addComboxOptions(cbb_myShowHpMode, showModeToString);
    addComboxOptions(cbb_myHpBarColorMode, colorModeToString);
    addComboxOptions(cbb_myHpBarColor, colorToString);

    this->add_widget(cbb_myShowHpMode, "myHpBarOptions");
    this->add_widget(cbb_myHpBarColorMode, "myHpBarOptions");
    this->add_widget(cbb_myHpBarColor, "myHpBarOptions");

    this->add_binding(create_combox_binding(cbb_myShowHpMode, this->gameConfig->customizableHpBars.mine.showMode));
    this->add_binding(create_combox_binding(cbb_myHpBarColorMode, this->gameConfig->customizableHpBars.mine.colorMode));
    this->add_binding(create_combox_binding(cbb_myHpBarColor, this->gameConfig->customizableHpBars.mine.color));

    // Ally

    cbb_allyShowHpMode = std::make_shared<nana::combox>(*this);
    cbb_allyHpBarColorMode = std::make_shared<nana::combox>(*this);
    cbb_allyHpBarColor = std::make_shared<nana::combox>(*this);

    cbb_allyShowHpMode->events().selected(
        [&](nana::arg_combox args) {
            update_hpBarColorMode_combox(cbb_allyShowHpMode, cbb_allyHpBarColorMode);
        }
    );

    cbb_allyHpBarColorMode->events().selected(
        [&](nana::arg_combox args) {
            update_hpBarColor_combox(cbb_allyHpBarColorMode, cbb_allyHpBarColor);
        }
    );

    addComboxOptions(cbb_allyShowHpMode, showModeToString);
    addComboxOptions(cbb_allyHpBarColorMode, colorModeToString);
    addComboxOptions(cbb_allyHpBarColor, colorToString);

    this->add_widget(cbb_allyShowHpMode, "allyHpBarOptions");
    this->add_widget(cbb_allyHpBarColorMode, "allyHpBarOptions");
    this->add_widget(cbb_allyHpBarColor, "allyHpBarOptions");

    this->add_binding(create_combox_binding(cbb_allyShowHpMode, this->gameConfig->customizableHpBars.ally.showMode));
    this->add_binding(create_combox_binding(cbb_allyHpBarColorMode, this->gameConfig->customizableHpBars.ally.colorMode));
    this->add_binding(create_combox_binding(cbb_allyHpBarColor, this->gameConfig->customizableHpBars.ally.color));

    // Enemy

    cbb_enemyShowHpMode = std::make_shared<nana::combox>(*this);
    cbb_enemyHpBarColorMode = std::make_shared<nana::combox>(*this);
    cbb_enemyHpBarColor = std::make_shared<nana::combox>(*this);

    cbb_enemyShowHpMode->events().selected(
        [&](nana::arg_combox args) {
            update_hpBarColorMode_combox(cbb_enemyShowHpMode, cbb_enemyHpBarColorMode);
        }
    );

    cbb_enemyHpBarColorMode->events().selected(
        [&](nana::arg_combox args) {
            update_hpBarColor_combox(cbb_enemyHpBarColorMode, cbb_enemyHpBarColor);
        }
    );

    addComboxOptions(cbb_enemyShowHpMode, showModeToString);
    addComboxOptions(cbb_enemyHpBarColorMode, colorModeToString);
    addComboxOptions(cbb_enemyHpBarColor, colorToString);

    this->add_widget(cbb_enemyShowHpMode, "enemyHpBarOptions");
    this->add_widget(cbb_enemyHpBarColorMode, "enemyHpBarOptions");
    this->add_widget(cbb_enemyHpBarColor, "enemyHpBarOptions");

    this->add_binding(create_combox_binding(cbb_enemyShowHpMode, this->gameConfig->customizableHpBars.enemy.showMode));
    this->add_binding(create_combox_binding(cbb_enemyHpBarColorMode, this->gameConfig->customizableHpBars.enemy.colorMode));
    this->add_binding(create_combox_binding(cbb_enemyHpBarColor, this->gameConfig->customizableHpBars.enemy.color));
}

void hp_bars_options_component::draw()
{
    this->layout->div("vert margin=[5]                     \
     <weight=30 <weight=75> topLabels arrange=[120, 130, 80]>                 \
     <weight=100                                                   \
        <weight=50 margin=[9] vert leftLabels gap=9>                          \
        <vert                                                                 \
            <margin=[5, 0, 5] myHpBarOptions    arrange=[120, 130, 80] gap=5> \
            <margin=[5, 0, 5] allyHpBarOptions  arrange=[120, 130, 80] gap=5> \
            <margin=[5, 0, 5] enemyHpBarOptions arrange=[120, 130, 80] gap=5> \
        >                                                                     \
     >");

    e_panel::draw();
}

void hp_bars_options_component::update()
{
    update_hpBarColorMode_combox(cbb_myShowHpMode, cbb_myHpBarColorMode);
    update_hpBarColorMode_combox(cbb_allyShowHpMode, cbb_allyHpBarColorMode);
    update_hpBarColorMode_combox(cbb_enemyShowHpMode, cbb_enemyHpBarColorMode);

    update_hpBarColor_combox(cbb_myHpBarColorMode, cbb_myHpBarColor);
    update_hpBarColor_combox(cbb_allyHpBarColorMode, cbb_allyHpBarColor);
    update_hpBarColor_combox(cbb_enemyHpBarColorMode, cbb_enemyHpBarColor);
}

void hp_bars_options_component::update_hpBarColorMode_combox(std::shared_ptr<nana::combox>& showMode, std::shared_ptr<nana::combox>& colorMode)
{
    if ((showMode->option() + 1) == ShowMode::Never) {
        colorMode->enabled(false);
    }
    else {
        colorMode->enabled(true);
    }
}

void hp_bars_options_component::update_hpBarColor_combox(std::shared_ptr<nana::combox>& mode, std::shared_ptr<nana::combox>& color)
{
    if ((mode->option() + 1) != ColorMode::Custom) {
        color->enabled(false);
    }
    else {
        color->enabled(true);
    }
}
