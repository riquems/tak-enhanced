#pragma once
#include "TAKEnhancedLauncher/nana_common.hpp"

class e_dialog : public nana::form
{
    std::shared_ptr<nana::place> layout;
    std::shared_ptr<nana::label> lbl_text;
    std::shared_ptr<nana::label> lbl_helpText;

public:
    e_dialog(std::string title, std::string text, std::string helpText, nana::rectangle rect);
};
