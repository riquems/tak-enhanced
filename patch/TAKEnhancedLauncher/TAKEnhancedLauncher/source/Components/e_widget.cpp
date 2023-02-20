#include "TAKEnhancedLauncher/Components/e_widget.hpp"
#include "Utils/TypeExtensions.hpp"

e_widget::e_widget(std::shared_ptr<nana::widget> widget, std::string field)
    : raw(widget), field(field)
{

}

void e_widget::enabled(bool value) {
    this->raw->enabled(value);

    if (is<nana::listbox>(*this->raw)) {
        if (value) {
            this->raw->bgcolor(nana::color(255, 255, 255, 1));
        }
        else {
            this->raw->bgcolor(nana::color(225, 225, 225, 1));
        }
    }
}
