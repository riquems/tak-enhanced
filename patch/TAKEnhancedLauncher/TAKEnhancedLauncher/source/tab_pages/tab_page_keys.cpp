#include "TAKEnhancedLauncher/tab_pages/tab_page_keys.hpp"
#include <iostream>

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
    e_panel(parent),
    userConfig(userConfig),
    commands(commands),
    keys(keys),
    commandStringParser(commandStringParser),
    keyCombinationStringParser(keyCombinationStringParser)
{
    initialize();
    draw();
    load();
}

void tab_page_keys::initialize()
{
    this->bgcolor(default_bgcolor);

    addOnSpacebarOption();
    addOnDoubleClickOption();
    addOnTripleClickOption();
    addOnCtrlDoubleClickOption();

    lb_keyBindings = std::make_shared<nana::listbox>(*this);
    lb_keyBindings->append_header("Command");
    lb_keyBindings->append_header("Key Combination");
    this->add_widget(lb_keyBindings, "keyBindingsList");

    btn_add = std::make_shared<nana::button>(*this, "Add");
    btn_edit = std::make_shared<nana::button>(*this, "Edit");
    this->add_widget(btn_edit, "actionButtons");

    btn_clear = std::make_shared<nana::button>(*this, "Clear");
    this->add_widget(btn_clear, "actionButtons");

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

void addComboxOptions(std::shared_ptr<nana::combox> cbb, std::vector<std::string> options) {
    for (auto option : options) {
        cbb->push_back(option);
    }
}

void tab_page_keys::addOnSpacebarOption() {
    lbl_onSpacebar = std::make_shared<nana::label>(*this, "On Spacebar: ");
    this->add_widget(lbl_onSpacebar, "clickOptions");

    cb_onSpacebar = std::make_shared<nana::combox>(*this);
    addComboxOptions(cb_onSpacebar, TAK::Commands::commands);
    this->add_widget(cb_onSpacebar, "clickOptions");
    this->add_binding(create_combox_binding(cb_onSpacebar, this->userConfig->onSpacebar));
}

void tab_page_keys::addOnDoubleClickOption() {
    lbl_onDoubleClick = std::make_shared<nana::label>(*this, "On Double Click: ");
    this->add_widget(lbl_onDoubleClick, "clickOptions");

    cb_onDoubleClick = std::make_shared<nana::combox>(*this);
    addComboxOptions(cb_onDoubleClick, TAK::Commands::commands);
    this->add_widget(cb_onDoubleClick, "clickOptions");
    this->add_binding(create_combox_binding(cb_onDoubleClick, this->userConfig->onDoubleClick));
}

void tab_page_keys::addOnTripleClickOption() {
    lbl_onTripleClick = std::make_shared<nana::label>(*this, "On Triple Click: ");
    this->add_widget(lbl_onTripleClick, "clickOptions");

    cb_onTripleClick = std::make_shared<nana::combox>(*this);
    addComboxOptions(cb_onTripleClick, TAK::Commands::commands);
    this->add_widget(cb_onTripleClick, "clickOptions");
    this->add_binding(create_combox_binding(cb_onTripleClick, this->userConfig->onTripleClick));
}

void tab_page_keys::addOnCtrlDoubleClickOption() {
    lbl_onCtrlDoubleClick = std::make_shared<nana::label>(*this, "On CTRL + Double Click: ");
    this->add_widget(lbl_onCtrlDoubleClick, "clickOptions");

    cb_onCtrlDoubleClick = std::make_shared<nana::combox>(*this);
    addComboxOptions(cb_onCtrlDoubleClick, TAK::Commands::commands);
    this->add_widget(cb_onCtrlDoubleClick, "clickOptions");
    this->add_binding(create_combox_binding(cb_onCtrlDoubleClick, this->userConfig->onCtrlDoubleClick));
}

void tab_page_keys::draw()
{
    layout->div(
        "margin=15                                                                           \
        <                                                                                    \
            <max=200 arrange=[15, 25, repeated] vert gap=[3, 10, repeated] clickOptions>     \
            <max=10>                                                                         \
            <keyBindingsList>                                                                \
            <max=10>                                                                         \
            <max=80 arrange=30 vert gap=5 actionButtons>                                     \
        >"
    );

    e_panel::draw();
}

void tab_page_keys::load()
{
    nana::listbox::cat_proxy category = lb_keyBindings->at(0);

    std::vector<KeyBindingListItem> keyBindingsListItems;

    for (KeyBinding entry : this->userConfig->keyBindings) {
        KeyCombination keyCombination = entry.keyCombination;
        std::shared_ptr<Command> command = entry.command;

        KeyBindingListItem keyBindingListItem = {
            this->commandStringParser->toString(*command),
            this->keyCombinationStringParser->toString(keyCombination)
        };

        keyBindingsListItems.push_back(keyBindingListItem);
    }

    category.model<std::recursive_mutex>(std::move(keyBindingsListItems), value_translator, cell_translator);

    e_panel::load();

    lb_keyBindings->column_at(0).fit_content();
}

void tab_page_keys::commit()
{
    std::vector<KeyBindingListItem> keyBindings = get_keyBindings();

    this->userConfig->keyBindings.clear();

    for (KeyBindingListItem keyBinding : keyBindings) {
        std::shared_ptr<Command> command = this->commandStringParser->fromString(keyBinding.command);
        KeyCombination keyCombination = this->keyCombinationStringParser->fromString(keyBinding.keyBinding);

        this->userConfig->keyBindings.push_back(KeyBinding{ keyCombination, command });
    }

    e_panel::commit();
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
