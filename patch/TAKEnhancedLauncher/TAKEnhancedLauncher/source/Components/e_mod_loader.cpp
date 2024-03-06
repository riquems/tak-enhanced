#pragma once
#include "TAKEnhancedLauncher/components/e_mod_loader.hpp"
#include <TAKEnhancedDll/Utils.hpp>
#include <TAKEnhancedDll/Wrappers/Defs.h>
#include <DKy/files.hpp>

e_mod_loader::e_mod_loader(
    nana::window parent,
    std::shared_ptr<LauncherConfig> launcherConfig,
    std::shared_ptr<GameConfig> gameConfig,
    std::shared_ptr<Logger> logger
) : e_panel(parent),
    launcherConfig(launcherConfig),
    gameConfig(gameConfig),
    logger(logger) {
    this->initialize();
    this->draw();
    this->load();
}

void e_mod_loader::move_items(
    nana::listbox::index_pairs items,
    std::shared_ptr<nana::listbox> source,
    std::shared_ptr<nana::listbox> dest
) {
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

void e_mod_loader::initialize() {
    this->bgcolor(default_bgcolor);

    this->lbl_listbox1 = std::make_shared<nana::label>(*this, "Available Mods:");
    this->add_widget(this->lbl_listbox1, "listbox1");

    this->lb_listbox1 = std::make_shared<nana::listbox>(*this);
    this->lb_listbox1->append_header("Name");
    this->add_widget(this->lb_listbox1, "listbox1");

    auto hpi_files = files::get(this->launcherConfig->modsPath, ".hpi");

    std::for_each(hpi_files.begin(), hpi_files.end(),
        [&](std::filesystem::path file) {
            std::string filename = file.filename().string();
            if (!vector_has_str(files_loaded_by_default, filename) &&
                !vector_has_str(this->gameConfig->mods.selectedMods, filename)) {
                this->modFiles.push_back(filename);
            }
        }
    );

    this->add_binding(create_listbox_binding(this->lb_listbox1, this->modFiles));

    this->btn_moveAllRight = std::make_shared<nana::button>(*this, ">>");
    this->btn_moveAllRight->events().click(
        [&]() {
            nana::listbox::index_pairs items = this->lb_listbox1->items();

            move_items(items, this->lb_listbox1, this->lb_listbox2);

            this->on_state_changed();
        }
    );
    this->add_widget(this->btn_moveAllRight, "buttons");

    this->btn_moveSelectedRight = std::make_shared<nana::button>(*this, ">");
    this->btn_moveSelectedRight->events().click(
        [&]() {
            nana::listbox::index_pairs selected_items = this->lb_listbox1->selected();

            move_items(selected_items, this->lb_listbox1, this->lb_listbox2);

            this->on_state_changed();
        }
    );
    this->add_widget(this->btn_moveSelectedRight, "buttons");

    this->btn_moveSelectedLeft = std::make_shared<nana::button>(*this, "<");
    this->btn_moveSelectedLeft->events().click(
        [&]() {
            nana::listbox::index_pairs selected_items = this->lb_listbox2->selected();

            move_items(selected_items, this->lb_listbox2, this->lb_listbox1);

            this->on_state_changed();
        }
    );
    this->add_widget(this->btn_moveSelectedLeft, "buttons");

    this->btn_moveAllLeft = std::make_shared<nana::button>(*this, "<<");
    this->btn_moveAllLeft->events().click(
        [&]() {
            nana::listbox::index_pairs items = this->lb_listbox2->items();

            move_items(items, this->lb_listbox2, this->lb_listbox1);

            this->on_state_changed();
        }
    );
    this->add_widget(this->btn_moveAllLeft, "buttons");

    this->lbl_listbox2 = std::make_shared<nana::label>(*this, "Selected Mods:");
    this->add_widget(this->lbl_listbox2, "listbox2");

    this->lb_listbox2 = std::make_shared<nana::listbox>(*this);
    this->lb_listbox2->append_header("Name");
    this->add_widget(this->lb_listbox2, "listbox2");
    this->add_binding(create_listbox_binding(this->lb_listbox2, this->gameConfig->mods.selectedMods));
}

void e_mod_loader::draw() {
    this->layout->div("<vert arrange=[20] listbox1><weight=40 vert margin=5 <><weight=150 vert margin=[20] grid=[1,4] gap=5 buttons><>><vert arrange=[20] listbox2>");
    e_panel::draw();
}

void e_mod_loader::reset() {
    this->lb_listbox1->clear();
    this->lb_listbox2->clear();
}
