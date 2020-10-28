#include "Button.hpp"

RectButton::RectButton() = default;

RectButton::RectButton(double x, double y, size_t width, size_t height)
    :pos(x, y), size(width, height){};

RectButton::RectButton(const Vector2d& pos, const Vector2sz& size)
    :pos(pos), size(size){};

void RectButton::draw_at(RenderWindow& to_draw_at){
    //Maybe there should be relateive path
    Graphics::SFML::draw_rect(pos, size);
}
