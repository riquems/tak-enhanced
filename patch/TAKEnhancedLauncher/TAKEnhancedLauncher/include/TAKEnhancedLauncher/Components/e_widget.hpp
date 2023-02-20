#pragma once
#include "TAKEnhancedLauncher/nana_common.hpp"

class e_widget
{
public:
    std::shared_ptr<nana::widget> raw;
    std::any entity_bound;
    std::string field;

    e_widget(std::shared_ptr<nana::widget> widget, std::string field);
    void enabled(bool value);
};
