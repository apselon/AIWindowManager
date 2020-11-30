#pragma once

#include "../Aux/Auxiliary.hpp"
#include "../Event/Event.hpp"
#include "Shape.hpp"
#include "Interface.hpp"

class AbstractWindow;
class AbstractRenderWindow;
class AbstractContainerWindow;

//================================================================================

class AbstractWindow {
    friend AbstractRenderWindow;
    friend AbstractContainerWindow;

protected:
    virtual bool dispatch_event(const Event& event);
    list<AbstractWindow*> subwindows = list<AbstractWindow*>();


public: 
    AbstractWindow() = default;
    virtual bool handle_event(const Event& event) = 0;
    virtual void add_subwindow(AbstractWindow* another);
    virtual ~AbstractWindow();
};

//================================================================================

template <class Shape>
class ShapedWindow: public AbstractWindow, public Drawable {
protected:
    Shape shape = {};
    void draw() override;
};

//================================================================================

using RectWindow = ShapedWindow<RectShape>;

//================================================================================

