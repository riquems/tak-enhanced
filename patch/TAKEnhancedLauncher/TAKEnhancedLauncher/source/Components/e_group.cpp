#include "TAKEnhancedLauncher/components/e_group.hpp"
#include "Utils/TypeExtensions.hpp"

e_group::e_group(
    nana::window parent,
    std::string title
) : nana::group(parent, title) {
    this->is_loading = true;
    this->layout = std::make_shared<nana::place>(*this);
}

void e_group::add_widget(std::shared_ptr<nana::widget> widget, std::string field) {
    if (is<nana::combox>(*widget)) {
        auto combox = std::dynamic_pointer_cast<nana::combox>(widget);

        combox->events().text_changed([&]() {
            this->on_state_changed();
        });
    }
    else if (is<nana::checkbox>(*widget)) {
        auto checkbox = std::dynamic_pointer_cast<nana::checkbox>(widget);

        checkbox->events().checked([&]() {
            this->on_state_changed();
        });
    }
    else if (is<nana::textbox>(*widget)) {
        auto textbox = std::dynamic_pointer_cast<nana::textbox>(widget);

        textbox->events().text_changed([&]() {
            this->on_state_changed();
        });
    }
    else if (is<nana::spinbox>(*widget)) {
        auto spinbox = std::dynamic_pointer_cast<nana::spinbox>(widget);

        spinbox->events().text_changed([&]() {
            this->on_state_changed();
        });
    }

    this->widgets.push_back(std::make_shared<e_widget>(widget, field));
}

void e_group::add_binding(std::shared_ptr<e_binding> binding) {
    this->bindings.push_back(binding);
}

void e_group::draw()
{
    for (auto& widget : this->widgets) {
        if (widget->field != "")
            this->layout->field(widget->field.c_str()) << *(widget->raw);
    }

    layout->collocate();
}

void e_group::load()
{
    this->is_loading = true;

    for (auto& binding : this->bindings) {
        binding->reflect();
    }

    this->is_loading = false;
}

void e_group::reload()
{
    this->load();
}


void e_group::commit()
{
    for (auto& binding : this->bindings) {
        binding->commit();
    }
}

void e_group::on_state_changed() {
    if (this->is_loading)
        return;

    this->on_state_changed_callback();
}

void e_group::make_editable()
{
    for (auto& widget : this->widgets) {
        widget->enabled(true);
    }
}

void e_group::make_readonly()
{
    for (auto& widget : this->widgets) {
        widget->enabled(false);
    }
}
