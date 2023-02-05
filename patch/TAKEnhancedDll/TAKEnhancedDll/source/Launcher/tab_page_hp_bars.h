#pragma once
#include "TAKEnhancedDll/Launcher/nana_common.hpp"
#include "TAKEnhancedDll/Configs/GameConfig.hpp"

class tab_page_hp_bars : public nana::panel<false>
{
    std::shared_ptr<GameConfig> gameConfig;
    std::shared_ptr<Logger> logger;

public:
    std::unique_ptr<nana::place> layout;

    // Hp Bar Options
    std::shared_ptr<nana::checkbox> cb_enableHpBarOptions;
    std::shared_ptr<nana::label> lbl_hpBarOptions;
    std::shared_ptr<nana::label> lbl_myHpBarOptions;
    std::shared_ptr<nana::label> lbl_allyHpBarOptions;
    std::shared_ptr<nana::label> lbl_enemyHpBarOptions;

    std::shared_ptr<nana::label> lbl_showHpMode;
    std::shared_ptr<nana::label> lbl_hpBarColorMode;
    std::shared_ptr<nana::label> lbl_hpBarColor;

    std::shared_ptr<nana::combox> cbb_myShowHpMode;
    std::shared_ptr<nana::combox> cbb_myHpBarColorMode;
    std::shared_ptr<nana::combox> cbb_myHpBarColor;

    std::shared_ptr<nana::combox> cbb_allyShowHpMode;
    std::shared_ptr<nana::combox> cbb_allyHpBarColorMode;
    std::shared_ptr<nana::combox> cbb_allyHpBarColor;

    std::shared_ptr<nana::combox> cbb_enemyShowHpMode;
    std::shared_ptr<nana::combox> cbb_enemyHpBarColorMode;
    std::shared_ptr<nana::combox> cbb_enemyHpBarColor;

    tab_page_hp_bars(nana::window parent, std::shared_ptr<GameConfig> gameConfig, std::shared_ptr<Logger> logger)
        : nana::panel<false>(parent), gameConfig(gameConfig), logger(logger)
    {
        initialize();
        draw();
        load();
        update();
    }

    void initialize()
    {
        initialize_hp_bar_options();
    }

    void initialize_hp_bar_options()
    {
        // Hp Bar Options Group Box
        cb_enableHpBarOptions = std::make_shared<nana::checkbox>(*this, nana::rectangle(8, 26, 15, 15));
        lbl_hpBarOptions = std::make_shared<nana::label>(*this, nana::rectangle(30, 18, 75, 30));
        lbl_hpBarOptions->caption("<bold>Hp Bar Options</>");
        lbl_hpBarOptions->format(true);

        // Left labels
        lbl_myHpBarOptions      = std::make_shared<nana::label>(*this, "Me: ");
        lbl_allyHpBarOptions    = std::make_shared<nana::label>(*this, "Ally: ");
        lbl_enemyHpBarOptions   = std::make_shared<nana::label>(*this, "Enemy: ");

        // Top labels
        lbl_showHpMode          = std::make_shared<nana::label>(*this, "Show Mode");
        lbl_hpBarColorMode      = std::make_shared<nana::label>(*this, "HP Color Mode");
        lbl_hpBarColor          = std::make_shared<nana::label>(*this, "Color");

        cb_enableHpBarOptions->bgcolor(default_bgcolor);
        lbl_hpBarOptions     ->bgcolor(default_bgcolor);
        lbl_myHpBarOptions   ->bgcolor(default_bgcolor);
        lbl_allyHpBarOptions ->bgcolor(default_bgcolor);
        lbl_enemyHpBarOptions->bgcolor(default_bgcolor);

        lbl_showHpMode       ->bgcolor(default_bgcolor);
        lbl_hpBarColorMode   ->bgcolor(default_bgcolor);
        lbl_hpBarColor       ->bgcolor(default_bgcolor);

        // Checkboxes
        cbb_myShowHpMode        = std::make_shared<nana::combox>(*this);
        cbb_myHpBarColorMode    = std::make_shared<nana::combox>(*this);
        cbb_myHpBarColor        = std::make_shared<nana::combox>(*this);

        cbb_allyShowHpMode      = std::make_shared<nana::combox>(*this);
        cbb_allyHpBarColorMode  = std::make_shared<nana::combox>(*this);
        cbb_allyHpBarColor      = std::make_shared<nana::combox>(*this);

        cbb_enemyShowHpMode     = std::make_shared<nana::combox>(*this);
        cbb_enemyHpBarColorMode = std::make_shared<nana::combox>(*this);
        cbb_enemyHpBarColor     = std::make_shared<nana::combox>(*this);

        fillShowHpModeComboxOptions(cbb_myShowHpMode);
        fillHpBarColorModeComboxOptions(cbb_myHpBarColorMode);
        fillHpBarColorComboxOptions(cbb_myHpBarColor);

        fillShowHpModeComboxOptions(cbb_allyShowHpMode);
        fillHpBarColorModeComboxOptions(cbb_allyHpBarColorMode);
        fillHpBarColorComboxOptions(cbb_allyHpBarColor);

        fillShowHpModeComboxOptions(cbb_enemyShowHpMode);
        fillHpBarColorModeComboxOptions(cbb_enemyHpBarColorMode);
        fillHpBarColorComboxOptions(cbb_enemyHpBarColor);

        cbb_myShowHpMode->events().selected(
            [&](nana::arg_combox args) {
                update_hpBarColorMode_combox(cbb_myShowHpMode, cbb_myHpBarColorMode);
            }
        );

        cbb_allyShowHpMode->events().selected(
            [&](nana::arg_combox args) {
                update_hpBarColorMode_combox(cbb_allyShowHpMode, cbb_allyHpBarColorMode);
            }
        );

        cbb_enemyShowHpMode->events().selected(
            [&](nana::arg_combox args) {
                update_hpBarColorMode_combox(cbb_enemyShowHpMode, cbb_enemyHpBarColorMode);
            }
        );

        cbb_myHpBarColorMode->events().selected(
            [&](nana::arg_combox args) {
                update_hpBarColor_combox(cbb_myHpBarColorMode, cbb_myHpBarColor);
            }
        );

        cbb_allyHpBarColorMode->events().selected(
            [&](nana::arg_combox args) {
                update_hpBarColor_combox(cbb_allyHpBarColorMode, cbb_allyHpBarColor);
            }
        );

        cbb_enemyHpBarColorMode->events().selected(
            [&](nana::arg_combox args) {
                update_hpBarColor_combox(cbb_enemyHpBarColorMode, cbb_enemyHpBarColor);
            }
        );

        cb_enableHpBarOptions->events().checked(
            [&](nana::arg_checkbox args) {
                if (args.widget->checked()) {
                    on_cb_enableHpBarOptions_checked();
                }
                else {
                    disableHpBarOptions();
                }
            }
        );
    }

    void fillShowHpModeComboxOptions(std::shared_ptr<nana::combox>& combox)
    {
        for (std::pair<ShowMode::Enum, std::string> entry : showModeToString) {
            combox->push_back(entry.second);
        }
    }

    void fillHpBarColorModeComboxOptions(std::shared_ptr<nana::combox>& combox)
    {
        for (std::pair<ColorMode::Enum, std::string> entry : colorModeToString) {
            combox->push_back(entry.second);
        }
    }

    void fillHpBarColorComboxOptions(std::shared_ptr<nana::combox>& combox)
    {
        for (std::pair<Color::Enum, std::string> entry : colorToString) {
            combox->push_back(entry.second);
        }
    }

    void draw()
    {
        layout = std::make_unique<nana::place>(*this);

        layout->div("margin=[25, 5, 0, 30] vert                             <weight=30 <weight=75> topLabels arrange=[120, 130, 80]>                          \
                    <weight=100 <weight=50 margin=[9] vert leftLabels gap=9><vert <margin=[5, 0, 5] myHpBarOptions    arrange=[120, 130, 80] gap=5>           \
                                                                                  <margin=[5, 0, 5] allyHpBarOptions  arrange=[120, 130, 80] gap=5>           \
                                                                                  <margin=[5, 0, 5] enemyHpBarOptions arrange=[120, 130, 80] gap=5>>>         ");

        layout->field("leftLabels") << *lbl_myHpBarOptions << *lbl_allyHpBarOptions << *lbl_enemyHpBarOptions;
        layout->field("topLabels")  << *lbl_showHpMode     << *lbl_hpBarColorMode   << *lbl_hpBarColor;

        layout->field("myHpBarOptions") << *cbb_myShowHpMode
                                        << *cbb_myHpBarColorMode
                                        << *cbb_myHpBarColor;

        layout->field("allyHpBarOptions") << *cbb_allyShowHpMode
                                          << *cbb_allyHpBarColorMode
                                          << *cbb_allyHpBarColor;

        layout->field("enemyHpBarOptions") << *cbb_enemyShowHpMode
                                           << *cbb_enemyHpBarColorMode
                                           << *cbb_enemyHpBarColor;

        layout->collocate();
    }

    void load()
    {
        cb_enableHpBarOptions  ->check(this->gameConfig->customizableHpBars.enabled);

        cbb_myShowHpMode       ->option(this->gameConfig->customizableHpBars.mine.showMode -  1);
        cbb_myHpBarColorMode   ->option(this->gameConfig->customizableHpBars.mine.colorMode -  1);
        cbb_myHpBarColor       ->option(this->gameConfig->customizableHpBars.mine.color -  1);

        cbb_allyShowHpMode     ->option(this->gameConfig->customizableHpBars.ally.showMode -  1);
        cbb_allyHpBarColorMode ->option(this->gameConfig->customizableHpBars.ally.colorMode -  1);
        cbb_allyHpBarColor     ->option(this->gameConfig->customizableHpBars.ally.color -  1);

        cbb_enemyShowHpMode    ->option(this->gameConfig->customizableHpBars.enemy.showMode -  1);
        cbb_enemyHpBarColorMode->option(this->gameConfig->customizableHpBars.enemy.colorMode -  1);
        cbb_enemyHpBarColor    ->option(this->gameConfig->customizableHpBars.enemy.color -  1);
    } 

    void update()
    {
        if (cb_enableHpBarOptions->checked()) {
            enableHpBarOptions();
        }
        else {
            disableHpBarOptions();
        }

        update_hpBarColorMode_combox(cbb_myShowHpMode, cbb_myHpBarColorMode);
        update_hpBarColorMode_combox(cbb_allyShowHpMode, cbb_allyHpBarColorMode);
        update_hpBarColorMode_combox(cbb_enemyShowHpMode, cbb_enemyHpBarColorMode);

        update_hpBarColor_combox(cbb_myHpBarColorMode, cbb_myHpBarColor);
        update_hpBarColor_combox(cbb_allyHpBarColorMode, cbb_allyHpBarColor);
        update_hpBarColor_combox(cbb_enemyHpBarColorMode, cbb_enemyHpBarColor);
    }

    void save()
    {
        // HP Options
        this->gameConfig->customizableHpBars.enabled = cb_enableHpBarOptions->checked();

        // Mine Options
        this->gameConfig->customizableHpBars.mine.showMode       = (ShowMode::Enum)  (cbb_myShowHpMode->option() + 1);

        if (cbb_myHpBarColorMode->enabled())
            this->gameConfig->customizableHpBars.mine.colorMode  = (ColorMode::Enum) (cbb_myHpBarColorMode->option() + 1);

        if (cbb_myHpBarColor->enabled())
            this->gameConfig->customizableHpBars.mine.color      = (Color::Enum)     (cbb_myHpBarColor->option() + 1);

        // Ally Options
        this->gameConfig->customizableHpBars.ally.showMode       = (ShowMode::Enum)  (cbb_allyShowHpMode->option() + 1);

        if (cbb_allyHpBarColorMode->enabled())
            this->gameConfig->customizableHpBars.ally.colorMode  = (ColorMode::Enum) (cbb_allyHpBarColorMode->option() + 1);

        if (cbb_allyHpBarColorMode->enabled())
            this->gameConfig->customizableHpBars.ally.color      = (Color::Enum)     (cbb_allyHpBarColor->option() + 1);

        // Enemy Options
        this->gameConfig->customizableHpBars.enemy.showMode      = (ShowMode::Enum)  (cbb_enemyShowHpMode->option() + 1);

        if (cbb_enemyHpBarColorMode->enabled())
            this->gameConfig->customizableHpBars.enemy.colorMode = (ColorMode::Enum) (cbb_enemyHpBarColorMode->option() + 1);

        if (cbb_enemyHpBarColor->enabled())
            this->gameConfig->customizableHpBars.enemy.color     = (Color::Enum)     (cbb_enemyHpBarColor->option() + 1);
    }

    void reload()
    {
        load();
    }

    void update_hpBarColorMode_combox(std::shared_ptr<nana::combox>& showMode, std::shared_ptr<nana::combox>& colorMode)
    {
        if ((showMode->option() + 1) == ShowMode::Never) {
            colorMode->enabled(false);
        }
        else {
            colorMode->enabled(true);
        }
    }

    void update_hpBarColor_combox(std::shared_ptr<nana::combox>& mode, std::shared_ptr<nana::combox>& color)
    {
        if ((mode->option() + 1) != ColorMode::Custom) {
            color->enabled(false);
        }
        else {
            color->enabled(true);
        }
    }

    void on_cb_enableHpBarOptions_checked()
    {
        enableHpBarOptions();
        update();
    }

    void enableHpBarOptions()
    {
        cbb_myShowHpMode       ->enabled(true);
        cbb_myHpBarColorMode   ->enabled(true);
        cbb_myHpBarColor       ->enabled(true);
        cbb_allyShowHpMode     ->enabled(true);
        cbb_allyHpBarColorMode ->enabled(true);
        cbb_allyHpBarColor     ->enabled(true);
        cbb_enemyShowHpMode    ->enabled(true);
        cbb_enemyHpBarColorMode->enabled(true);
        cbb_enemyHpBarColor    ->enabled(true);
    }

    void disableHpBarOptions()
    {
        cbb_myShowHpMode       ->enabled(false);
        cbb_myHpBarColorMode   ->enabled(false);
        cbb_myHpBarColor       ->enabled(false);
        cbb_allyShowHpMode     ->enabled(false);
        cbb_allyHpBarColorMode ->enabled(false);
        cbb_allyHpBarColor     ->enabled(false);
        cbb_enemyShowHpMode    ->enabled(false);
        cbb_enemyHpBarColorMode->enabled(false);
        cbb_enemyHpBarColor    ->enabled(false);
    }

    void make_editable()
    {
        cb_enableHpBarOptions->enabled(true);
        enableHpBarOptions();
        update();
    }

    void make_readonly()
    {
        cb_enableHpBarOptions->enabled(false);
        disableHpBarOptions();
    }
};
