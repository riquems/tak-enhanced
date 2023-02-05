#pragma once

#include "TAKEnhancedDll/Launcher/nana_common.hpp"

nana::color default_bgcolor = nana::color(0xF0, 0xF0, 0xF0, 1);

#include "tab_page_mods.h"
#include "tab_page_patches.h"
#include "tab_page_keys.h"
#include "tab_page_hp_bars.h"
#include "Components/modal_save_as_preset.hpp"
#include <Utils/Logger.h>
#include <TAKEnhancedDll/Presets/Presets.hpp>
#include "TAKEnhancedDll/Configs/LauncherConfig.hpp"
#include "Utils/CRC.h"
#include <TAKEnhancedDll/Presets/PresetApplier.hpp>
#include "Utils/CopyToClipboard.hpp"

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
    ) :
        launcherConfig(launcherConfig),
        gameConfig(gameConfig),
        userConfig(userConfig),
        presets(presets),
        presetApplier(presetApplier),
        commands(commands),
        keys(keys),
        commandStringParser(commandStringParser),
        keyCombinationStringParser(keyCombinationStringParser),
        logger(logger)
    {
        initialize();
    }

    void show()
    {
        fm_main->show();
        nana::exec();
    }

    void update()
    {
        update_crc();
    }

    void save_all()
    {
        this      ->save();
        tp_mods   ->save();
        tp_patches->save();
        tp_hp_bars->save();
        tp_keys   ->save();
        this      ->on_save();
    }

private:
    void initialize()
    {
        nana::API::window_icon_default(nana::paint::image("Kingdoms.exe"));

        nana::rectangle fm_rect = nana::API::make_center(launcherConfig->window.width, launcherConfig->window.height);
        fm_main = std::make_unique<nana::form>(fm_rect, nana::appearance(1, 1, 1, 0, 0, 0, 1));

        fm_main->caption("TA:K Enhanced Launcher");
        fm_main->bgcolor(default_bgcolor);

        layout = std::make_unique<nana::place>(fm_main->handle());
        layout->div("margin=[1] vert<weight=25 tabs>                                                                  \
                                       <content>                                                                      \
                    <weight=60 margin=[0, 20, 15, 15] <weight=60 saveBtn><margin=[0, 0, 0, 5]><weight=170 vert <weight=25 margin=[0, 0, 0, 5] <weight=43 margin=[4] presetPickerLabel><weight=110 presetPicker>><<weight=36 margin=[5, 0, 0, 9] presetHashLabel><margin=[5, 0, 0, 7] presetHash>>><weight=120 buttons gap=5 arrange=[60, 60]>");

        addTabs();
        
        addPlayButton();
        addExitButton();
        addSaveButton();
        
        addPresetPicker();

        layout->collocate();

        //btn_save_as_preset = std::make_unique<nana::button>(fm_main->handle(), "Save as preset");

        /*btn_save_as_preset->events().click(
            [&]() {
                modal_save_as_preset modal(this, &settings);
                modal.show();
                nana::exec();
            }
        );*/
    }

    void addTabs() {
        tabs = std::make_unique<nana::tabbar<std::string>>(fm_main->handle());
        tabs->bgcolor(default_bgcolor);

        addModsTab();
        addPatchesTab();
        addHpBarsTab();
        addKeysTab();

        layout->field("tabs") << *tabs;
        layout->field("content").fasten(*tp_mods).fasten(*tp_patches).fasten(*tp_hp_bars).fasten(*tp_keys);

        tabs->activated(0);
    }

    void addModsTab() {
        tp_mods = std::make_unique<tab_page_mods>(fm_main->handle(), this->gameConfig, this->logger);

        tabs->append("Mods", *tp_mods);
    }

    void addPatchesTab() {
        tp_patches = std::make_unique<tab_page_patches>(fm_main->handle(), this->gameConfig);

        tabs->append("Patches", *tp_patches);
    }

    void addHpBarsTab() {
        tp_hp_bars = std::make_unique<tab_page_hp_bars>(fm_main->handle(), this->gameConfig, this->logger);

        tabs->append("HP Bars", *tp_hp_bars);
    }

    void addKeysTab() {
        tp_keys = std::make_unique<tab_page_keys>(
            fm_main->handle(),
            this->userConfig,
            this->commands,
            this->keys,
            this->commandStringParser,
            this->keyCombinationStringParser
        );

        tabs->append("Keys", *tp_keys);
    }

    void addPlayButton() {
        btn_play = std::make_unique<nana::button>(fm_main->handle(), "Play");

        btn_play->events().click(
            [&]() {
                save_all();
                nana::API::exit_all();
            }
        );

        layout->field("buttons") << *btn_play;
    }

    void addExitButton() {
        btn_exit = std::make_unique<nana::button>(fm_main->handle(), "Exit");

        btn_exit->events().click(
            [&]() {
                nana::API::exit_all();
                ExitProcess(0);
            }
        );

        layout->field("buttons") << *btn_exit;
    }

    void addSaveButton() {
        btn_save = std::make_unique<nana::button>(fm_main->handle(), "Save");

        btn_save->events().click(
            [&]() {
                save_all();
                update();
            }
        );

        layout->field("saveBtn") << *btn_save;
    }

    void save()
    {
        nana::size main_form_size = fm_main->size();

        this->launcherConfig->currentPreset = cbb_preset_picker->text(cbb_preset_picker->option());
        this->launcherConfig->window.width = main_form_size.width;
        this->launcherConfig->window.height = main_form_size.height;
    }

    void addPresetPicker()
    {
        lbl_preset_picker = std::make_unique<nana::label>(fm_main->handle(), "Preset: ");
        cbb_preset_picker = std::make_unique<nana::combox>(fm_main->handle());
        lbl_lbl_preset_hash = std::make_unique<nana::label>(fm_main->handle(), "CRC: ");
        lbl_preset_hash = std::make_unique<nana::label>(fm_main->handle());
        lbl_preset_hash->format(true);
        lbl_preset_hash->tooltip("Click to copy");

        lbl_preset_picker->bgcolor(default_bgcolor);

        cbb_preset_picker->push_back("Custom");

        std::vector<Preset> presets = this->presets->asVector();

        for (Preset preset : presets) {
            cbb_preset_picker->push_back(preset.name);
        }

        cbb_preset_picker->events().text_changed(
            [&](nana::arg_combox args) {
                std::string preset_name = args.widget.text(args.widget.option());

                if (preset_name == "Custom") {
                    this->make_all_editable();
                    this->reload_all();
                    btn_save->enabled(true);
                }
                else {
                    std::optional<Preset> preset = this->presets->get(preset_name);

                    if (!preset.has_value())
                        return;

                    this->presetApplier->applyPreset(preset.value(), *this->gameConfig);

                    this->reload_all();
                    this->make_all_readonly();
                    btn_save->enabled(false);
                }

                update_crc();
            }
        );

        cbb_preset_picker->option(0);
        for (int i = 0; i < cbb_preset_picker->the_number_of_options(); i++)
        {
            if (cbb_preset_picker->text(i) == this->launcherConfig->currentPreset) {
                cbb_preset_picker->option(i);
                break;
            }
        }

        lbl_preset_hash->events().click(
            [&]() {
                std::string text = lbl_preset_hash->caption();

                if (text != "Copied!") {
                    copyToClipboard(text);

                    oldHash = text;
                    lbl_preset_hash->caption("Copied!");
                }
            }
        );

        lbl_preset_hash->events().mouse_leave(
            [&]() {
                lbl_preset_hash->caption(oldHash);
            }
        );

        layout->field("presetPickerLabel") << *lbl_preset_picker;
        layout->field("presetPicker") << *cbb_preset_picker;

        layout->field("presetHashLabel") << *lbl_lbl_preset_hash;
        layout->field("presetHash") << *lbl_preset_hash;
    }

    void update_crc() {
        json j = *this->gameConfig;
        auto jsonStr = j.dump(4);
        auto crc = CRC::Calculate(jsonStr.c_str(), jsonStr.size(), CRC::CRC_32());
        std::string hash = std::to_string(crc);
        oldHash = hash;
        lbl_preset_hash->caption(hash);
    }

    void reload_all()
    {
        tp_mods   ->reload();
        tp_keys   ->reload();
        tp_patches->reload();
        tp_hp_bars->reload();
    }

    void make_all_editable()
    {
        tp_mods   ->make_editable();
        tp_patches->make_editable();
    }

    void make_all_readonly()
    {
        tp_mods   ->make_readonly();
        tp_patches->make_readonly();
    }
};
