#pragma once

#include "../Window/Window.hpp"
#include "../Aux/Auxiliary.hpp"
#include "../Engine/SFMLGraphics.hpp"

class AbstractRectButton: public AbstractRenderWindow {
private:
    Vector2d pos   = Vector2d();    
    Vector2sz size = Vector2sz();
    bool contains(const Vector2d& point);

public:
    AbstractRectButton();
    AbstractRectButton(double x, double y, size_t width, size_t height);
    AbstractRectButton(const Vector2d& pos, const Vector2sz& size);

    void draw_at() override;
    bool on_mouse_click(const Vector2d& click) override;
    bool on_idle() override;

    virtual void on_press() = 0;
};

//================================================================================

class HelloWorldButton: public AbstractRectButton {
public:
    HelloWorldButton(double x, double y, size_t width, size_t height);
    void on_press() override;
};
