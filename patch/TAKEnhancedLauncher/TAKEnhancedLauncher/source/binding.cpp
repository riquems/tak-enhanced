#include "TAKEnhancedLauncher/binding.hpp"


std::shared_ptr<e_binding> create_binding(const std::function<void()>& reflect, const std::function<void()>& commit) {
    return std::make_shared<e_binding>(e_binding{
        .reflect = reflect,
        .commit = commit
    });
}

std::shared_ptr<e_binding> create_checkbox_binding(std::shared_ptr<nana::checkbox>& cb, bool& entity) {
    auto reflect = [&]() -> void {
        cb->check(entity);
    };

    auto commit = [&]() -> void {
        entity = cb->checked();
    };

    return create_binding(reflect, commit);
}

std::shared_ptr<e_binding> create_spinbox_binding(std::shared_ptr<nana::spinbox>& sb, uint& entity) {
    auto reflect = [&]() -> void {
        sb->value(std::to_string(entity));
    };

    auto commit = [&]() -> void {
        entity = sb->to_int();
    };

    return create_binding(reflect, commit);
}

std::shared_ptr<e_binding> create_listbox_binding(std::shared_ptr<nana::listbox>& lb, std::vector<std::string>& entity) {
    auto reflect = [&]() -> void {
        nana::listbox::cat_proxy default_category = lb->at(0);

        for (std::string item : entity) {
            default_category.append(item);
        }
    };

    auto commit = [&]() -> void {
        entity.clear();

        std::vector<std::string> items;

        nana::listbox::index_pairs items_index_pairs = lb->items();

        for (nana::listbox::index_pair item_index_pairs : items_index_pairs) {
            std::string item = lb->at(item_index_pairs).text(0);

            items.push_back(item);
        }

        for (std::string item : items) {
            entity.push_back(item);
        }
    };

    return create_binding(reflect, commit);
}

std::shared_ptr<e_binding> create_combox_binding(std::shared_ptr<nana::combox>& cbb, std::string& entity) {
    auto reflect = [&]() -> void {
        for (int i = 0; i < cbb->the_number_of_options(); i++) {
            if (cbb->text(i) == entity) {
                cbb->option(i);
                break;
            }
        }
    };

    auto commit = [&]() -> void {
        if (cbb->enabled())
            entity = cbb->text(cbb->option());
    };

    return create_binding(reflect, commit);
}