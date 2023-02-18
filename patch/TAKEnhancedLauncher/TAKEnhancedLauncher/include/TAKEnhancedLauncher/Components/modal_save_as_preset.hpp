#pragma once

#include "TAKEnhancedDll/Launcher/nana_common.hpp"
#include "success_modal.hpp"

class main_form;

//class modal_save_as_preset : public nana::form
//{
//    main_form* configurationUpdater,
//
//    std::shared_ptr<nana::place> layout;
//
//    std::shared_ptr<nana::label> lbl_presetName;
//    std::shared_ptr<nana::textbox> tb_presetName;
//    std::shared_ptr<nana::label> lbl_invalidNameMessage;
//
//    std::shared_ptr<nana::label> lbl_presetFilename;
//    std::shared_ptr<nana::textbox> tb_presetFilename;
//    std::shared_ptr<nana::label> lbl_invalidFilenameMessage;
//
//    std::shared_ptr<nana::label> lbl_select_settings_to_include;
//
//    std::shared_ptr<nana::checkbox> cb_include_mods;
//    std::shared_ptr<nana::checkbox> cb_include_patches;
//    std::shared_ptr<nana::checkbox> cb_include_customization;
//    std::shared_ptr<nana::checkbox> cb_include_keys;
//
//    std::shared_ptr<nana::button> btn_save;
//
//    std::shared_ptr<nana::filebox> fb_save;
//
//public:
//    modal_save_as_preset(main_form* configurationUpdater, Settings* settings) : nana::form(nana::api::make_center(345, 250), nana::appearance(1, 1, 1, 0, 0, 0, 0))
//    {
//        this->settings = settings;
//        this->configurationUpdater = configurationUpdater;
//
//        initialize();
//        draw();
//        load();
//    }
//
//    void initialize()
//    {
//        layout = std::make_shared<nana::place>(*this);
//
//        lbl_presetName = std::make_shared<nana::label>(*this, "Preset name: ");
//        tb_presetName = std::make_shared<nana::textbox>(*this);
//        lbl_invalidNameMessage = std::make_shared<nana::label>(*this, "<color=0xff0000>Invalid name.</>");
//
//        lbl_presetFilename = std::make_shared<nana::label>(*this, "Preset filename: ");
//        tb_presetFilename = std::make_shared<nana::textbox>(*this);
//        lbl_invalidFilenameMessage = std::make_shared<nana::label>(*this, "<color=0xff0000>Invalid filename.</>");
//
//        lbl_select_settings_to_include = std::make_shared<nana::label>(*this, "Select settings to include in the preset:");
//
//        cb_include_mods          = std::make_shared<nana::checkbox>(*this, "Mods");
//        cb_include_patches       = std::make_shared<nana::checkbox>(*this, "Patches");
//        cb_include_customization = std::make_shared<nana::checkbox>(*this, "Customization");
//        cb_include_keys          = std::make_shared<nana::checkbox>(*this, "Keys");
//
//        btn_save = std::make_shared<nana::button>(*this, "Save");
//
//        fb_save = std::make_shared<nana::filebox>(*this, true);
//
//        tb_presetName->events().focus(
//            [&](nana::arg_focus args) {
//                if (!tb_presetName->focused()) {
//                    fill_presetFilename_with_suggestion();
//                }
//            }
//        );
//
//        tb_presetName->events().text_changed(
//            [&](nana::arg_textbox args) {
//                if (!is_valid_tb_presetName()) {
//                    lbl_invalidNameMessage->show();
//                    return;
//                }
//
//                lbl_invalidNameMessage->hide();
//            }
//        );
//
//        tb_presetFilename->events().text_changed(
//            [&](nana::arg_textbox args) {
//                if (!is_valid_tb_presetFilename()) {
//                    lbl_invalidFilenameMessage->show();
//                    return;
//                }
//
//                lbl_invalidFilenameMessage->hide();
//            }
//        );
//        
//        btn_save->events().click(
//            [&]() {
//                validate_form();
//                if (!form_is_valid()) {
//                    return;
//                }
//             
//                std::cout << "Form is valid" << std::endl;
//
//                save_preset();
//
//                this->close();
//
//                std::string current_directory = std::filesystem::current_path().string();
//                success_modal successModal(422, 130,
//                    "Preset saved under " + current_directory + "\\Enhanced\\Presets successfully.");
//                successModal.show();
//                nana::exec();
//            }
//        );
//    }
//
//    bool form_is_valid() {
//        return is_valid_tb_presetName() && is_valid_tb_presetFilename();
//    }
//
//    void validate_form()
//    {
//        if (!is_valid_tb_presetName()) {
//            lbl_invalidNameMessage->show();
//        }
//
//        if (!is_valid_tb_presetFilename()) {
//            lbl_invalidFilenameMessage->show();
//        }
//    }
//
//    bool is_valid_tb_presetName()
//    {
//        std::string text = tb_presetName->text();
//
//        if (!text.empty()) {
//            return true;
//        }
//
//        return false;
//    }
//
//    bool is_valid_tb_presetFilename()
//    {
//        std::string text = tb_presetFilename->text();
//
//        if (!dky::isValidFilename(text)) {
//            return false;
//        }
//
//        return true;
//    }
//
//    void fill_presetFilename_with_suggestion()
//    {
//        std::string presetName = tb_presetName->text();
//
//        if (!presetName.empty()) {
//            std::string suggestion = dky::convertToValidFilename(presetName);
//
//            tb_presetFilename->caption(suggestion);
//        }
//    }
//
//    void draw()
//    {
//        layout->div("margin=15 vert <weight=25 <weight=150 presetNameLabel> <margin=[0, 0, 0, 10] weight=160 presetFilenameLabel>>                                         \
//                                    <weight=40 <vert weight=150 <weight=20 presetNameInput><weight=20 margin=[2] <weight=150 presetInvalidNameMessage>>> <margin=[0, 0, 0, 10] vert weight=160 <weight=20 presetFilenameInput>         \
//                                                                                                       <weight=20 margin=[2] <weight=160 presetInvalidFilenameMessage>>>>  \
//                                                                                                                                                                           \
//                                    <margin=[5] weight=25 <weight=205 selectSettingsLabel>>                                                                                \
//                                    <margin=[10] vert includeOptions arrange=30>                                                                                           \
//                                    <weight=35 <><weight=60 saveBtn>>                                                                                                      ");
//
//        layout->field("presetNameLabel") << *lbl_presetName;
//        layout->field("presetNameInput") << *tb_presetName;
//        layout->field("presetInvalidNameMessage") << *lbl_invalidNameMessage;
//
//        layout->field("presetFilenameLabel") << *lbl_presetFilename;
//        layout->field("presetFilenameInput") << *tb_presetFilename;
//        layout->field("presetInvalidFilenameMessage") << *lbl_invalidFilenameMessage;
//
//        layout->field("selectSettingsLabel") << *lbl_select_settings_to_include;
//
//        layout->field("includeOptions") << *cb_include_mods
//                                        << *cb_include_patches
//                                        << *cb_include_customization
//                                        << *cb_include_keys;
//
//        layout->field("saveBtn") << *btn_save;
//
//        layout->collocate();
//    }
//
//    void load()
//    {
//        this->caption("Save as preset");
//        this->bgcolor(default_bgcolor);
//        lbl_presetName                ->bgcolor(default_bgcolor);
//        lbl_invalidNameMessage        ->bgcolor(default_bgcolor);
//
//        lbl_invalidNameMessage->format(true);
//        lbl_invalidNameMessage->hide();
//
//        lbl_presetFilename            ->bgcolor(default_bgcolor);
//        lbl_invalidFilenameMessage    ->bgcolor(default_bgcolor);
//        lbl_select_settings_to_include->bgcolor(default_bgcolor);
//        cb_include_mods               ->bgcolor(default_bgcolor);
//        cb_include_patches            ->bgcolor(default_bgcolor);
//        cb_include_customization      ->bgcolor(default_bgcolor);
//        cb_include_keys               ->bgcolor(default_bgcolor);
//
//        lbl_invalidFilenameMessage->format(true);
//        lbl_invalidFilenameMessage->hide();
//
//        tb_presetName->focus();
//        cb_include_mods->check(true);
//        cb_include_patches->check(true);
//        tb_presetName->focus();
//    }
//
//    void save_preset()
//    {
//        std::string presetName = tb_presetName->text();
//        std::string presetFilename = tb_presetFilename->text();
//
//        PresetOptions presetOptions;
//        presetOptions.IncludeMods = cb_include_mods->checked();
//        presetOptions.IncludePatches = cb_include_patches->checked();
//        presetOptions.IncludeCustomization = cb_include_customization->checked();
//        presetOptions.IncludeKeys = cb_include_keys->checked();
//
//        configurationUpdater->save_all();
//        settings->saveAsPreset(presetName, presetFilename, presetOptions);
//    }
//};
