#pragma once
#include "TAKEnhancedDll/Launcher/nana_common.hpp"

class e_dialog : public nana::form
{
    std::shared_ptr<nana::place> layout;
    std::shared_ptr<nana::label> lbl_text;
    std::shared_ptr<nana::label> lbl_helpText;

public:
    e_dialog(std::string title, std::string text, std::string helpText, nana::rectangle rect) : nana::form(rect, nana::appearance(1, 1, 1, 0, 0, 0, 1))
    {
        this->caption(title);
        this->bgcolor(default_bgcolor);

        layout = std::make_shared<nana::place>(*this);

        lbl_text = std::make_shared<nana::label>(*this, text);
        lbl_helpText = std::make_shared<nana::label>(*this, helpText);
        lbl_text->text_align(nana::align::center);
        lbl_helpText->text_align(nana::align::center);

        layout->div("margin=10 vert         <>                \
                                      <<><lblText><>>         \
                                       <lblHelpText>          ");

        layout->field("lblText") << *lbl_text;
        layout->field("lblHelpText") << *lbl_helpText;
        layout->collocate();
    }
};