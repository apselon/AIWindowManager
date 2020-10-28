#pragma once

#include "../Window/Window.hpp"
#include "../Aux/Auxiliary.hpp"
#include "../Engine/SFMLGraphics.hpp"

class RectButton: public RenderWindow {
private:
    Vector2d pos   = Vector2d();    
    Vector2sz size = Vector2sz();

public:
    RectButton();
    RectButton(double x, double y, size_t width, size_t height);
    RectButton(const Vector2d& pos, const Vector2sz& size);

    void draw_at(RenderWindow& to_draw_at) override;
};

