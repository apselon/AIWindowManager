#include "Window.hpp"

size_t AbstractWindow::id() {
    return window_id;
};

//================================================================================

void ContainerWindow::add_subwindow(RenderWindow* another){
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

void ContainerWindow::draw(){
    
    for (auto sub: subwindows){
        sub->draw();
    }
}

//================================================================================
