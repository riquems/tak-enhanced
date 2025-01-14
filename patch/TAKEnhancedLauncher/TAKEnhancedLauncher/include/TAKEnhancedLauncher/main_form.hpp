#pragma once

#include <Utils/Logger.h>
#include "Utils/CRC.h"
#include "Utils/CopyToClipboard.hpp"
#include "TAKEnhancedLauncher/nana_common.hpp"
#include "TAKEnhancedLauncher/components/e_form.hpp"
#include "TAKEnhancedLauncher/components/hp_bars_options_component.hpp"
#include "TAKEnhancedLauncher/tab_pages/tab_page_keys.hpp"
#include "TAKEnhancedLauncher/tab_pages/tab_page_main.hpp"
#include "TAKEnhancedLauncher/tab_pages/tab_page_game_options.hpp"
#include "TAKEnhancedLauncher/components/modal_save_as_preset.hpp"
#include <TAKEnhancedDll/Presets/Presets.hpp>
#include "TAKEnhancedDll/Configs/LauncherConfig.hpp"
#include "TAKEnhancedLibrary/Commands/CommandStringParser.hpp"

class main_form : public e_form
{
    std::shared_ptr<LauncherConfig> launcherConfig;
    std::shared_ptr<GameConfig> gameConfig;
    std::shared_ptr<UserConfig> userConfig;
    std::shared_ptr<Presets> presets;
    std::shared_ptr<Keys> keys;
    std::shared_ptr<CommandStringParser> commandStringParser;
    std::shared_ptr<KeyCombinationStringParser> keyCombinationStringParser;
    std::shared_ptr<Logger> logger;

    std::shared_ptr<nana::tabbar<std::string>> tabs;

    // Tab Pages
    std::shared_ptr<tab_page_main> tp_main;
    std::shared_ptr<tab_page_game_options> tp_game_options;
    std::shared_ptr<tab_page_keys> tp_keys;
    
    // Buttons
    std::shared_ptr<nana::button> btn_play;
    std::shared_ptr<nana::button> btn_save;
    //std::shared_ptr<nana::button> btn_save_as_preset;
    std::shared_ptr<nana::button> btn_exit;

    std::shared_ptr<nana::label> lbl_tak_version;
    std::shared_ptr<nana::label> lbl_tak_version_value;

    std::shared_ptr<nana::label> lbl_preset_picker;
    std::shared_ptr<nana::combox> cbb_preset_picker;
    std::shared_ptr<nana::label> lbl_preset_hash;
    std::shared_ptr<nana::label> lbl_lbl_preset_hash;

    std::string oldHash;

public:
    // Events
    std::function<void(void)> on_save;

    main_form(
        nana::rectangle rect,
        std::optional<std::string> maybeTakVersion,
        std::shared_ptr<LauncherConfig> launcherConfig,
        std::shared_ptr<GameConfig> gameConfig,
        std::shared_ptr<UserConfig> userConfig,
        std::shared_ptr<Presets> presets,
        std::shared_ptr<Keys> keys,
        std::shared_ptr<CommandStringParser> commandStringParser,
        std::shared_ptr<KeyCombinationStringParser> keyCombinationStringParser,
        std::shared_ptr<Logger> logger
    );

    void show();

    void commit_all();
    void save();

private:
    void initialize(std::optional<std::string> maybeTakVersion);
    void draw();

    void addTabs();
    void addMainTab();
    void addGameOptionsTab();
    void addKeysTab();
    void addPlayButton();
    void addExitButton();
    void addSaveButton();
    void commit();

    void addPresetPicker();

    void on_state_changed();
    void update_crc();

    void reload_all();
    void make_all_editable();
    void make_all_readonly();
};
