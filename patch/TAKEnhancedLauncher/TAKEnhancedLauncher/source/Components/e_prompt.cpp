#include "TAKEnhancedLauncher/components/e_prompt.hpp"
#include "TAKEnhancedLibrary/Keys/KeyComparator.hpp"
#include "TAKEnhancedLibrary/Keys/Keys.hpp"

e_prompt::e_prompt(std::string title, std::string currentValue, nana::rectangle rect)
    : nana::form(rect, nana::appearance(1, 1, 1, 0, 0, 0, 1))
{
    this->caption(title);
    this->bgcolor(default_bgcolor);

    layout = std::make_shared<nana::place>(*this);
    tb_input = std::make_shared<nana::textbox>(*this, currentValue);
    tb_input->multi_lines(false);
    tb_input->text_align(nana::align::center);
    tb_input->focus();
    tb_input->select(true);

    btn_save = std::make_shared<nana::button>(*this, "Save");

    btn_save->events().click(
        [&]() {
            std::string value = this->tb_input->text();
            this->on_save(value);
        }
    );

    this->tb_input->events().key_press(
        [&](nana::arg_keyboard args) {
            if (KeyComparator::isLike(args.key, Keys::Return)) {
                nana::API::emit_event(nana::event_code::click, *this->btn_save, nana::arg_click());
            }
        }
    );

    layout->div("margin=10                       \
        <vert gap=10                             \
            <>                                   \
            <weight=20 <><weight=130 tbInput><>> \
            <>                                   \
            <weight=30 <><weight=60 btnSave><>>  \
        >"
    );

    layout->field("tbInput") << *tb_input;
    layout->field("btnSave") << *btn_save;

    layout->collocate();
}
