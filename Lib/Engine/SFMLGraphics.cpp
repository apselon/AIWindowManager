#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include "SFMLGraphics.hpp"


sf::RenderWindow* SFMLGraphicSystem::sf_desktop = nullptr;
stack<sf::RenderTarget*> SFMLGraphicSystem::draw_targets;
stack<Vector2d> SFMLGraphicSystem::draw_offsets;

void SFMLGraphicSystem::start()
{
    sf_desktop = new sf::RenderWindow(sf::VideoMode(1920/2, 1080), "Desktop");
    draw_targets.push(sf_desktop);
    draw_offsets.push({0, 0});
    display_desktop();
}

void SFMLGraphicSystem::stop()
{
    delete sf_desktop;
}

sf::Vector2f SFMLGraphicSystem::to_sfVect2f(const Vector2d& vect)
{
    return sf::Vector2f(vect.x, vect.y);
}

Vector2d SFMLGraphicSystem::eff_pos(const Vector2d& pos)
{
    return pos - SFMLGraphicSystem::draw_offsets.top(); 
}

void SFMLGraphicSystem::display_desktop()
{
    sf_desktop->display();
    GraphicSystem::desktop()->clear(sf::Color::White);
}

sf::RenderWindow* SFMLGraphicSystem::desktop()
{
    return sf_desktop;
}

bool SFMLGraphicSystem::is_running()
{
    return desktop()->isOpen();
}

void SFMLGraphicSystem::push_target(const Vector2d& size, const Vector2d& offset)
{
    auto* sf_texture = new sf::RenderTexture();
    sf_texture->create(size.x, size.y);
    sf_texture->clear(sf::Color::White);
    draw_targets.push(sf_texture);
    draw_offsets.push(offset);
}

void SFMLGraphicSystem::pop_target_to_display(const Vector2d& pos)
{
    auto flushed_texture = static_cast<sf::RenderTexture*>(draw_targets.top());
    flushed_texture->display();

    auto sf_sprite = sf::Sprite();
    sf_sprite.setTexture(flushed_texture->getTexture());
    sf_sprite.setPosition(to_sfVect2f(pos));

    draw_targets.pop();
    draw_targets.top()->draw(sf_sprite);
    delete flushed_texture;
}

void SFMLGraphicSystem::draw_rect(const Vector2d& pos, const Vector2d& size) 
{
    auto sf_rect = sf::RectangleShape();
    sf_rect.setSize(to_sfVect2f(size));
    sf_rect.setPosition(to_sfVect2f(pos));
    sf_rect.setFillColor(sf::Color::Red);

    draw_targets.top()->draw(sf_rect);
}

void SFMLGraphicSystem::draw_text(const char* text, const Vector2d& pos, size_t size)
{
    auto sf_text = sf::Text();
    auto sf_font = sf::Font();

    sf_font.loadFromFile("Misc/SanFrancisco.ttf");
    sf_text.setString(text);
    sf_text.setFont(sf_font);
    sf_text.setCharacterSize(size);
    sf_text.setFillColor(sf::Color::Black);
    sf_text.setPosition(to_sfVect2f(pos));

    draw_targets.top()->draw(sf_text);
}

/*
void SFMLGraphicSystem::draw_scrollable_text(
        const std::string& text, const Vector2d& pos, 
        const Vector2d& size, double offset)
{
    auto sf_text = sf::Text();
    auto sf_font = sf::Font();

    sf_font.loadFromFile("Misc/SanFrancisco.ttf");
    sf_text.setString(sf::String::fromUtf8(text.begin(), text.end()));
    sf_text.setFont(sf_font);
    sf_text.setCharacterSize(12);
    sf_text.setFillColor(sf::Color::Black);

    sf_text.setPosition(0, offset); 


    auto sf_sprite = sf::Sprite();
    sf_sprite.setTexture(sf_texture.getTexture());
    sf_sprite.setPosition(to_sfVect2f(pos));
    sf_desktop->draw(sf_sprite);

}
*/
