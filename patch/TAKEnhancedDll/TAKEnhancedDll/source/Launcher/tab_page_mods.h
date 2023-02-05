#pragma once
#include "TAKEnhancedDll/Launcher/nana_common.hpp"
#include "TAKEnhancedDll/Utils.hpp"
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

    void initialize_checkboxes()
    {
        cb_enableDevMode = std::make_shared<nana::checkbox>(*this, "Enable Developer Mode");
        cb_enableMods    = std::make_shared<nana::checkbox>(*this, "Enable Mods");

        cb_enableDevMode->bgcolor(default_bgcolor);
        cb_enableMods->bgcolor(default_bgcolor);

        cb_enableMods->events().checked(
            [&]() {
                if (!cb_enableMods->checked()) {
                    desactivate_listboxes();
                    desactivate_buttons();
                }
                else {
                    activate_listboxes();
                    activate_buttons();
                }
            }
        );
    }

    void desactivate_listboxes()
    {
        lb_listbox1->enabled(false);
        lb_listbox2->enabled(false);

        nana::color listbox_colors_desactivated = nana::color(225, 225, 225, 1);
        lb_listbox1->bgcolor(listbox_colors_desactivated);
        lb_listbox2->bgcolor(listbox_colors_desactivated);
    }

    void desactivate_buttons()
    {
        btn_moveAllRight->enabled(false);
        btn_moveSelectedRight->enabled(false);
        btn_moveSelectedLeft->enabled(false);
        btn_moveAllLeft->enabled(false);
    }

    void activate_listboxes()
    {
        lb_listbox1->enabled(true);
        lb_listbox2->enabled(true);

        nana::color listbox_colors_activated = nana::color(255, 255, 255, 1);
        lb_listbox1->bgcolor(listbox_colors_activated);
        lb_listbox2->bgcolor(listbox_colors_activated);
    }

    void activate_buttons()
    {
        btn_moveAllRight->enabled(true);
        btn_moveSelectedRight->enabled(true);
        btn_moveSelectedLeft->enabled(true);
        btn_moveAllLeft->enabled(true);
    }

    void initialize_listbox1()
    {
        lbl_listbox1 = std::make_shared<nana::label>(*this, "Available Mods:");
        lbl_listbox1->bgcolor(default_bgcolor);

        lb_listbox1 = std::make_shared<nana::listbox>(*this);
        lb_listbox1->append_header("Name");
    }

    void load_listbox1()
    {
        nana::listbox::cat_proxy default_category = lb_listbox1->at(0);

        std::filesystem::path current_path = std::filesystem::current_path();

        std::vector<std::string> hpi_files = get_files_from_path(current_path, ".hpi");

        std::for_each(hpi_files.begin(), hpi_files.end(),
            [&](std::string filename) {
                if (!vector_has_str(files_loaded_by_default, filename) &&
                    !vector_has_str(this->gameConfig->mods.selectedMods, filename)) {
                    default_category.append(filename);
                }
            }
        );
    }

    void initialize_listbox2()
    {
        lbl_listbox2 = std::make_shared<nana::label>(*this, "Selected Mods:");
        lbl_listbox2->bgcolor(default_bgcolor);

        lb_listbox2 = std::make_shared<nana::listbox>(*this);
        lb_listbox2->append_header("Name");
    }

    void load_listbox2()
    {
        nana::listbox::cat_proxy default_category = lb_listbox2->at(0);

        for (std::string mod_filename : this->gameConfig->mods.selectedMods) {
            default_category.append(mod_filename);
        }
    }

    void move_items(nana::listbox::index_pairs items, std::shared_ptr<nana::listbox> source, std::shared_ptr<nana::listbox> dest)
    {
        std::reverse(items.begin(), items.end());

        std::vector<std::string> filenames;

        for (nana::listbox::index_pair selected_item_pair : items) {
            nana::listbox::item_proxy item = source->at(selected_item_pair);
            std::string filename = item.text(0);

            source->erase(item);

            filenames.push_back(filename);
        }

        std::reverse(filenames.begin(), filenames.end());

        nana::listbox::cat_proxy dest_default_category = dest->at(0);

        for (std::string filename : filenames) {
            dest_default_category.append(filename);
        }
    }

    void initialize_buttons()
    {
        btn_moveAllRight = std::make_shared<nana::button>(*this, ">>");
        btn_moveSelectedRight = std::make_shared<nana::button>(*this, ">");
        btn_moveSelectedLeft = std::make_shared<nana::button>(*this, "<");
        btn_moveAllLeft = std::make_shared<nana::button>(*this, "<<");

        btn_moveAllRight->events().click(
            [&]() {
                nana::listbox::index_pairs items = lb_listbox1->items();

                move_items(items, lb_listbox1, lb_listbox2);
            }
        );

        btn_moveSelectedRight->events().click(
            [&]() {
                nana::listbox::index_pairs selected_items = lb_listbox1->selected();

                move_items(selected_items, lb_listbox1, lb_listbox2);
            }
        );

        btn_moveSelectedLeft->events().click(
            [&]() {
                nana::listbox::index_pairs selected_items = lb_listbox2->selected();

                move_items(selected_items, lb_listbox2, lb_listbox1);
            }
        );

        btn_moveAllLeft->events().click(
            [&]() {
                nana::listbox::index_pairs items = lb_listbox2->items();

                move_items(items, lb_listbox2, lb_listbox1);
            }
        );
    }

public:
    tab_page_mods(nana::window parent, std::shared_ptr<GameConfig> gameConfig, std::shared_ptr<Logger> logger) :
        nana::panel<false>(parent), gameConfig(gameConfig), logger(logger)
    {
        initialize();
        draw();
        load();
        update();
    }

    void initialize()
    {
        initialize_listbox1();
        initialize_buttons();
        initialize_listbox2();
        initialize_checkboxes();
    }

    void draw()
    {
        layout = std::make_shared<nana::place>(*this);

        layout->div("margin=15 vert                                                                     \
                     <weight=30 checkboxes>                                                             \
                     <                                                                                  \
                         <vert arrange=[20] listbox1><weight=40 vert margin=5 <><weight=150 vert margin=[20] grid=[1,4] gap=5 buttons><>><vert arrange=[20] listbox2>         \
                     >");

        layout->field("checkboxes") << *cb_enableDevMode << *cb_enableMods;

        layout->field("listbox1") << *lbl_listbox1 << *lb_listbox1;
        layout->field("listbox2") << *lbl_listbox2 << *lb_listbox2;

        layout->field("buttons") << *btn_moveAllRight << *btn_moveSelectedRight
            << *btn_moveSelectedLeft << *btn_moveAllLeft;

        layout->collocate();
    }

    std::vector<std::string> get_selected_mods()
    {
        std::vector<std::string> selected_mods;

        nana::listbox::index_pairs selected_mods_index_pairs = lb_listbox2->items();

        for (nana::listbox::index_pair selected_mod_index_pairs : selected_mods_index_pairs) {
            std::string selected_mod_filename = lb_listbox2->at(selected_mod_index_pairs).text(0);

            selected_mods.push_back(selected_mod_filename);
        }

        return selected_mods;
    }

    void load()
    {
        cb_enableDevMode->check(this->gameConfig->developerMode.enabled);
        cb_enableMods->check(this->gameConfig->mods.enabled);

        load_listbox1();
        load_listbox2();
    }

    void update()
    {
        if (!cb_enableMods->checked()) {
            desactivate_listboxes();
            desactivate_buttons();
        }
        else {
            activate_listboxes();
            activate_buttons();
        }
    }

    void save()
    {
        this->gameConfig->developerMode.enabled = cb_enableDevMode->checked();
        this->gameConfig->mods.enabled = cb_enableMods->checked();

        // Selected Mods
        this->gameConfig->mods.selectedMods.clear();

        std::vector<std::string> selected_mods = get_selected_mods();

        for (std::string selected_mod : selected_mods) {
            this->gameConfig->mods.selectedMods.push_back(selected_mod);
        }
    }

    void reset()
    {
        lb_listbox1->clear();
        lb_listbox2->clear();
    }

    void reload()
    {
        this->reset();
        load();
    }

    void make_readonly()
    {
        cb_enableDevMode->enabled(false);
        cb_enableMods->enabled(false);

        desactivate_listboxes();
        desactivate_buttons();
    }

    void make_editable()
    {
        cb_enableDevMode->enabled(true);
        cb_enableMods->enabled(true);

        activate_listboxes();
        activate_buttons();
    }
};
