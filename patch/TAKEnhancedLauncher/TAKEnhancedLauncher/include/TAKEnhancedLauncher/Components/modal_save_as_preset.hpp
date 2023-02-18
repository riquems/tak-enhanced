#pragma once

#include "TAKEnhancedLauncher/nana_common.hpp"
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
//    modal_save_as_preset(main_form* configurationUpdater, Settings* settings);
//
//    void initialize();
//    bool form_is_valid();
//    void validate_form();
//    bool is_valid_tb_presetName();
//    bool is_valid_tb_presetFilename();
//    void fill_presetFilename_with_suggestion();
//    void draw();
//    void load();
//
//    void save_preset();
//};
