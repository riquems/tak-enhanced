#pragma once
#include "TAKEnhancedLauncher/tab_page_keys.hpp"

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

tab_page_keys::tab_page_keys(
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

void tab_page_keys::initialize()
{
    addOnDoubleClickOption();
    addOnTripleClickOption();
    addOnCtrlDoubleClickOption();

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

void tab_page_keys::addOnDoubleClickOption() {
    lbl_onDoubleClick = std::make_shared<nana::label>(*this, "On Double Click: ");
    lbl_onDoubleClick->bgcolor(default_bgcolor);

    cb_onDoubleClick = std::make_shared<nana::combox>(*this);

    int idx = 0;
    int userOptionIndex = 0;
    for (auto& clickOption : TAK::Commands::commands) {
        if (this->userConfig->onDoubleClick == clickOption) {
            userOptionIndex = idx;
        }

        cb_onDoubleClick->push_back(clickOption);
        idx++;
    }

    cb_onDoubleClick->option(userOptionIndex);
}

void tab_page_keys::addOnTripleClickOption() {
    lbl_onTripleClick = std::make_shared<nana::label>(*this, "On Triple Click: ");
    lbl_onTripleClick->bgcolor(default_bgcolor);

    cb_onTripleClick = std::make_shared<nana::combox>(*this);

    int idx = 0;
    int userOptionIndex = 0;
    for (auto& clickOption : TAK::Commands::commands) {
        if (this->userConfig->onTripleClick == clickOption) {
            userOptionIndex = idx;
        }

        cb_onTripleClick->push_back(clickOption);
        idx++;
    }

    cb_onTripleClick->option(userOptionIndex);
}

void tab_page_keys::addOnCtrlDoubleClickOption() {
    lbl_onCtrlDoubleClick = std::make_shared<nana::label>(*this, "On CTRL + Double Click: ");
    lbl_onCtrlDoubleClick->bgcolor(default_bgcolor);

    cb_onCtrlDoubleClick = std::make_shared<nana::combox>(*this);

    int idx = 0;
    int userOptionIndex = 0;
    for (auto& clickOption : TAK::Commands::commands) {
        if (this->userConfig->onCtrlDoubleClick == clickOption) {
            userOptionIndex = idx;
        }

        cb_onCtrlDoubleClick->push_back(clickOption);
        idx++;
    }

    cb_onCtrlDoubleClick->option(userOptionIndex);
}

void tab_page_keys::draw()
{
    layout = std::make_unique<nana::place>(*this);

    layout->div(
        "margin=15                                                                           \
        <                                                                                    \
            <max=200 arrange=[15, 25, repeated] vert gap=[3, 10, repeated] clickOptions>     \
            <max=10>                                                                         \
            <max=249 keyBindingsList>                                                        \
            <max=10>                                                                         \
            <max=80 arrange=30 vert gap=5 actionButtons>                                     \
        >"
    );

    layout->field("clickOptions") << *lbl_onDoubleClick;
    layout->field("clickOptions") << *cb_onDoubleClick;

    layout->field("clickOptions") << *lbl_onTripleClick;
    layout->field("clickOptions") << *cb_onTripleClick;

    layout->field("clickOptions") << *lbl_onCtrlDoubleClick;
    layout->field("clickOptions") << *cb_onCtrlDoubleClick;

    layout->field("keyBindingsList") << *lb_keyBindings;
    layout->field("actionButtons") << *btn_edit << *btn_clear;

    layout->collocate();
}

void tab_page_keys::load()
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

void tab_page_keys::save()
{
    std::vector<KeyBindingListItem> keyBindings = get_keyBindings();

    this->userConfig->keyBindings.clear();

    for (KeyBindingListItem keyBinding : keyBindings) {
        Command command = this->commandStringParser->fromString(keyBinding.command);
        KeyCombination keyCombination = this->keyCombinationStringParser->fromString(keyBinding.keyBinding);

        this->userConfig->keyBindings.push_back(KeyBinding{ keyCombination, command });
    }

    this->userConfig->onDoubleClick = this->cb_onDoubleClick->text(this->cb_onDoubleClick->option());
    this->userConfig->onTripleClick = this->cb_onTripleClick->text(this->cb_onTripleClick->option());
    this->userConfig->onCtrlDoubleClick = this->cb_onCtrlDoubleClick->text(this->cb_onCtrlDoubleClick->option());
}

void tab_page_keys::update()
{

}

void tab_page_keys::reload()
{
    lb_keyBindings->clear();
    load();
}

std::vector<KeyBindingListItem> tab_page_keys::get_keyBindings() {
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
