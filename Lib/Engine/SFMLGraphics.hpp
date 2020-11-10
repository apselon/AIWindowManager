#pragma once
#include "../Aux/Auxiliary.hpp"

class SFMLGraphicSystem {
private:
    SFMLGraphicSystem() = default;
    static sf::RenderWindow* sf_desktop;

    static sf::Vector2f to_sfVect2f(const Vector2d& vect);
    //static sf::Vector2f to_sfVect2f(const Vector2sz& vect);

public:
    static void start();
    static void stop();

    static sf::RenderWindow* desktop();
    static void display_desktop();
    static void clear_desktop();
    static bool is_running();

    static void draw_rect(const Vector2d& pos, const Vector2d& size);
    static void draw_text(const char* text, const Vector2d& pos, size_t size);
    static void draw_scrollable_text(const std::string& text, const Vector2d& pos, 
                                     const Vector2d& size, double offset);

};

using GraphicSystem = SFMLGraphicSystem;
