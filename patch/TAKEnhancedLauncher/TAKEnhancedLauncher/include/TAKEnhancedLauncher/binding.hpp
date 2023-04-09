#pragma once
#include "TAKEnhancedLauncher/nana_common.hpp"
#include <functional>

struct e_binding
{
    std::function<void()> reflect;
    std::function<void()> commit;
};

std::shared_ptr<e_binding> create_binding(const std::function<void()>& reflect, const std::function<void()>& commit);
std::shared_ptr<e_binding> create_checkbox_binding(std::shared_ptr<nana::checkbox>& cb, bool& entity);
std::shared_ptr<e_binding> create_spinbox_binding(std::shared_ptr<nana::spinbox>& sb, uint& entity);
std::shared_ptr<e_binding> create_listbox_binding(std::shared_ptr<nana::listbox>& lb, std::vector<std::string>& entity);

template<typename T>
std::shared_ptr<e_binding> create_combox_binding(std::shared_ptr<nana::combox>& cbb, T& entity, uint enumOffset = 1) {
    auto reflect = [&, enumOffset]() -> void {
        cbb->option(entity - enumOffset);
    };

    auto commit = [&, enumOffset]() -> void {
        if (cbb->enabled())
            entity = (T)(cbb->option() + enumOffset);
    };

    return create_binding(reflect, commit);
}

std::shared_ptr<e_binding> create_combox_binding(std::shared_ptr<nana::combox>& cbb, std::string& entity);
