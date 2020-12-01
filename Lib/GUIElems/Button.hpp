#pragma once

#include "../Window/Window.hpp"
#include "../Aux/Auxiliary.hpp"
#include "../Engine/SFMLGraphics.hpp"

class AbstractRectButton: public RectWindow, public MouseReceptive {
public:
    AbstractRectButton();
    AbstractRectButton(const Vector2d& pos, const Vector2d& size);
    bool handle_event(const Event* event) override;
};

//================================================================================

class HelloWorldButton: public AbstractRectButton {
protected:
    bool on_mouse_click(const Vector2d& override)   override;
    bool on_mouse_move(const Vector2d& override)    override;
    bool on_mouse_release(const Vector2d& override) override;

public:
    HelloWorldButton(const Vector2d&, const Vector2d&);
};
