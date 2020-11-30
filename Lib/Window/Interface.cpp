#include "Interface.hpp"

bool Draggable::on_mouse_move(const Vector2d& pos)
{
    is_pressed = true;
    return true;
}

bool Draggable::on_mouse_release(const Vector2d& pos)
{
    if (is_pressed) {
        is_pressed = false;
        return true;
    }

    return false;
}

bool on_mouse_move(const Vector2d& pos) {
    if (!is_pressed) return false;
    drag_to(pos);
}
