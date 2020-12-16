#pragma once
#include "../../Lib/Aux/Auxiliary.hpp"
#include "../../Lib/Window/Window.hpp"
#include "../../Lib/Engine/SFMLGraphics.hpp"

struct Color {
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
    uint8_t a = 0;

    Color() = default;
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
};

class Image: public ShapedWindow<RectShape>, public MouseReceptive {
protected:
    vector<uint8_t> data = vector<uint8_t>();
public:

    Image(const Vector2d& pos, const Vector2d& size);
    bool handle_event(const Event* event) override;
    bool on_mouse_click(const Vector2d& pos) override;
    bool on_mouse_move(const Vector2d& pos) override;
    bool on_mouse_release(const Vector2d& pos) override;
    void draw() override;

    void set_color(int64_t x, int64_t y, const Color& color);
    Color get_color(int64_t x, int64_t y);
    uint8_t* get_data();
};
