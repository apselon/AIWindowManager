#include "Button.hpp"
#include "../Engine/SFMLGraphics.hpp"

AbstractRectButton::AbstractRectButton() = default;

bool AbstractRectButton::contains(const Vector2d& point){
    return (pos.x <= point.x && point.x <= pos.x + static_cast<double>(size.x)) &&
           (pos.y <= point.y && point.y <= pos.y + static_cast<double>(size.y));
}

AbstractRectButton::AbstractRectButton(double x, double y, size_t width, size_t height)
    :pos(x, y), size(width, height){}

AbstractRectButton::AbstractRectButton(const Vector2d& pos, const Vector2sz& size)
    :pos(pos), size(size){}

void AbstractRectButton::draw_at() {
    GraphicSystem::draw_rect(pos, size);
}

bool AbstractRectButton::on_mouse_click(const Vector2d& click) {
    if (contains(click)){
        on_press();
        return true;
    }

    return false;
}

bool AbstractRectButton::on_mouse_move(const Vector2d& dest) {
    if (contains(dest)){
        on_hover();
        return true;
    }

    return false;
}

//================================================================================

HelloWorldButton::HelloWorldButton(double x, double y, size_t width, size_t height)
    :AbstractRectButton(x, y, width, height) {}

void HelloWorldButton::on_press() {
    printf("Hello World %d\n", rand());
}

void HelloWorldButton::on_hover() {
    printf("Привет, Мир %d\n", rand());
}
