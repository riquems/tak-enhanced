#pragma once
#include "TAKEnhancedLauncher/nana_common.hpp"
#include <TAKEnhancedLauncher/binding.hpp>
#include <TAKEnhancedLauncher/Components/e_widget.hpp>

class e_panel : public nana::panel<false>
{
protected:
    std::shared_ptr<nana::place> layout;
    std::vector<std::shared_ptr<e_widget>> widgets;
    std::vector<std::shared_ptr<e_binding>> bindings;

public:
    e_panel(nana::window parent);

    void add_widget(std::shared_ptr<nana::widget> widget, std::string field = "");
    void add_binding(std::shared_ptr<e_binding> binding);
    void draw();
    void load();
    void reload();
    void save();
    void make_editable();
    void make_readonly();
};
