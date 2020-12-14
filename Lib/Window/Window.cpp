#include "Window.hpp"
#include "../../Lib/Engine/SFMLGraphics.hpp"


bool AbstractWindow::dispatch_event(const Event* event)
{
    for (auto sub: subwindows) {
        if (sub->handle_event(event)) {
            return true;
        }
    }

    return false;
}

void AbstractWindow::add_subwindow(AbstractWindow* another)
{
    subwindows.push_back(another);
}

AbstractWindow::~AbstractWindow()
{
    for (auto sub: subwindows) {
        sub->~AbstractWindow();
        delete sub;
        sub = nullptr;
    }
}

//================================================================================

bool DesktopWindow::handle_event(const Event* event)
{
    if (dispatch_event(event)) {
        return true;
    }

    return false;
}

//================================================================================

template <class Shape>
ShapedWindow<Shape>::ShapedWindow(const Shape& shape)
    :shape(shape) {}

template <class Shape>
void ShapedWindow<Shape>::draw()
{
    shape.draw();
}

template class ShapedWindow<RectSprite>;
//================================================================================


