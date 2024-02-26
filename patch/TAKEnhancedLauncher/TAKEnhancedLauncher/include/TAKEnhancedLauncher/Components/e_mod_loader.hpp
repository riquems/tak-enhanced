#pragma once
#include "TAKEnhancedLauncher/components/e_panel.hpp"
#include <TAKEnhancedDll/Configs/GameConfig.hpp>
#include <TAKEnhancedDll/Configs/LauncherConfig.hpp>
#include <Utils/Logger.h>

class e_mod_loader : public e_panel
{
    std::shared_ptr<LauncherConfig> launcherConfig;
    std::shared_ptr<GameConfig> gameConfig;
    std::shared_ptr<Logger> logger;

    std::vector<std::string> modFiles;

    std::shared_ptr<nana::label> lbl_listbox1;
    std::shared_ptr<nana::label> lbl_listbox2;
    std::shared_ptr<nana::listbox> lb_listbox1;
    std::shared_ptr<nana::listbox> lb_listbox2;

    std::shared_ptr<nana::button> btn_moveAllRight;
    std::shared_ptr<nana::button> btn_moveSelectedRight;
    std::shared_ptr<nana::button> btn_moveSelectedLeft;
    std::shared_ptr<nana::button> btn_moveAllLeft;

    void move_items(
        nana::listbox::index_pairs items,
        std::shared_ptr<nana::listbox> source,
        std::shared_ptr<nana::listbox> dest
    );

public:
    e_mod_loader(
        nana::window parent,
        std::shared_ptr<LauncherConfig> launcherConfig,
        std::shared_ptr<GameConfig> gameConfig,
        std::shared_ptr<Logger> logger
    );

    void initialize();

    void draw();
    void reset();
};
