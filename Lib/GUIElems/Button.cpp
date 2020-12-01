#include "Button.hpp"
#include "../Engine/SFMLGraphics.hpp"

AbstractRectButton::AbstractRectButton(const Vector2d& pos, const Vector2d& size)
    :RectWindow({pos, size}) {}

bool AbstractRectButton::handle_event(const Event* event) {
    if (event == nullptr) return false;

    switch (event->get_type()) {
        case EventType::MouseMove:
            if (on_mouse_move(dynamic_cast<const MouseEvent*>(event)->get_pos())) {
                delete event;
                return true;
            }

            break;

        case EventType::MouseClick:
            if (on_mouse_click(dynamic_cast<const MouseEvent*>(event)->get_pos())) {
                delete event;
                return true;
            }

            break;

        case EventType::MouseRelease:
            if (on_mouse_release(dynamic_cast<const MouseEvent*>(event)->get_pos())) {
                delete event;
                return true;
            }

            break;

        case EventType::Redraw:
            draw();
            delete event;
            break;

        default:
            return false;
    }

    return false;
}

//================================================================================

HelloWorldButton::HelloWorldButton(const Vector2d& pos, const Vector2d& size)
    :AbstractRectButton(pos, size) {}

bool HelloWorldButton::on_mouse_move(const Vector2d& pos) {
    if (!shape.contains(pos)) return false;
    printf("Moved\n");
    return true;
}

bool HelloWorldButton::on_mouse_click(const Vector2d& pos) {
    if (!shape.contains(pos)) return false;
    printf("Clicked\n");
    return true;
}

bool HelloWorldButton::on_mouse_release(const Vector2d& pos) {
    if (!shape.contains(pos)) return false;
    printf("Release\n");
    return true;
}
