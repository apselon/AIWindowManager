#include "Primitives.hpp"

Primitives::Rect::Rect(double pos_x, double pos_y, double width, double height)
    :pos_x(pos_x), pos_y(pos_y), width(width), height(height) {};

bool Primitives::Rect::contains(double x, double y) {
    return (pos_x <= x && x <= pos_x + width) && (pos_y <= y && y <= pos_y + height);
}

void Primitives::Rect::draw() {
    printf("Drawed rectangle %lg x %lg at (%lg, %lg)", width, height, pos_x, pos_y);
}
