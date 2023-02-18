#pragma once
#include "TAKEnhancedLauncher/nana_common.hpp"
#include "Utils/VirtualKeys.h"
#include "Utils/HelperFunctions.hpp"

#include "TAKCore/Commands.h"
#include "TAKEnhancedDll/Commands/Command.hpp"
#include "TAKEnhancedDll/Keys/Keys.hpp"
#include <TAKEnhancedDll/Configs/UserConfig.hpp>
#include <TAKEnhancedDll/Commands/CommandStringParser.hpp>
#include <TAKEnhancedDll/Keys/KeyCombinationStringParser.hpp>
#include "TAKEnhancedLauncher/Components/e_dialog.hpp"

struct KeyBindingListItem
{
    std::string command;
    std::string keyBinding;

    bool operator==(const KeyBindingListItem& kb2) {
        return str_equals_str(command, kb2.command) && 
               str_equals_str(keyBinding, kb2.keyBinding);
    }
};

class tab_page_keys : public nana::panel<false>
{
    std::shared_ptr<UserConfig> userConfig;
    std::shared_ptr<Commands> commands;
    std::shared_ptr<Keys> keys;
    std::shared_ptr<CommandStringParser> commandStringParser;
    std::shared_ptr<KeyCombinationStringParser> keyCombinationStringParser;

    std::unique_ptr<nana::place> layout;

    std::shared_ptr<nana::label> lbl_onDoubleClick;
    std::shared_ptr<nana::combox> cb_onDoubleClick;

    std::shared_ptr<nana::label> lbl_onTripleClick;
    std::shared_ptr<nana::combox> cb_onTripleClick;

    std::shared_ptr<nana::label> lbl_onCtrlDoubleClick;
    std::shared_ptr<nana::combox> cb_onCtrlDoubleClick;

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
    );

    void initialize();

    void addOnDoubleClickOption();
    void addOnTripleClickOption();
    void addOnCtrlDoubleClickOption();

    void draw();
    void load();

    void save();

    void update();

    void reload();

    std::vector<KeyBindingListItem> get_keyBindings();
};
