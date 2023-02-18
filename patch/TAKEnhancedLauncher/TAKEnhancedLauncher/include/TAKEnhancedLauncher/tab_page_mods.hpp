#pragma once
#include "TAKEnhancedLauncher/nana_common.hpp"
#include "TAKEnhancedDll/Configs/GameConfig.hpp"
#include "TAKEnhancedDll/Utils.hpp"
#include "Utils/Logger.h"
#include "TAKEnhancedDll/Wrappers/Defs.h"

class tab_page_mods : public nana::panel<false>
{
    std::shared_ptr<GameConfig> gameConfig;
    std::shared_ptr<Logger> logger;

    std::shared_ptr<nana::place> layout;

    std::shared_ptr<nana::checkbox> cb_enableDevMode;
    std::shared_ptr<nana::checkbox> cb_enableMods;
    std::shared_ptr<nana::label> lbl_listbox1;
    std::shared_ptr<nana::label> lbl_listbox2;
    std::shared_ptr<nana::listbox> lb_listbox1;
    std::shared_ptr<nana::listbox> lb_listbox2;

    std::shared_ptr<nana::button> btn_moveAllRight;
    std::shared_ptr<nana::button> btn_moveSelectedRight;
    std::shared_ptr<nana::button> btn_moveSelectedLeft;
    std::shared_ptr<nana::button> btn_moveAllLeft;

    void initialize_checkboxes();
    void desactivate_listboxes();
    void desactivate_buttons();
    void activate_listboxes();
    void activate_buttons();
    void initialize_listbox1();
    void load_listbox1();
    void initialize_listbox2();
    void load_listbox2();
    void move_items(nana::listbox::index_pairs items, std::shared_ptr<nana::listbox> source, std::shared_ptr<nana::listbox> dest);

    void initialize_buttons();

public:
    tab_page_mods(nana::window parent, std::shared_ptr<GameConfig> gameConfig, std::shared_ptr<Logger> logger);

    void initialize();

    void draw();
    std::vector<std::string> get_selected_mods();

    void load();
    void update();
    void save();
    void reset();
    void reload();

    void make_readonly();
    void make_editable();
};
