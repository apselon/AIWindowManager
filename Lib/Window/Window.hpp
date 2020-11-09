#pragma once
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

public: 
    virtual bool handle_mouse_move   (const Vector2d& dest); 
    virtual bool handle_mouse_click  (const Vector2d& click);
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
    virtual bool contains(const Vector2d& point) = 0;
    //virtual ~AbstractRenderWindow();
};

//================================================================================

class AbstractRectWindow: public AbstractRenderWindow {

protected:
    Vector2d pos   = Vector2d();
    Vector2d size = Vector2d();

    void on_redraw() override;
    bool contains(const Vector2d& point) override;

public:
    AbstractRectWindow(const Vector2d& pos, const Vector2d& size);
};

//================================================================================

class DraggableRectWindow: public AbstractRectWindow {

private:
    bool pressed_flag = false;
    const Vector2d direction_vect = {};
    Vector2d old_pos = {}; 
    Vector2d drag_rel_pos = {};

protected:
    bool on_mouse_click(const Vector2d& click) override;
    bool on_mouse_move(const Vector2d& move) override;
    bool on_mouse_release(const Vector2d& pos) override;

public:
    DraggableRectWindow(const Vector2d& pos, const Vector2d& size, const Vector2d& dir = {});
};

