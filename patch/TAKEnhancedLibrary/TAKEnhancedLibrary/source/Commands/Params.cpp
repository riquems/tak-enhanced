#include "TAKEnhancedLibrary/Commands/Params.hpp"

Params::Params() {}
Params::Params(std::initializer_list<Param> params) {
    for (auto param : params) {
        this->add(param);
    }
}

std::optional<std::string> Params::get(std::string key) {
    return this->params[key];
}

void Params::add(Param param) {
    this->add(param.key, param.value);
}

void Params::add(std::string key, std::string value) {
    this->params.insert(std::pair<std::string, std::string>(key, value));
}

uint Params::count() {
    return this->params.size();
}

std::unordered_map<std::string, std::string> Params::asUnorderedMap() {
    return params;
}
