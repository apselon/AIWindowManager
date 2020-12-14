#pragma once
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <stack>
#include "../Aux/Auxiliary.hpp"

using std::stack;


class SFMLGraphicSystem {

private:
    SFMLGraphicSystem() = default;
    static sf::RenderWindow* sf_desktop;
    static stack<sf::RenderTarget*> draw_targets;
    static stack<Vector2d> draw_offsets;

    static sf::Vector2f to_sfVect2f(const Vector2d& vect);
    static Vector2d eff_pos(const Vector2d& pos);

public:
    static void start();
    static void stop();

    static sf::RenderWindow* desktop();
    static void display_desktop();
    static void clear_desktop();
    static bool is_running();

    static void draw_rect(const Vector2d& pos, const Vector2d& size);
    static void draw_text(const std::string& text, const Vector2d& pos, size_t size);
    static void draw_texture(const Vector2d& pos, 
                             const char* image_name);

    static void push_target(const Vector2d& size, const Vector2d& offset);
    static void pop_target_to_display(const Vector2d& pos);

};

using GraphicSystem = SFMLGraphicSystem;
