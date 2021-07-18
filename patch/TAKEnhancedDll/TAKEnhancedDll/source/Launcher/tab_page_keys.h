#pragma once
#include "nana_common.h"
#include "Utils/defs.h"
#include "Utils/HelperFunctions.hpp"

#include "TAKEnhancedDll/Models/Command.hpp"
#include "TAKEnhancedDll/Models/Keys.hpp"

struct KeyBindingListItem
{
    std::string command;
    std::string keyBinding;

    bool operator==(const KeyBindingListItem& kb2) {
        return str_equals_str(command, kb2.command) && 
               str_equals_str(keyBinding, kb2.keyBinding);
    }
};

nana::listbox::iresolver& operator>>(nana::listbox::iresolver& irs, KeyBindingListItem& kb)
{
    return irs >> kb.command >> kb.keyBinding;
}

auto value_translator = [](const std::vector<nana::listbox::cell>& cells)
{
    KeyBindingListItem kb;
    kb.command = cells[0].text;
    kb.keyBinding = cells[1].text;
    return kb;
};

auto cell_translator = [](const KeyBindingListItem& kb)
{
    std::vector<nana::listbox::cell> cells;
    cells.emplace_back(kb.command);
    cells.emplace_back(kb.keyBinding);
    return cells;
};

class takenhanced_dialog : public nana::form
{
    std::shared_ptr<nana::place> layout;
    std::shared_ptr<nana::label> lbl_text;
    std::shared_ptr<nana::label> lbl_helpText;

public:
    takenhanced_dialog(std::string title, std::string text, std::string helpText, nana::rectangle rect) : nana::form(rect, nana::appearance(1, 1, 1, 0, 0, 0, 1))
    {
        this->caption(title);
        this->bgcolor(default_bgcolor);

        layout = std::make_shared<nana::place>(*this);

        lbl_text = std::make_shared<nana::label>(*this, text);
        lbl_helpText = std::make_shared<nana::label>(*this, helpText);
        lbl_text->text_align(nana::align::center);
        lbl_helpText->text_align(nana::align::center);

        layout->div("margin=10 vert         <>                \
                                      <<><lblText><>>         \
                                       <lblHelpText>          ");

        layout->field("lblText") << *lbl_text;
        layout->field("lblHelpText") << *lbl_helpText;
        layout->collocate();
    }
};

class tab_page_keys : public nana::panel<false>
{
    std::unique_ptr<nana::place> layout;

    std::shared_ptr<nana::textbox> tb_searchBox;
    std::shared_ptr<nana::listbox> lb_keyBindings;

    std::shared_ptr<nana::button> btn_add;
    std::shared_ptr<nana::button> btn_edit;
    std::shared_ptr<nana::button> btn_clear;

    void add_search_box()
    {
        tb_searchBox = std::make_shared<nana::textbox>(*this);

        layout->field("searchBox") << *tb_searchBox;
    }

    void add_key_bindings()
    {
        lb_keyBindings = std::make_shared<nana::listbox>(*this);
        lb_keyBindings->append_header("Command");
        lb_keyBindings->append_header("KeyBinding");

        load_key_bindings();

        layout->field("keyBindingsList") << *lb_keyBindings;
    }

    void load_key_bindings()
    {
        nana::listbox::cat_proxy category = lb_keyBindings->at(0);

        std::vector<KeyBindingListItem> keyBindingsListItems;

        for (std::pair<Keys, Command> entry : settings.keyBindings) {
            Keys keys = entry.first;
            Command command = entry.second;

            KeyBindingListItem keyBindingListItem = { command.to_string(), keys.to_string() };
            keyBindingsListItems.push_back(keyBindingListItem);
        }

        category.model<std::recursive_mutex>(std::move(keyBindingsListItems), value_translator, cell_translator);
    }

    void add_buttons()
    {
        btn_add = std::make_shared<nana::button>(*this, "Add");
        btn_edit = std::make_shared<nana::button>(*this, "Edit");
        btn_clear = std::make_shared<nana::button>(*this, "Clear");

        btn_edit->events().click(
            [&]() {
                nana::listbox::index_pairs items = lb_keyBindings->selected();

                if (items.size() == 0)
                    return;

                nana::listbox::item_proxy item = lb_keyBindings->at(items.at(0));

                KeyBindingListItem kb;
                item.resolve_to(kb);

                takenhanced_dialog keyBindingForm(kb.command, kb.keyBinding, 
                                                  "Hit any Key...", nana::API::make_center(160, 110));
                
                keyBindingForm.events().key_press(
                    [&](nana::arg_keyboard args) {
                        int keyPressed = args.key;

                        item.text(1, keyToStr[keyPressed]);

                        keyBindingForm.close();
                    }
                );

                keyBindingForm.show();
                nana::exec();
            }
        );

        btn_clear->events().click(
            [&]() {
                nana::listbox::index_pairs items = lb_keyBindings->selected();

                if (items.size() == 0)
                    return;

                nana::listbox::item_proxy item = lb_keyBindings->at(items.at(0));

                item.text(1, keyToStr[VK_NONE]);
            }
        );

        layout->field("actionButtons") << *btn_edit << *btn_clear;
    }

public:
    tab_page_keys(nana::window parent) : nana::panel<false>(parent)
    {
        layout = std::make_unique<nana::place>(*this);

        layout->div("margin=15                            \
                     <margin=[0] keyBindingsList><weight=100 vert margin=[0, 20, 0, 20] <weight=80 vert gap=5 actionButtons>>");

        add_search_box();
        add_key_bindings();
        add_buttons();

        layout->collocate();
    }

    std::vector<KeyBindingListItem> get_keyBindings() {
        std::vector<KeyBindingListItem> keyBindings;

        nana::listbox::index_pairs itemsPositions = lb_keyBindings->items();

        for (nana::listbox::index_pair itemPos : itemsPositions) {
            nana::listbox::item_proxy item = lb_keyBindings->at(itemPos);

            KeyBindingListItem kb;
            item->resolve_to(kb);

            keyBindings.push_back(kb);
        }

        return keyBindings;
    }
};
