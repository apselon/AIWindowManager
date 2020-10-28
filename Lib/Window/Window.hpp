#pragma once
#include <ctime>
#include <cstdint>

#include "vector.hpp"
#include "Primitives.hpp"
#include "Event.hpp"
#include "Auxiliary.hpp"

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
friend ContainerWindow;

protected:
    virtual void draw() {};
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
    void draw() override;
};

//================================================================================

