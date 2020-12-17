#include "Button.hpp"
#include "../Engine/SFMLGraphics.hpp"

AbstractRectButton::AbstractRectButton(const Vector2d& pos, 
                                       const Vector2d& size, const char* image)
    :RectWindow({pos, size, image}) {}

bool AbstractRectButton::handle_event(const Event* event) {
    if (event == nullptr) return false;

    Vector2d pos = {};

    switch (event->get_type()) {
        case EventType::MouseMove:
            pos = dynamic_cast<const MouseEvent*>(event)->get_pos();
            if (shape.contains(pos)) {
                on_mouse_move(pos);
                delete event;
                return true;
            }
            break;

        case EventType::MouseClick:
            pos = dynamic_cast<const MouseEvent*>(event)->get_pos();
            if (shape.contains(pos)) {
                on_mouse_click(pos);
                delete event;
                return true;
            }
            break;

        case EventType::MouseRelease:
            pos = dynamic_cast<const MouseEvent*>(event)->get_pos();
            if (shape.contains(pos)) {
                on_mouse_release(pos);
                delete event;
                return true;
            }

            break;

        case EventType::Redraw:
            draw();
            break;

        default:
            return false;
    }

    return false;
}

//================================================================================

