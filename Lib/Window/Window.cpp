#include "Window.hpp"

size_t AbstractWindow::id() {
    return window_id;
};

//================================================================================

/*
 * Для обычного окна вся суть рендеринга --- отрисовка себя.
 */
void RenderWindow::render_at(RenderWindow& to_render_at){
    draw_at(to_render_at);
}

//================================================================================

void ContainerWindow::add_subwindow(RenderWindow* another) {
    subwindows.push_back(another);
}

bool ContainerWindow::handle_mouse_click(double x, double y) {

    for (auto sub: subwindows){
        if(sub->handle_mouse_click(x, y)){
            return true;
        }
    }

    return false;
}

/*
 * Для контейнера рендеринг это отрисовка себя и рендеринг своих детей.
 */

void ContainerWindow::render_at(RenderWindow& to_render_at) {

    draw_at(to_render_at);

    for (auto sub: subwindows){
        sub->render_at(*this);
    }
};

//================================================================================
