#pragma once

#include "../Window/Window.hpp"
#include "../Aux/Auxiliary.hpp"
#include "../Engine/SFMLGraphics.hpp"

class TextLabel: public AbstractRenderWindow {
private:
    const char* buffer = nullptr;
    const Vector2d pos = Vector2d();
    size_t text_size = 12;

public:
    TextLabel() = default;
    TextLabel(const char* text, double x, double y, size_t text_size = 12);
    TextLabel(const char* text, const Vector2d& pos, size_t text_size = 12);

    void draw_at() override;
    bool on_mouse_click(const Vector2d&) override;
};
