#pragma once
#include "TAKEnhancedDll/Launcher/nana_common.h"
#include "TAKEnhancedDll/Settings.hpp"

class tab_page_customization : public nana::panel<false>
{
public:
    std::unique_ptr<nana::place> layout;

    // Hp Bar Options
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

    void initialize_hp_bar_options()
    {
        // Hp Bar Options Group Box
        lbl_hpBarOptions = std::make_shared<nana::label>(*this, nana::rectangle(25, 13, 75, 30));
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

        lbl_hpBarOptions->bgcolor(default_bgcolor);
        lbl_myHpBarOptions->bgcolor(default_bgcolor);
        lbl_allyHpBarOptions->bgcolor(default_bgcolor);
        lbl_enemyHpBarOptions->bgcolor(default_bgcolor);

        lbl_showHpMode->bgcolor(default_bgcolor);
        lbl_hpBarColorMode->bgcolor(default_bgcolor);
        lbl_hpBarColor->bgcolor(default_bgcolor);

        // Checkboxes
        cbb_myShowHpMode        = std::make_shared<nana::combox>(*this);
        cbb_myHpBarColorMode    = std::make_shared<nana::combox>(*this);
        cbb_myHpBarColor        = std::make_shared<nana::combox>(*this);

        fillShowHpModeComboxOptions(cbb_myShowHpMode);
        fillHpBarColorModeComboxOptions(cbb_myHpBarColorMode);
        fillHpBarColorComboxOptions(cbb_myHpBarColor);

        cbb_myShowHpMode->option(settings.myHpOptions.showHpOption);
        cbb_myHpBarColorMode->option(settings.myHpOptions.hpColorOption.mode);
        cbb_myHpBarColor->option(settings.myHpOptions.hpColorOption.color);

        cbb_allyShowHpMode      = std::make_shared<nana::combox>(*this);
        cbb_allyHpBarColorMode  = std::make_shared<nana::combox>(*this);
        cbb_allyHpBarColor      = std::make_shared<nana::combox>(*this);

        fillShowHpModeComboxOptions(cbb_allyShowHpMode);
        fillHpBarColorModeComboxOptions(cbb_allyHpBarColorMode);
        fillHpBarColorComboxOptions(cbb_allyHpBarColor);

        cbb_allyShowHpMode->option(settings.allyHpOptions.showHpOption);
        cbb_allyHpBarColorMode->option(settings.allyHpOptions.hpColorOption.mode);
        cbb_allyHpBarColor->option(settings.allyHpOptions.hpColorOption.color);

        cbb_enemyShowHpMode     = std::make_shared<nana::combox>(*this);
        cbb_enemyHpBarColorMode = std::make_shared<nana::combox>(*this);
        cbb_enemyHpBarColor     = std::make_shared<nana::combox>(*this);

        fillShowHpModeComboxOptions(cbb_enemyShowHpMode);
        fillHpBarColorModeComboxOptions(cbb_enemyHpBarColorMode);
        fillHpBarColorComboxOptions(cbb_enemyHpBarColor);

        cbb_enemyShowHpMode->option(settings.enemyHpOptions.showHpOption);
        cbb_enemyHpBarColorMode->option(settings.enemyHpOptions.hpColorOption.mode);
        cbb_enemyHpBarColor->option(settings.enemyHpOptions.hpColorOption.color);

        update_hpBarColorMode_combox(cbb_myShowHpMode, cbb_myHpBarColorMode);
        cbb_myShowHpMode->events().selected(
            [&](nana::arg_combox args) {
                update_hpBarColorMode_combox(cbb_myShowHpMode, cbb_myHpBarColorMode);
            }
        );

        update_hpBarColorMode_combox(cbb_allyShowHpMode, cbb_allyHpBarColorMode);
        cbb_allyShowHpMode->events().selected(
            [&](nana::arg_combox args) {
                update_hpBarColorMode_combox(cbb_allyShowHpMode, cbb_allyHpBarColorMode);
            }
        );

        update_hpBarColorMode_combox(cbb_enemyShowHpMode, cbb_enemyHpBarColorMode);
        cbb_enemyShowHpMode->events().selected(
            [&](nana::arg_combox args) {
                update_hpBarColorMode_combox(cbb_enemyShowHpMode, cbb_enemyHpBarColorMode);
            }
        );

        update_hpBarColor_combox(cbb_myHpBarColorMode, cbb_myHpBarColor);
        cbb_myHpBarColorMode->events().selected(
            [&](nana::arg_combox args) {
                update_hpBarColor_combox(cbb_myHpBarColorMode, cbb_myHpBarColor);
            }
        );

        update_hpBarColor_combox(cbb_allyHpBarColorMode, cbb_allyHpBarColor);
        cbb_allyHpBarColorMode->events().selected(
            [&](nana::arg_combox args) {
                update_hpBarColor_combox(cbb_allyHpBarColorMode, cbb_allyHpBarColor);
            }
        );

        update_hpBarColor_combox(cbb_enemyHpBarColorMode, cbb_enemyHpBarColor);
        cbb_enemyHpBarColorMode->events().selected(
            [&](nana::arg_combox args) {
                update_hpBarColor_combox(cbb_enemyHpBarColorMode, cbb_enemyHpBarColor);
            }
        );

        layout->field("leftLabels") << *lbl_myHpBarOptions << *lbl_allyHpBarOptions << *lbl_enemyHpBarOptions;
        layout->field("topLabels") << *lbl_showHpMode << *lbl_hpBarColorMode << *lbl_hpBarColor;

        layout->field("myHpBarOptions") << *cbb_myShowHpMode
            << *cbb_myHpBarColorMode
            << *cbb_myHpBarColor;

        layout->field("allyHpBarOptions") << *cbb_allyShowHpMode
            << *cbb_allyHpBarColorMode
            << *cbb_allyHpBarColor;

        layout->field("enemyHpBarOptions") << *cbb_enemyShowHpMode
            << *cbb_enemyHpBarColorMode
            << *cbb_enemyHpBarColor;

    }

    void update_hpBarColorMode_combox(std::shared_ptr<nana::combox>& showMode, std::shared_ptr<nana::combox>& colorMode)
    {
        if (showMode->option() == NEVER_SHOW) {
            colorMode->enabled(false);
        }
        else {
            colorMode->enabled(true);
        }
    }

    void update_hpBarColor_combox(std::shared_ptr<nana::combox>& mode, std::shared_ptr<nana::combox>& color)
    {
        if (mode->option() != FIXED_COLOR) {
            color->enabled(false);
        }
        else {
            color->enabled(true);
        }
    }

    void fillShowHpModeComboxOptions(std::shared_ptr<nana::combox>& combox)
    {
        for (std::pair<ShowHpOption, std::string> entry : showHpOptionToString)
        {
            combox->push_back(entry.second);
        }
    }

    void fillHpBarColorModeComboxOptions(std::shared_ptr<nana::combox>& combox)
    {
        for (std::pair<HpColorMode, std::string> entry : hpColorModeToString)
        {
            combox->push_back(entry.second);
        }
    }

    void fillHpBarColorComboxOptions(std::shared_ptr<nana::combox>& combox)
    {
        for (std::pair<Color, std::string> entry : colorToString)
        {
            combox->push_back(entry.second);
        }
    }

    tab_page_customization(nana::window parent) : nana::panel<false>(parent)
    {
        layout = std::make_unique<nana::place>(*this);

        layout->div("margin=[25, 5, 0, 30] vert                             <weight=30 <weight=75> topLabels arrange=[120, 130, 80]>                          \
                    <weight=100 <weight=50 margin=[9] vert leftLabels gap=9><vert <margin=[5, 0, 5] myHpBarOptions    arrange=[120, 130, 80] gap=5>           \
                                                                                  <margin=[5, 0, 5] allyHpBarOptions  arrange=[120, 130, 80] gap=5>           \
                                                                                  <margin=[5, 0, 5] enemyHpBarOptions arrange=[120, 130, 80] gap=5>>>         ");

        initialize_hp_bar_options();

        layout->collocate();
    }
};