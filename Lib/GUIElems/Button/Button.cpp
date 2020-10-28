#include "Button.hpp"

Primitives::Rect& AbstractLabeledRectButton::button_shape() {
    return state_shapes[static_cast<int>(state)];
};

void AbstractLabeledRectButton::draw() {
    button_shape().draw();
}

void AbstractLabeledRectButton::handle_mouse_click(double x, double y) {

    if (button_shape().contains(x, y)) {
        state = ButtonState::CLICKED;
        draw();
        callback();
    }
}

/*
void AbstractLabeledRectButton::handle_mouse_move(double x, double y) {

    if (button_shape().contains(x, y)) {
        state = ButtonState::HOVERED;
        draw();
    }
}

void AbstractLabeledRectButton::handle_timer(time_t) {
    //PASS;
}
*/
