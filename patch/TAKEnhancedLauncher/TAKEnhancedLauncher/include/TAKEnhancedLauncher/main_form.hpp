#pragma once

#include <Utils/Logger.h>
#include "Utils/CRC.h"
#include "Utils/CopyToClipboard.hpp"
#include "TAKEnhancedLauncher/nana_common.hpp"
#include "TAKEnhancedLauncher/tab_page_hp_bars.hpp"
#include "TAKEnhancedLauncher/tab_page_keys.hpp"
#include "TAKEnhancedLauncher/tab_page_mods.hpp"
#include "TAKEnhancedLauncher/tab_page_patches.hpp"
#include "TAKEnhancedLauncher/Components/modal_save_as_preset.hpp"
#include <TAKEnhancedDll/Presets/Presets.hpp>
#include "TAKEnhancedDll/Configs/LauncherConfig.hpp"
#include <TAKEnhancedDll/Presets/PresetApplier.hpp>

class main_form
{
    std::shared_ptr<LauncherConfig> launcherConfig;
    std::shared_ptr<GameConfig> gameConfig;
    std::shared_ptr<UserConfig> userConfig;
    std::shared_ptr<Presets> presets;
    std::shared_ptr<PresetApplier> presetApplier;
    std::shared_ptr<Commands> commands;
    std::shared_ptr<Keys> keys;
    std::shared_ptr<CommandStringParser> commandStringParser;
    std::shared_ptr<KeyCombinationStringParser> keyCombinationStringParser;
    std::shared_ptr<Logger> logger;

    std::unique_ptr<nana::form> fm_main;
    std::unique_ptr<nana::place> layout;

    std::unique_ptr<nana::tabbar<std::string>> tabs;

    // Tab Pages
    std::unique_ptr<tab_page_mods> tp_mods;
    std::unique_ptr<tab_page_patches> tp_patches;
    std::unique_ptr<tab_page_hp_bars> tp_hp_bars;
    std::unique_ptr<tab_page_keys> tp_keys;
    
    // Buttons
    std::unique_ptr<nana::button> btn_play;
    std::unique_ptr<nana::button> btn_save;
    //std::unique_ptr<nana::button> btn_save_as_preset;
    std::unique_ptr<nana::button> btn_exit;

    std::unique_ptr<nana::label> lbl_preset_picker;
    std::unique_ptr<nana::combox> cbb_preset_picker;
    std::unique_ptr<nana::label> lbl_preset_hash;
    std::unique_ptr<nana::label> lbl_lbl_preset_hash;

    std::string oldHash;

public:
    // Events
    std::function<void(void)> on_save;

    main_form(
        std::shared_ptr<LauncherConfig> launcherConfig,
        std::shared_ptr<GameConfig> gameConfig,
        std::shared_ptr<UserConfig> userConfig,
        std::shared_ptr<Presets> presets,
        std::shared_ptr<PresetApplier> presetApplier,
        std::shared_ptr<Commands> commands,
        std::shared_ptr<Keys> keys,
        std::shared_ptr<CommandStringParser> commandStringParser,
        std::shared_ptr<KeyCombinationStringParser> keyCombinationStringParser,
        std::shared_ptr<Logger> logger
    );

    void show();

    void update();
    void save_all();

private:
    void initialize();
    void addTabs();
    void addModsTab();
    void addPatchesTab();
    void addHpBarsTab();
    void addKeysTab();
    void addPlayButton();
    void addExitButton();
    void addSaveButton();
    void save();

    void addPresetPicker();

    void update_crc();

    void reload_all();
    void make_all_editable();
    void make_all_readonly();
};
