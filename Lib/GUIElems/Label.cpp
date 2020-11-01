#include "Label.hpp"

TextLabel::TextLabel(const char* text, double x, double y, size_t size)
    :buffer(text), pos(x, y), text_size(size) {};

TextLabel::TextLabel(const char* text, const Vector2d& pos, size_t size)
    :buffer(text), pos(pos), text_size(size) {};

void TextLabel::draw_at() {
    GraphicSystem::draw_text(buffer, pos, text_size);
}

bool TextLabel::on_mouse_click(const Vector2d&) {
    return false;
}

