#pragma once
#include "../Aux/Auxiliary.hpp"

class MouseReceptive {
protected:
    virtual bool on_mouse_click  (const Vector2d& click) = 0;
    virtual bool on_mouse_release(const Vector2d& pos)   = 0;
    virtual bool on_mouse_move   (const Vector2d& dest)  = 0;
};

//================================================================================

class Drawable {
protected:
    virtual void draw() = 0;
};

//================================================================================

class Draggable: public MouseReceptive {
protected:
    
    bool is_pressed = false;

    bool on_mouse_click(const Vector2d& pos)   override;
    bool on_mouse_move(const Vector2d& pos)    override;
    bool on_mouse_release(const Vector2d& pos) override;

    virtual void drag_to() = 0;
};

