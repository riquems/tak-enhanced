#pragma once
#include "TAKEnhancedLauncher/nana_common.hpp"
#include <TAKEnhancedLauncher/binding.hpp>
#include <TAKEnhancedLauncher/Components/e_widget.hpp>

class e_form : public nana::form
{
protected:
    std::shared_ptr<nana::place> layout;
    std::vector<std::shared_ptr<e_widget>> widgets;
    std::vector<std::shared_ptr<e_binding>> bindings;

public:
    e_form(nana::rectangle rect, nana::appearance appearance);

    void add_widget(std::shared_ptr<nana::widget> widget, std::string field = "");
    void add_binding(std::shared_ptr<e_binding> binding);
    void draw();
    void load();
    void reload();
    void commit();
    std::function<void()> on_state_changed_callback = []() {};
    virtual void on_state_changed();
    void make_editable();
    void make_readonly();
};
