#pragma once
#include "TAKEnhancedLauncher/main_form.hpp"
#include "TAKEnhancedLauncher/binding.hpp"
#include "TAKEnhancedDll/GlobalState.hpp"

main_form::main_form(
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
    ) :
        e_form(rect, nana::appearance(1, 1, 1, 0, 0, 0, 1)),
        launcherConfig(launcherConfig),
        gameConfig(gameConfig),
        userConfig(userConfig),
        presets(presets),
        keys(keys),
        commandStringParser(commandStringParser),
        keyCombinationStringParser(keyCombinationStringParser),
        logger(logger)
    {
        this->initialize(maybeTakVersion);
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
    tp_main->commit();
    tp_game_options->commit();
    tp_game_options->hp_bars_options->commit();
    tp_game_options->friendly_fire_options_group->commit();

    tp_keys->commit();
}

void main_form::save()
{
    this->commit_all();
    this->on_save();
}

void main_form::initialize(std::optional<std::string> maybeTakVersion)
{
    this->caption("TA:K Enhanced Launcher v1.3.5");
    this->bgcolor(default_bgcolor);

    addTabs();

    this->lbl_tak_version = std::make_shared<nana::label>(this->handle(), "TA:K Version: ");

    this->lbl_tak_version_value = std::make_shared<nana::label>(this->handle(), (maybeTakVersion.has_value() ? maybeTakVersion.value() : "<Error>"));
    this->add_widget(this->lbl_tak_version, "takVersion");
    this->add_widget(this->lbl_tak_version_value, "takVersionValue");

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

    this->events().key_press(
        [&](nana::arg_keyboard args) {
            auto key = this->keys->get(args.key);

            if (key == Keys::Return) {
                nana::API::emit_event(nana::event_code::click, *this->btn_play, nana::arg_click());
            }
        }
    );

    nana::API::enum_widgets(*this, true, [&](nana::widget& child_widget) {
        nana::API::events(child_widget).key_press.connect([&](const nana::arg_keyboard& arg) {
            nana::API::emit_event(nana::event_code::key_press, *this, arg);
        });
    });
}

void main_form::draw() {
    layout->div("                                                  \
        margin=[1] vert                                            \
        <weight=25 tabs>                                           \
        <content>                                                  \
        <margin=[0, 25, 10, 25] weight=90                          \
            <vert weight=60                                        \
                <>                                                 \
                <weight=40 saveBtn>                                \
                <>                                                 \
            >                                                      \
            <>                                                     \
            <vert weight=180                                       \
                <weight=25                                         \
                    <weight=39 presetPickerLabel><presetPicker>    \
                >                                                  \
                <margin=[7]                                        \
                    <weight=72 takVersion><takVersionValue>        \
                >                                                  \
                <margin=[4]                                        \
                    <weight=28 presetHashLabel><presetHash>        \
                >                                                  \
            >                                                      \
            <weight=30>                                            \
            <vert weight=120                                       \
              <>                                                   \
              <weight=40 buttons gap=5 arrange=[60, 60]>           \
              <>                                                   \
            >                                                      \
        >");

    e_form::draw();
}

void main_form::addTabs() {
    tabs = std::make_shared<nana::tabbar<std::string>>(this->handle());
    tabs->bgcolor(default_bgcolor);

    addMainTab();
    addGameOptionsTab();
    addKeysTab();

    layout->field("tabs") << *tabs;
    layout->field("content").fasten(*tp_main).fasten(*tp_game_options).fasten(*tp_keys);

    tabs->activated(0);
    tp_main->focus();
}

void main_form::addMainTab() {
    tp_main = std::make_shared<tab_page_main>(
        this->handle(),
        this->launcherConfig,
        this->gameConfig,
        this->logger
    );

    tp_main->on_state_changed_callback = [&]() {
        this->on_state_changed();
    };

    tabs->append(tp_main->name, *tp_main);
}

void main_form::addGameOptionsTab() {
    tp_game_options = std::make_shared<tab_page_game_options>(this->handle(), this->gameConfig, this->logger);

    tp_game_options->on_state_changed_callback = [&]() {
        this->on_state_changed();
    };

    tabs->append(tp_game_options->name, *tp_game_options);
}

void main_form::addKeysTab() {
    tp_keys = std::make_shared<tab_page_keys>(
        this->handle(),
        this->userConfig,
        this->keys,
        this->commandStringParser,
        this->keyCombinationStringParser
    );

    tp_keys->on_state_changed_callback = [&]() {
        this->on_state_changed();
    };

    tabs->append(tp_keys->name, *tp_keys);
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
    lbl_preset_picker->text_align(nana::align::left, nana::align_v::center);

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
                std::optional<Preset> maybePreset = this->presets->get(preset_name);

                if (!maybePreset.has_value())
                    return;

                auto& preset = maybePreset.value();

                logger->debug("Loading %s preset...", preset.name.c_str());

                *this->gameConfig = preset;

                logger->debug("Preset loaded successfully: ");

                json j = *this->gameConfig;

                logger->debug("%s", j.dump(4).c_str());

                logger->debug("Reloading the UI to reflect changes...", preset.name);

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
    tp_main   ->reload();
    tp_keys   ->reload();
    tp_game_options->reload();
    tp_game_options->hp_bars_options->reload();

    this->on_state_changed();
}

void main_form::make_all_editable()
{
    tp_main   ->make_editable();
    tp_game_options->make_editable();
}

void main_form::make_all_readonly()
{
    tp_main   ->make_readonly();
    tp_game_options->make_readonly();
}
