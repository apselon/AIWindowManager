#include "Window.hpp"

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
        sub->handle_mouse_release(m_pos);
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

IRect::IRect(const Vector2d& pos, const Vector2sz& size)
    :pos(pos), size(size) {}

IRect::IRect(double x, double y, size_t width, size_t height)
    :pos(x, y), size(width, height) {}
