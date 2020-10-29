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

bool AbstractWindow::handle_idle(){

    return on_idle();
}

//================================================================================

bool AbstractRenderWindow::handle_idle(){
    draw_at();
    return on_idle();
};

//================================================================================

void AbstractContainerWindow::add_subwindow(AbstractWindow* another) {
    subwindows.push_back(another);
}

/*
 * Для контейнера обработка нажатия --- диспетчеризация нажатия детям и, если надо, вызов своей реакции на нажатие.
 */
bool AbstractContainerWindow::handle_mouse_click(const Vector2d& click) {

    for (auto sub: subwindows){
        if(sub->handle_mouse_click(click)){
            return true;
        }
    }

    return on_mouse_click(click);
}

bool AbstractContainerWindow::handle_idle(){
    for (auto sub: subwindows){
        sub->handle_idle();
    }

    return on_idle();
}

//================================================================================

/*
 * bool AbstractRenderContainerWindow::handle_idle(){
 *     draw_at();
 *
 *     for (auto sub: subwindows){
 *         sub->handle_idle();
 *     }
 *
 *     return on_idle();
 * }
 */
