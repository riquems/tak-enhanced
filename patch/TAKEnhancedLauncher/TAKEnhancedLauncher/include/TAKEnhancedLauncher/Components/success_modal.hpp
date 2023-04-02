#pragma once
#include "TAKEnhancedLauncher/nana_common.hpp"

class success_modal : public nana::form
{
public:
    success_modal(uint width, uint height, std::string message);

    void initialize();
    void load();
    void draw();


private:
    std::shared_ptr<nana::place> layout;

    std::shared_ptr<nana::label> lbl_successMessage;
    std::shared_ptr<nana::button> btn_ok;

    std::string message;
};
