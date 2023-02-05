#pragma once
#include "TAKEnhancedDll/Launcher/nana_common.hpp"
#include "Utils/VirtualKeys.h"
#include "Utils/HelperFunctions.hpp"

#include "TAKEnhancedDll/Commands/Command.hpp"
#include "TAKEnhancedDll/Keys/Keys.hpp"
#include <TAKEnhancedDll/Configs/UserConfig.hpp>
#include <TAKEnhancedDll/Commands/CommandStringParser.hpp>
#include <TAKEnhancedDll/Keys/KeyCombinationStringParser.hpp>
#include "Components/e_dialog.hpp"

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

class tab_page_keys : public nana::panel<false>
{
    std::shared_ptr<UserConfig> userConfig;
    std::shared_ptr<Commands> commands;
    std::shared_ptr<Keys> keys;
    std::shared_ptr<CommandStringParser> commandStringParser;
    std::shared_ptr<KeyCombinationStringParser> keyCombinationStringParser;

    std::unique_ptr<nana::place> layout;

    std::shared_ptr<nana::listbox> lb_keyBindings;

    std::shared_ptr<nana::button> btn_add;
    std::shared_ptr<nana::button> btn_edit;
    std::shared_ptr<nana::button> btn_clear;

public:
    tab_page_keys(
        nana::window parent,
        std::shared_ptr<UserConfig> userConfig,
        std::shared_ptr<Commands> commands,
        std::shared_ptr<Keys> keys,
        std::shared_ptr<CommandStringParser> commandStringParser,
        std::shared_ptr<KeyCombinationStringParser> keyCombinationStringParser
    ) :
        nana::panel<false>(parent),
        userConfig(userConfig),
        commands(commands),
        keys(keys),
        commandStringParser(commandStringParser),
        keyCombinationStringParser(keyCombinationStringParser)
    {
        initialize();
        draw();
        load();
        update();
    }

    void initialize()
    {
        lb_keyBindings = std::make_shared<nana::listbox>(*this);
        lb_keyBindings->append_header("Command");
        lb_keyBindings->append_header("Key Combination");

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

                e_dialog keyBindingForm(
                    kb.command,
                    kb.keyBinding,
                    "Hit any Key...",
                    nana::API::make_center(160, 110)
                );
                
                keyBindingForm.events().key_press(
                    [&](nana::arg_keyboard args) {
                        int keyPressed = args.key;

                        item.text(1, this->keys->get(keyPressed).value().name);

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

                item.text(1, keys->get(VK_NONE).value().name);
            }
        );
    }

    void draw()
    {
        layout = std::make_unique<nana::place>(*this);

        layout->div("margin=15                                                          \
                     <margin=[0] keyBindingsList><weight=100 vert margin=[0, 20, 0, 20] <weight=80 vert gap=5 actionButtons>>");
        
        layout->field("keyBindingsList") << *lb_keyBindings;
        layout->field("actionButtons") << *btn_edit << *btn_clear;

        layout->collocate();
    }

    void load()
    {
        nana::listbox::cat_proxy category = lb_keyBindings->at(0);

        std::vector<KeyBindingListItem> keyBindingsListItems;

        for (KeyBinding entry : this->userConfig->keyBindings) {
            KeyCombination keyCombination = entry.keyCombination;
            Command command = entry.command;

            KeyBindingListItem keyBindingListItem = {
                this->commandStringParser->toString(command),
                this->keyCombinationStringParser->toString(keyCombination)
            };

            keyBindingsListItems.push_back(keyBindingListItem);
        }

        category.model<std::recursive_mutex>(std::move(keyBindingsListItems), value_translator, cell_translator);
    }

    void save()
    {
        std::vector<KeyBindingListItem> keyBindings = get_keyBindings();

        this->userConfig->keyBindings.clear();

        for (KeyBindingListItem keyBinding : keyBindings) {
            Command command = this->commandStringParser->fromString(keyBinding.command);
            KeyCombination keyCombination = this->keyCombinationStringParser->fromString(keyBinding.keyBinding);

            this->userConfig->keyBindings.push_back(KeyBinding{ keyCombination, command });
        }
    }

    void update()
    {

    }

    void reload()
    {
        lb_keyBindings->clear();
        load();
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
