#include "Window.hpp"

bool AbstractWindow::handle_mouse_click(const Vector2d& click){

    return on_mouse_click(click);
}

bool AbstractWindow::handle_redraw(){
    return false; 
}

bool AbstractWindow::handle_mouse_move(const Vector2d& dest){
    return on_mouse_move(dest); 
}

AbstractWindow::~AbstractWindow(){
    //PASS;
}

//================================================================================

bool AbstractRenderWindow::handle_redraw(){
    draw_at();
    return true;
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

bool AbstractContainerWindow::handle_mouse_move(const Vector2d& dest) {

    for (auto sub: subwindows){
        if(sub->handle_mouse_move(dest)){
            return true;
        }
    }

    return on_mouse_move(dest);
}

bool AbstractContainerWindow::handle_redraw(){
    for (auto sub: subwindows){
        sub->handle_redraw();
    }

    return true;
}

AbstractContainerWindow::~AbstractContainerWindow() {
    for (auto sub: subwindows){
        delete sub;
    };
}

//================================================================================

/*
bool AbstractRenderContainerWindow::handle_redraw(){
    draw_at();

    for (auto sub: subwindows){
        sub->handle_redraw();
    }

    return on_redraw();
    
}
*/
