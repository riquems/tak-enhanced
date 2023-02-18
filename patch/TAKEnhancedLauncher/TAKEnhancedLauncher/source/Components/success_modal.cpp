#pragma once
#include "TAKEnhancedLauncher/Components/success_modal.hpp"

success_modal::success_modal(uint width, uint height, std::string message)
    : nana::form(nana::API::make_center(width, height), nana::appearance(1, 1, 1, 0, 0, 0, 0))
{
    this->message = message;

    initialize();
    load();
    draw();
}

void success_modal::initialize()
{
    layout = std::make_shared<nana::place>(*this);
    lbl_successMessage = std::make_shared<nana::label>(*this);
    btn_ok = std::make_shared<nana::button>(*this);

    btn_ok->events().click(
        [&]() {
            this->close();
        }
    );
}

void success_modal::load()
{
    this->caption("Success!");
    lbl_successMessage->format(true);
    lbl_successMessage->caption(message);
    lbl_successMessage->text_align(nana::align::center);
    btn_ok->caption("Ok");

    this              ->bgcolor(default_bgcolor);
    lbl_successMessage->bgcolor(default_bgcolor);
}

void success_modal::draw()
{
    layout->div("margin=[30, 15, 15, 15] vert <successMessage> <weight=35 <> <weight=65 okBtn>>");

    layout->field("successMessage") << *lbl_successMessage;
    layout->field("okBtn") << *btn_ok;

    layout->collocate();
}
