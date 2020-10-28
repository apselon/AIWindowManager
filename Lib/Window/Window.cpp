#include "Window.hpp"

size_t AbstractWindow::id() {
    return window_id;
};

/*
 * Для обычного окна обработка нажатия --- вызов реакции на нажатие. 
 */
bool AbstractWindow::handle_mouse_click(const Vector2d& click){

    return on_mouse_click(click);
}

//================================================================================

/*
 * Для обычного окна рендеринг --- отрисовка себя.
 */
void RenderWindow::render_at(RenderWindow& to_render_at){
    draw_at(to_render_at);
}

//================================================================================

void ContainerWindow::add_subwindow(RenderWindow* another) {
    subwindows.push_back(another);
}

/*
 * Для контейнера обработка нажатия --- диспетчеризация нажатия детям и, если надо, вызов своей реакции на нажатие.
 */
bool ContainerWindow::handle_mouse_click(const Vector2d& click) {

    for (auto sub: subwindows){
        if(sub->handle_mouse_click(click)){
            return true;
        }
    }

    return on_mouse_click(click);
}

/*
 * Для контейнера рендеринг --- отрисовка себя и рендеринг своих детей.
 */

void ContainerWindow::render_at(RenderWindow& to_render_at) {

    draw_at(to_render_at);

    for (auto sub: subwindows){
        sub->render_at(*this);
    }
};

//================================================================================
