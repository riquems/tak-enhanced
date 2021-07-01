#pragma once

#include "Context.h"
#include "nana_common.h"
#include "tab_page_mods.h"
#include "tab_page_patches.h"

class main_form
{
    std::unique_ptr<nana::form> fm_main;
    std::unique_ptr<nana::place> layout;

    std::unique_ptr<nana::tabbar<std::string>> tabs;

    // Tab Pages
    std::unique_ptr<tab_page_mods> tp_mods;
    std::unique_ptr<tab_page_patches> tp_patches;

    // Buttons
    std::unique_ptr<nana::button> btn_continue;
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

        tabs->append("Mods", *tp_mods);
        tabs->append("Patch", *tp_patches);

        tabs->activated(0);

        layout->field("tabs") << *tabs;
        layout->field("content").fasten(*tp_mods).fasten(*tp_patches);

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
        btn_continue = std::make_unique<nana::button>(fm_main->handle(), "Continue");
        btn_exit     = std::make_unique<nana::button>(fm_main->handle(), "Exit");

        btn_continue->events().click(
            [&]() {
                settings.max_units                  = tp_patches->get_max_units();
                settings.pathfinding_cycles         = tp_patches->get_pathfinding_cycles();
                settings.forced_minrange_for_melees = tp_patches->get_forced_minrange_for_melees();

                settings.enable_dev_mode      = tp_mods->get_enableDevMode();
                settings.enable_mods          = tp_mods->get_enableMods();
                settings.no_cd                = tp_patches->get_noCD();
                settings.melee_stuck_fix      = tp_patches->get_meleeStuckFix();
                settings.offscreen_fix        = tp_patches->get_offscreenFix();
                settings.pause_when_unfocused = tp_patches->get_pauseWhenUnfocused();

                settings.selected_mods.clear();

                std::vector<std::string> selected_mods = tp_mods->get_selected_mods();

                for (std::string selected_mod : selected_mods) {
                    settings.selected_mods.push_back(selected_mod);
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

        layout->field("buttons") << *btn_continue << *btn_exit;
    }
};