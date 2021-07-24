#pragma once
#include "TAKEnhancedDll/Launcher/nana_common.h"
#include "Wrappers/Info.h"
#include "TAKEnhancedDll/Utils.hpp"

class tab_page_mods : public nana::panel<false>
{
    std::unique_ptr<nana::place> layout;

    std::unique_ptr<nana::checkbox> cb_enableDevMode;
    std::unique_ptr<nana::checkbox> cb_enableMods;
    std::shared_ptr<nana::label> lbl_listbox1;
    std::shared_ptr<nana::label> lbl_listbox2;
    std::shared_ptr<nana::listbox> lb_listbox1;
    std::shared_ptr<nana::listbox> lb_listbox2;

    std::unique_ptr<nana::button> btn_moveAllRight;
    std::unique_ptr<nana::button> btn_moveSelectedRight;
    std::unique_ptr<nana::button> btn_moveSelectedLeft;
    std::unique_ptr<nana::button> btn_moveAllLeft;

    void initialize_checkboxes()
    {
        cb_enableDevMode = std::make_unique<nana::checkbox>(*this, "Enable Developer Mode");
        cb_enableDevMode->bgcolor(default_bgcolor);

        if (settings.EnableDevMode) {
            cb_enableDevMode->check(true);
        }

        cb_enableMods = std::make_unique<nana::checkbox>(*this, "Enable Mods");
        cb_enableMods->bgcolor(default_bgcolor);

        if (settings.EnableMods) {
            cb_enableMods->check(true);
        }

        if (!cb_enableMods->checked()) {
            desactivate_listboxes();
            desactivate_buttons();
        }
        else {
            activate_listboxes();
            activate_buttons();
        }

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

        layout->field("checkboxes") << *cb_enableDevMode << *cb_enableMods;
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

        lb_listbox1 = std::make_unique<nana::listbox>(*this);
        lb_listbox1->append_header("Name");

        nana::listbox::cat_proxy default_category = lb_listbox1->at(0);

        std::filesystem::path current_path = std::filesystem::current_path();

        std::vector<std::string> hpi_files = get_files_from_path(current_path, ".hpi");

        std::for_each(hpi_files.begin(), hpi_files.end(),
            [&](std::string filename) {
                if (!vector_has_str(files_loaded_by_default, filename) &&
                    !vector_has_str(settings.SelectedMods, filename)) {
                    default_category.append(filename);
                }
            }
        );

        layout->field("listbox1") << *lbl_listbox1 << *lb_listbox1;
    }

    void initialize_listbox2()
    {
        lbl_listbox2 = std::make_shared<nana::label>(*this, "Selected Mods:");
        lbl_listbox2->bgcolor(default_bgcolor);

        lb_listbox2 = std::make_unique<nana::listbox>(*this);
        lb_listbox2->append_header("Name");

        nana::listbox::cat_proxy default_category = lb_listbox2->at(0);

        for (std::string mod_filename : settings.SelectedMods) {
             default_category.append(mod_filename);
        }

        layout->field("listbox2") << *lbl_listbox2 << *lb_listbox2;
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
        btn_moveAllRight = std::make_unique<nana::button>(*this, ">>");
        btn_moveSelectedRight = std::make_unique<nana::button>(*this, ">");
        btn_moveSelectedLeft = std::make_unique<nana::button>(*this, "<");
        btn_moveAllLeft = std::make_unique<nana::button>(*this, "<<");

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

        layout->field("buttons") << *btn_moveAllRight << *btn_moveSelectedRight
                                 << *btn_moveSelectedLeft << *btn_moveAllLeft;
    }

public:
    tab_page_mods(nana::window parent) : nana::panel<false>(parent)
    {
        layout = std::make_unique<nana::place>(*this);

        layout->div("margin=15 vert                                                                     \
                     <weight=30 checkboxes>                                                             \
                     <                                                                                  \
                         <vert arrange=[20] listbox1><weight=40 vert margin=5 <><weight=150 vert margin=[20] grid=[1,4] gap=5 buttons><>><vert arrange=[20] listbox2>         \
                     >");

        initialize_listbox1();
        initialize_buttons();
        initialize_listbox2();
        initialize_checkboxes();

        layout->collocate();
    }

    bool get_enableDevMode()
    {
        return cb_enableDevMode->checked();
    }

    bool get_enableMods()
    {
        return cb_enableMods->checked();
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
};