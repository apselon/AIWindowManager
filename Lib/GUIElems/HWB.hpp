#include "Button.hpp"

class HelloWorldButton: public AbstractRectButton {
protected:
    bool on_mouse_click(const Vector2d& pos) override;
    bool on_mouse_move(const Vector2d& pos) override;
    bool on_mouse_release(const Vector2d& pos) override;
public:
    HelloWorldButton(const Vector2d& pos, const Vector2d& size, const char* image);
};
