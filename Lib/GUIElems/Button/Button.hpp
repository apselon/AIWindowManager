#pragma once

#include "Window.hpp"


class AbstractButton: public AbstractWindow {
protected:
    virtual void callback(void) = 0;
};

//=============================================================================

class AbstractLabeledRectButton: public AbstractButton {
    enum class ButtonState {IDLE, HOVERED, CLICKED};

private:
    ButtonState state = ButtonState::IDLE;
    Primitives::Rect state_shapes[3] = {};
    Primitives::Label button_label = Primitives::Label();

    Primitives::Rect& button_shape();

protected:
    void handle_mouse_click(double x, double y) override;
public:
    void draw() override;
};


