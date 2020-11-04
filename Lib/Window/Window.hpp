#pragma once
#include <ctime>
#include <cstdint>

#include "../Aux/Auxiliary.hpp"

class AbstractWindow;
class AbstractRenderWindow;
class AbstractContainerWindow;

//================================================================================

class AbstractWindow {
    friend AbstractRenderWindow;
    friend AbstractContainerWindow;

protected:
    list<AbstractWindow*> subwindows = list<AbstractWindow*>();

    virtual bool on_mouse_click  (const Vector2d& click) = 0;
    virtual bool on_mouse_move   (const Vector2d& dest)  = 0;
    virtual bool on_mouse_release(const Vector2d& pos)   = 0;
    /*
    virtual bool handle_timer(time_t timer)  = 0;
    virtual bool handle_resize(size_t new_w, size_t new_h)  = 0;
    virtual bool handle_key_pressed();
    */

public: 
    virtual bool handle_mouse_click  (const Vector2d& click);
    virtual bool handle_mouse_move   (const Vector2d& dest); 
    virtual bool handle_mouse_release(const Vector2d& click);
    virtual bool handle_redraw();

    virtual void add_subwindow(AbstractWindow* another);

    virtual ~AbstractWindow();
};

//================================================================================

class AbstractRenderWindow: public AbstractWindow {
    friend AbstractContainerWindow;

protected:
    virtual void on_redraw() = 0;

public:
    bool handle_redraw() override;
    virtual bool contains(const Vector2d& dot) = 0;
    //virtual ~AbstractRenderWindow();
};

//================================================================================

class IRect {

protected:
    Vector2d pos = Vector2d();
    Vector2sz size = Vector2sz();

public:
    IRect(const Vector2d& pos, const Vector2sz& size);
    IRect(double x, double y, size_t width, size_t height);
};
