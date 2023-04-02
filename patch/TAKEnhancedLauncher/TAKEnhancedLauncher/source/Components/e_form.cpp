#include "TAKEnhancedLauncher/Components/e_form.hpp"
#include "Utils/TypeExtensions.hpp"

e_form::e_form(nana::rectangle rect, nana::appearance appearance) : nana::form(rect, appearance) {
    layout = std::make_shared<nana::place>(*this);
}

void e_form::add_widget(std::shared_ptr<nana::widget> widget, std::string field) {
    if (
        is_not<nana::combox>(*widget)
     && is_not<nana::button>(*widget)
     && is_not<nana::spinbox>(*widget)
     && is_not<nana::listbox>(*widget)
    ) {
        widget->bgcolor(default_bgcolor);
    }

    this->widgets.push_back(std::make_shared<e_widget>(widget, field));
}

void e_form::add_binding(std::shared_ptr<e_binding> binding) {
    this->bindings.push_back(binding);
}

void e_form::draw()
{
    for (auto& widget : this->widgets) {
        if (widget->field != "")
            this->layout->field(widget->field.c_str()) << *(widget->raw);
    }

    layout->collocate();
}

void e_form::load()
{
    for (auto& binding : this->bindings) {
        binding->reflect();
    }
}

void e_form::reload()
{
    this->load();
}

void e_form::save()
{
    for (auto& binding : this->bindings) {
        binding->commit();
    }
}

void e_form::make_editable()
{
    for (auto& widget : this->widgets) {
        widget->enabled(true);
    }
}

void e_form::make_readonly()
{
    for (auto& widget : this->widgets) {
        widget->enabled(false);
    }
}
