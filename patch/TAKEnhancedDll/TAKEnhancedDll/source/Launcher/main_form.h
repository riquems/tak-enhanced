#pragma once

#include "../Context.h"
#include "nana_common.h"
#include "tab_page_mods.h"
#include "tab_page_patches.h"
#include "tab_page_keys.h"
#include "tab_page_customization.h"

class main_form
{
    std::unique_ptr<nana::form> fm_main;
    std::unique_ptr<nana::place> layout;

    std::unique_ptr<nana::tabbar<std::string>> tabs;

    // Tab Pages
    std::unique_ptr<tab_page_mods> tp_mods;
    std::unique_ptr<tab_page_patches> tp_patches;
    std::unique_ptr<tab_page_keys> tp_keys;
    std::unique_ptr<tab_page_customization> tp_customization;

    // Buttons
    std::unique_ptr<nana::button> btn_play;
    std::unique_ptr<nana::button> btn_exit;

public:
    main_form()
    {
        nana::API::window_icon_default(nana::paint::image("Kingdoms.exe"));

        nana::rectangle fm_rect = nana::API::make_center(settings.Launcher.Width, settings.Launcher.Height);
        fm_main = std::make_unique<nana::form>(fm_rect, nana::appearance(1, 1, 1, 0, 0, 0, 1));

        fm_main->caption("TA:K Enhanced Settings");
        fm_main->bgcolor(default_bgcolor);

        layout = std::make_unique<nana::place>(fm_main->handle());
        layout->div("margin=[1] vert<weight=25 tabs><content><weight=40 <><margin=5 grid=[2, 1] gap=5 buttons>>");

        tabs = std::make_unique<nana::tabbar<std::string>>(fm_main->handle());
        tabs->bgcolor(default_bgcolor);

        tp_mods = std::make_unique<tab_page_mods>(fm_main->handle());
        tp_patches = std::make_unique<tab_page_patches>(fm_main->handle());
        tp_keys = std::make_unique<tab_page_keys>(fm_main->handle());
        tp_customization = std::make_unique<tab_page_customization>(fm_main->handle());

        tabs->append("Mods", *tp_mods);
        tabs->append("Patches", *tp_patches);
        tabs->append("Keys", *tp_keys);
        tabs->append("Customization", *tp_customization);
        layout->field("content").fasten(*tp_mods).fasten(*tp_patches).fasten(*tp_keys).fasten(*tp_customization);

        tabs->activated(0);

        layout->field("tabs") << *tabs;

        initialize_buttons();

        layout->collocate();

        
    }
    void show()
    {
        fm_main->show();
        nana::exec();
    }

private:
    void initialize_buttons()
    {
        btn_play = std::make_unique<nana::button>(fm_main->handle(), "Play");
        btn_exit = std::make_unique<nana::button>(fm_main->handle(), "Exit");

        btn_play->events().click(
            [&]() {
                nana::size main_form_size = fm_main->size();

                settings.Launcher.Width = main_form_size.width;
                settings.Launcher.Height = main_form_size.height;

                settings.MaxUnits                  = tp_patches->get_max_units();
                settings.PathFindingCycles         = tp_patches->get_pathfinding_cycles();
                settings.ForcedMinRangeForMelees   = tp_patches->get_forced_minrange_for_melees();

                settings.EnableDevMode       = tp_mods->get_enableDevMode();
                settings.EnableMods          = tp_mods->get_enableMods();
                settings.NoCD                = tp_patches->get_noCD();
                settings.MeleeStuckFix       = tp_patches->get_meleeStuckFix();
                settings.OffscreenFix        = tp_patches->get_offscreenFix();
                settings.PauseWhenUnfocused  = tp_patches->get_pauseWhenUnfocused();

                // HP Options
                
                // My Options
                settings.myHpOptions.showHpOption               = (ShowHpOption) tp_customization->cbb_myShowHpMode->option();

                if (tp_customization->cbb_myHpBarColorMode->enabled())
                    settings.myHpOptions.hpColorOption.mode     = (HpColorMode)  tp_customization->cbb_myHpBarColorMode->option();

                if (tp_customization->cbb_myHpBarColor->enabled())
                    settings.myHpOptions.hpColorOption.color    = (Color)        tp_customization->cbb_myHpBarColor->option();

                // Ally Options
                settings.allyHpOptions.showHpOption             = (ShowHpOption) tp_customization->cbb_allyShowHpMode->option();

                if (tp_customization->cbb_allyHpBarColorMode->enabled())
                    settings.allyHpOptions.hpColorOption.mode   = (HpColorMode)  tp_customization->cbb_allyHpBarColorMode->option();

                if (tp_customization->cbb_allyHpBarColorMode->enabled())
                settings.allyHpOptions.hpColorOption.color      = (Color)        tp_customization->cbb_allyHpBarColor->option();

                // Enemy Options
                settings.enemyHpOptions.showHpOption            = (ShowHpOption) tp_customization->cbb_enemyShowHpMode->option();

                if (tp_customization->cbb_enemyHpBarColorMode->enabled())
                    settings.enemyHpOptions.hpColorOption.mode  = (HpColorMode)  tp_customization->cbb_enemyHpBarColorMode->option();
                
                if (tp_customization->cbb_enemyHpBarColor->enabled())
                    settings.enemyHpOptions.hpColorOption.color = (Color)        tp_customization->cbb_enemyHpBarColor->option();

                // Selected Mods
                settings.SelectedMods.clear();
                
                std::vector<std::string> selected_mods = tp_mods->get_selected_mods();

                for (std::string selected_mod : selected_mods) {
                    settings.SelectedMods.push_back(selected_mod);
                }

                std::vector<KeyBindingListItem> keyBindings = tp_keys->get_keyBindings();

                for (KeyBindingListItem keyBinding : keyBindings) {
                    Command command = strToCommand(keyBinding.command);
                    Keys keys = strToKeys(keyBinding.keyBinding);

                    auto keys_iterator = std::find_if(settings.keyBindings.begin(), settings.keyBindings.end(),
                        [&](std::pair<Keys, Command> entry) {
                            return command == entry.second;
                        }
                    );

                    if (keys_iterator != settings.keyBindings.end()) {
                        settings.keyBindings.erase(keys_iterator);
                    }

                    settings.keyBindings.insert(std::pair { keys, command });
                }

                settings.Save();
                nana::API::exit_all();
            }
        );

        btn_exit->events().click(
            []() {
                nana::API::exit_all();
                ExitProcess(0);
            }
        );

        layout->field("buttons") << *btn_play << *btn_exit;
    }
};