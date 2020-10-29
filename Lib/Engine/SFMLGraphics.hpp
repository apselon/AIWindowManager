#pragma once
#include "../Aux/Auxiliary.hpp"

class SFMLGraphicSystem {
private:
    SFMLGraphicSystem() = default;
    static sf::RenderWindow* sf_desktop;

    static sf::Vector2f to_sfVect2f(const Vector2d& vect);
    static sf::Vector2f to_sfVect2f(const Vector2sz& vect);

public:
    static void start();
    static void stop();

    static sf::RenderWindow* desktop();
    static void display_desktop();
    static void clear_desktop();
    static bool desktop_is_running();
    static void draw_rect(const Vector2d& pos, const Vector2sz& size);

};

using GraphicSystem = SFMLGraphicSystem;
