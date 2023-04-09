#pragma once
#include "TAKEnhancedLauncher/main_form.hpp"
#include "TAKEnhancedLauncher/binding.hpp"
#include "TAKEnhancedDll/GlobalState.hpp"

main_form::main_form(
        nana::rectangle rect,
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
        e_form(rect, nana::appearance(1, 1, 1, 0, 0, 0, 1)),
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
        this->initialize();
        this->load();
        this->draw();
        this->on_state_changed();
    }

void main_form::show()
{
    nana::form::show();
    nana::exec();
}

void main_form::commit_all()
{
    this->commit();
    tp_mods->commit();
    tp_patches->commit();
    tp_hp_bars->commit();
    tp_keys->commit();
}

void main_form::save()
{
    this->commit_all();
    this->on_save();
}

void main_form::initialize()
{
    this->caption("TA:K Enhanced Launcher");
    this->bgcolor(default_bgcolor);

    addTabs();

    addPlayButton();
    addExitButton();
    addSaveButton();

    addPresetPicker();

    //btn_save_as_preset = std::make_shared<nana::button>(this->handle(), "Save as preset");

    /*btn_save_as_preset->events().click(
        [&]() {
            modal_save_as_preset modal(this, &settings);
            modal.show();
            nana::exec();
        }
    );*/
}

void main_form::draw() {
    layout->div("                                                                           \
        margin=[1] vert                                                                             \
        <weight=25 tabs>                                                                            \
        <content>                                                                                   \
        <margin=25 weight=100                                                                       \
            <vert weight=60 <weight=40 saveBtn>>                                                    \
            <>                                                                                      \
            <vert                                                                                   \
                <weight=25 margin=[0, 0, 0, 5]                                                      \
                    <weight=43 margin=[4] presetPickerLabel><weight=110 presetPicker>               \
                >                                                                                   \
                <                                                                                   \
                    <weight=36 margin=[5, 0, 0, 9] presetHashLabel><margin=[5, 0, 0, 7] presetHash> \
                >                                                                                   \
            >                                                                                       \
            <vert weight=120 <weight=40 buttons gap=5 arrange=[60, 60]>>                            \
        >");

    e_form::draw();
}

void main_form::addTabs() {
    tabs = std::make_shared<nana::tabbar<std::string>>(this->handle());
    tabs->bgcolor(default_bgcolor);

    addModsTab();
    addPatchesTab();
    addHpBarsTab();
    addKeysTab();

    layout->field("tabs") << *tabs;
    layout->field("content").fasten(*tp_mods).fasten(*tp_patches).fasten(*tp_hp_bars).fasten(*tp_keys);

    tabs->activated(0);
}

void main_form::addModsTab() {
    tp_mods = std::make_shared<tab_page_mods>(
        this->handle(),
        this->launcherConfig,
        this->gameConfig,
        this->logger
    );

    tp_mods->on_state_changed_callback = [&]() {
        this->on_state_changed();
    };

    tabs->append("Mods", *tp_mods);
}

void main_form::addPatchesTab() {
    tp_patches = std::make_shared<tab_page_patches>(this->handle(), this->gameConfig);
    tp_patches->on_state_changed_callback = [&]() {
        this->on_state_changed();
    };

    tabs->append("Patches", *tp_patches);
}

void main_form::addHpBarsTab() {
    tp_hp_bars = std::make_shared<tab_page_hp_bars>(this->handle(), this->gameConfig, this->logger);
    tp_hp_bars->on_state_changed_callback = [&]() {
        this->on_state_changed();
    };

    tabs->append("HP Bars", *tp_hp_bars);
}

void main_form::addKeysTab() {
    tp_keys = std::make_shared<tab_page_keys>(
        this->handle(),
        this->userConfig,
        this->commands,
        this->keys,
        this->commandStringParser,
        this->keyCombinationStringParser
    );
    tp_keys->on_state_changed_callback = [&]() {
        this->on_state_changed();
    };

    tabs->append("Keys", *tp_keys);
}

void main_form::addPlayButton() {
    btn_play = std::make_shared<nana::button>(this->handle(), "Play");

    btn_play->events().click(
        [&]() {
            this->save();

            files::move(this->launcherConfig->modsPath, exePath, {
                .filenames = &this->gameConfig->mods.selectedMods
            });

            nana::API::exit_all();
        }
    );

    this->add_widget(btn_play, "buttons");
}

void main_form::addExitButton() {
    btn_exit = std::make_shared<nana::button>(this->handle(), "Exit");

    btn_exit->events().click(
        [&]() {
            nana::API::exit_all();
            ExitProcess(0);
        }
    );

    this->add_widget(btn_exit, "buttons");
}

void main_form::addSaveButton() {
    btn_save = std::make_shared<nana::button>(this->handle(), "Save");

    btn_save->events().click(
        [&]() {
            this->save();
        }
    );

    this->add_widget(btn_save, "saveBtn");
}

void main_form::commit()
{
    nana::size main_form_size = this->size();
    this->launcherConfig->window.width = main_form_size.width;
    this->launcherConfig->window.height = main_form_size.height;

    e_form::commit();
}

void main_form::addPresetPicker()
{
    lbl_preset_picker = std::make_shared<nana::label>(this->handle(), "Preset: ");
    cbb_preset_picker = std::make_shared<nana::combox>(this->handle());
    lbl_lbl_preset_hash = std::make_shared<nana::label>(this->handle(), "CRC: ");
    lbl_preset_hash = std::make_shared<nana::label>(this->handle());
    lbl_preset_hash->format(true);
    lbl_preset_hash->tooltip("Click to copy");

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
        }
    );

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

    this->add_widget(this->lbl_preset_picker, "presetPickerLabel");
    this->add_widget(this->cbb_preset_picker, "presetPicker");
    this->add_binding(create_combox_binding(this->cbb_preset_picker, this->launcherConfig->currentPreset));

    this->add_widget(this->lbl_lbl_preset_hash, "presetHashLabel");
    this->add_widget(this->lbl_preset_hash, "presetHash");
}

void main_form::on_state_changed() {
    logger->debug("State has changed");
    this->commit_all();
    this->update_crc();

    e_form::on_state_changed();
}

void main_form::update_crc() {
    json j = *this->gameConfig;
    auto jsonStr = j.dump(4);
    auto crc = CRC::Calculate(jsonStr.c_str(), jsonStr.size(), CRC::CRC_32());
    std::string hash = std::to_string(crc);
    oldHash = hash;
    lbl_preset_hash->caption(hash);
}

void main_form::reload_all()
{
    tp_mods   ->reload();
    tp_keys   ->reload();
    tp_patches->reload();
    tp_hp_bars->reload();
}

void main_form::make_all_editable()
{
    tp_mods   ->make_editable();
    tp_patches->make_editable();
}

void main_form::make_all_readonly()
{
    tp_mods   ->make_readonly();
    tp_patches->make_readonly();
}
