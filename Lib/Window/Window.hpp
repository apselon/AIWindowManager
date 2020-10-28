#pragma once
#include <ctime>
#include <cstdint>

#include "../Aux/Auxiliary.hpp"

class AbstractWindow;
class RenderWindow;
class ContainerWindow;

//================================================================================

class AbstractWindow {
    friend RenderWindow;
    friend ContainerWindow;

private:
    size_t window_id = 0;

protected:
    virtual bool handle_mouse_click(double x, double y)  = 0;
    /*
    virtual bool handle_mouse_move(double x, double y)  = 0;
    virtual bool handle_timer(time_t timer)  = 0;
    virtual bool handle_resize(size_t new_w, size_t new_h)  = 0;
    virtual bool handle_key_pressed();
    */
    size_t id();
};


//================================================================================

class RenderWindow: public AbstractWindow {
/*!
 * Окно, которое может быть нарисовано внутри другого окна.
 */
friend ContainerWindow;

protected:
    virtual void render_at(RenderWindow& to_render_at);
    virtual void draw_at(RenderWindow& to_draw_at) = 0;
};

//================================================================================

class ContainerWindow: public RenderWindow {
//Winndow that sends its events to subwindows.
private:
    list<RenderWindow*> subwindows = list<RenderWindow*>();

public:
    ContainerWindow() = default;
    ContainerWindow(const ContainerWindow& another);
    ContainerWindow(ContainerWindow&& another);

    void add_subwindow(RenderWindow* another);
    bool handle_mouse_click(double x,  double y) override;
    void render_at(RenderWindow& to_render_at) override;
};

//================================================================================

