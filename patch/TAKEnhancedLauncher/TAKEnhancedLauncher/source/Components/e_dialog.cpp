#include "TAKEnhancedLauncher/Components/e_dialog.hpp"

e_dialog::e_dialog(std::string title, std::string text, std::string helpText, nana::rectangle rect)
    : nana::form(rect, nana::appearance(1, 1, 1, 0, 0, 0, 1))
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