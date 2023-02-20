#include "TAKEnhancedLauncher/tab_pages/e_panel.hpp"

e_panel::e_panel(nana::window parent) : nana::panel<false>(parent) {
    layout = std::make_unique<nana::place>(*this);
}

void e_panel::add_widget(std::shared_ptr<nana::widget> widget, std::string field) {
    widget->bgcolor(default_bgcolor);
    this->widgets.push_back(std::make_shared<e_widget>(widget, field));
}

void e_panel::add_binding(std::shared_ptr<e_binding> binding) {
    this->bindings.push_back(binding);
}

void e_panel::draw()
{
    for (auto& widget : this->widgets) {
        if (widget->field != "")
            this->layout->field(widget->field.c_str()) << *(widget->raw);
    }

    layout->collocate();
}

void e_panel::load()
{
    for (auto& binding : this->bindings) {
        binding->reflect();
    }
}

void e_panel::reload()
{
    this->load();
}


void e_panel::save()
{
    for (auto& binding : this->bindings) {
        binding->commit();
    }
}

void e_panel::make_editable()
{
    for (auto& widget : this->widgets) {
        widget->enabled(true);
    }
}

void e_panel::make_readonly()
{
    for (auto& widget : this->widgets) {
        widget->enabled(false);
    }
}
