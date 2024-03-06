#pragma once
#include "TAKEnhancedLauncher/nana_common.hpp"

class e_prompt : public nana::form
{
    std::shared_ptr<nana::place> layout;
    std::shared_ptr<nana::textbox> tb_input;
    std::shared_ptr<nana::button> btn_save;

public:
    std::function<void(std::string)> on_save;

    e_prompt(std::string title, std::string currentValue, nana::rectangle rect);
};
