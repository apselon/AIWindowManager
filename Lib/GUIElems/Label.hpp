#pragma once

#include "../Window/Window.hpp"
#include "../Aux/Auxiliary.hpp"
#include "../Engine/SFMLGraphics.hpp"

class TextLabel: public RectWindow{
private:
    const char* buffer = nullptr;
    const Vector2d pos = Vector2d();
    const Vector2d size = Vector2d();
    size_t text_size = 12;

public:
    TextLabel(const Vector2d& pos, const Vector2d& size, 
              const char* text, size_t text_size = 16);

    bool handle_event(const Event* event) override;
    void draw() override;
};
