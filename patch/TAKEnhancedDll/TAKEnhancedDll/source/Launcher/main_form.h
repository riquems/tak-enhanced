#pragma once

#include "../Context.h"
#include "nana_common.h"
#include "tab_page_mods.h"
#include "tab_page_patches.h"
#include "tab_page_keys.h"

class main_form
{
    std::unique_ptr<nana::form> fm_main;
    std::unique_ptr<nana::place> layout;

    std::unique_ptr<nana::tabbar<std::string>> tabs;

    // Tab Pages
    std::unique_ptr<tab_page_mods> tp_mods;
    std::unique_ptr<tab_page_patches> tp_patches;
    std::unique_ptr<tab_page_keys> tp_keys;

    // Buttons
    std::unique_ptr<nana::button> btn_play;
    std::unique_ptr<nana::button> btn_exit;

public:
    main_form()
    {
        nana::API::window_icon_default(nana::paint::image("Kingdoms.exe"));

        fm_main = std::make_unique<nana::form>(nana::API::make_center(450, 320), nana::appearance(1, 1, 1, 0, 0, 0, 1));

        fm_main->caption("TA:K Enhanced Settings");
        fm_main->bgcolor(default_bgcolor);

        layout = std::make_unique<nana::place>(fm_main->handle());
        layout->div("margin=[1] vert<weight=25 tabs><content><weight=40 <><margin=5 grid=[2, 1] gap=5 buttons>>");

        tabs = std::make_unique<nana::tabbar<std::string>>(fm_main->handle());
        tabs->bgcolor(default_bgcolor);

        tp_mods = std::make_unique<tab_page_mods>(fm_main->handle());
        tp_patches = std::make_unique<tab_page_patches>(fm_main->handle());
        tp_keys = std::make_unique<tab_page_keys>(fm_main->handle());

        tabs->append("Mods", *tp_mods);
        tabs->append("Patch", *tp_patches);
        tabs->append("Keys", *tp_keys);

        tabs->activated(0);

        layout->field("tabs") << *tabs;
        layout->field("content").fasten(*tp_mods).fasten(*tp_patches).fasten(*tp_keys);

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
                bool showPlayer        = tp_patches->get_showPlayerHpBar();
                bool showAllies        = tp_patches->get_showAlliesHpBar();
                bool showEnemies       = tp_patches->get_showEnemiesHpBar();
                bool showOnlyIfDamaged = tp_patches->get_showHpBarOnlyIfDamaged();

                if (showPlayer)        settings.showHpOptions |= SHOW_PLAYER;
                else                   settings.showHpOptions &= ~SHOW_PLAYER;
                if (showAllies)        settings.showHpOptions |= SHOW_ALLIES;
                else                   settings.showHpOptions &= ~SHOW_ALLIES;
                if (showEnemies)       settings.showHpOptions |= SHOW_ENEMIES;
                else                   settings.showHpOptions &= ~SHOW_ENEMIES;
                if (showOnlyIfDamaged) settings.showHpOptions |= SHOW_ONLY_IF_DAMAGED;
                else                   settings.showHpOptions &= ~SHOW_ONLY_IF_DAMAGED;

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