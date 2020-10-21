#include "Button.hpp"
#include "Primitives.hpp"

class AbstractLabeledRectButton: public AbstractButton {
    enum class ButtonState {IDLE, HOVERED, CLICKED};

private:
    ButtonState state = ButtonState::IDLE;
    Primitives::Rect state_shapes[3] = {}; 
    Primitives::Label button_label = Primitives::Label();

    Primitives::Rect& button_shape();

protected:
    void handle_mouse_click(double x, double y) override;
    void handle_mouse_move(double x, double y) override;
    void handle_timer(time_t timer) override;

public:
    void draw() override;
};

