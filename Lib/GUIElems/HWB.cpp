#include "HWB.hpp"

HelloWorldButton::HelloWorldButton(const Vector2d& pos, const Vector2d& size, const char* img)
    :AbstractRectButton(pos, size, img) {}

bool HelloWorldButton::on_mouse_move(const Vector2d& pos) {
        printf("Moved\n");
            return true;
}

bool HelloWorldButton::on_mouse_click(const Vector2d& pos) {
        printf("Clicked\n");
            return true;
}

bool HelloWorldButton::on_mouse_release(const Vector2d& pos) {
        printf("Release\n");
            return true;
}
