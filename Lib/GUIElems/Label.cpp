#include "Label.hpp"


TextLabel::TextLabel(const Vector2d& pos, const Vector2d& size,  const char* text, size_t text_size)
    :RectWindow({pos, size}), buffer(text), text_size(text_size) {};

bool TextLabel::handle_event(const Event* event)
{
    if (event == nullptr) return true;

    if (event->get_type() == EventType::Redraw) {
        draw();
    }

    return false;
}

void TextLabel::draw()
{
    GraphicSystem::draw_text(buffer, pos, text_size);
}

