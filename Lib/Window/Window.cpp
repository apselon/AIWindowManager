#include "Window.hpp"
#include "../../Lib/Engine/SFMLGraphics.hpp"

bool AbstractWindow::handle_redraw() {
    for (auto sub: subwindows) {
        sub->handle_redraw();
    }

    return true;
}

bool AbstractWindow::handle_mouse_click(const Vector2d& click) {
    for (auto sub: subwindows) {
        if(sub->handle_mouse_click(click)) {
            return true;
        }
    }

    return on_mouse_click(click);
}

bool AbstractWindow::handle_mouse_move(const Vector2d& dest) {
    for (auto sub: subwindows) {
        if(sub->handle_mouse_move(dest)) {
            return true;
        }
    }

    return on_mouse_move(dest);
}

bool AbstractWindow::handle_mouse_release(const Vector2d& m_pos) {
    for (auto sub: subwindows) {
        if(sub->handle_mouse_release(m_pos)) {
            return true;
        }

        return on_mouse_release(m_pos);
    }

    return on_mouse_release(m_pos);
}

void AbstractWindow::add_subwindow(AbstractWindow* another) {
    subwindows.push_back(another);
}

AbstractWindow::~AbstractWindow() {
    for (auto sub: subwindows) {
        sub->~AbstractWindow();
        delete sub;
        sub = nullptr;
    }
}

//================================================================================

bool AbstractRenderWindow::handle_redraw() {
    for (auto sub: subwindows) {
        sub->handle_redraw();
    }

    on_redraw();
    return true;
}

//================================================================================

AbstractRectWindow::AbstractRectWindow(const Vector2d& pos, const Vector2d& size)
    :pos(pos), size(size){}

void AbstractRectWindow::on_redraw() {
    //GraphicSystem::draw_texture(texture, pos, size);
    GraphicSystem::draw_rect(pos, size);
}

bool AbstractRectWindow::contains(const Vector2d& point) {
    return (pos.x <= point.x && point.x <= pos.x + size.x) &&
           (pos.y <= point.y && point.y <= pos.y + size.y);
}

//================================================================================

DraggableRectWindow::DraggableRectWindow(const Vector2d& pos, const Vector2d& size, 
                                         const Vector2d& dir) 
    :AbstractRectWindow(pos, size), direction_vect(dir) {}

bool DraggableRectWindow::on_mouse_click(const Vector2d& click) {
    if (!contains(click)) return false;

    pressed_flag = true;
    old_pos = pos;
    drag_rel_pos = {click.x - pos.x, click.y - pos.y};

    return true;
}

bool DraggableRectWindow::on_mouse_release(const Vector2d& click) {
    if (!contains(click)) return false;

    pressed_flag = false;

    return true;
}

bool DraggableRectWindow::on_mouse_move(const Vector2d& click) {
    if (!contains(click) || !pressed_flag) return false;

    pos = pos + (direction_vect * ((click - pos - drag_rel_pos) ^ direction_vect));

    return true;
}
