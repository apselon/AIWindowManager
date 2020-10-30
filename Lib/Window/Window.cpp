#include "Window.hpp"

bool AbstractWindow::handle_mouse_click(const Vector2d& click){

    return on_mouse_click(click);
}

bool AbstractWindow::handle_idle(){

    return on_idle();
}

AbstractWindow::~AbstractWindow(){
    //PASS;
}

//================================================================================

bool AbstractRenderWindow::handle_idle(){
    draw_at();
    return on_idle();
}

AbstractRenderWindow::~AbstractRenderWindow(){
    //PASS;
}

//================================================================================

void AbstractContainerWindow::add_subwindow(AbstractWindow* another) {
    subwindows.push_back(another);
}

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

AbstractContainerWindow::~AbstractContainerWindow() {
    /*
    for (auto sub: subwindows){
        delete sub;
    };
    */
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
