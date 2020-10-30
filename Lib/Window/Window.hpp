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
    virtual bool on_mouse_click(const Vector2d& click) = 0;
    virtual bool on_idle() = 0;
    /*
    virtual bool handle_mouse_move(double x, double y)  = 0;
    virtual bool handle_timer(time_t timer)  = 0;
    virtual bool handle_resize(size_t new_w, size_t new_h)  = 0;
    virtual bool handle_key_pressed();
    */

public: 
    virtual bool handle_mouse_click(const Vector2d& click);
    virtual bool handle_idle();
    virtual ~AbstractWindow();
};

//================================================================================

class AbstractRenderWindow: public AbstractWindow {
/*!
 * Окно, которое может быть нарисовано внутри другого окна.
 */
friend AbstractContainerWindow;

public:
    bool handle_idle() override;
    virtual void draw_at() = 0;
    virtual ~AbstractRenderWindow();
};

//================================================================================

class AbstractContainerWindow: public AbstractWindow {
//Winndow that sends its events to subwindows.
private:
    list<AbstractWindow*> subwindows = list<AbstractWindow*>();

public:
    AbstractContainerWindow() = default;
    AbstractContainerWindow(const AbstractContainerWindow& another);
    AbstractContainerWindow(AbstractContainerWindow&& another);

    void add_subwindow(AbstractWindow* another);
    bool handle_mouse_click(const Vector2d& click) override;
    bool handle_idle() override;

    virtual  ~AbstractContainerWindow();
};

//================================================================================

/* Dimond-shaped inheritance.
class AbstractRenderContainerWindow: AbstractContainerWindow, AbstractRenderWindow {
     
};
*/

//================================================================================
