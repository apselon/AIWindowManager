#include "SFMLGraphics.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>


sf::RenderWindow* SFMLGraphicSystem::sf_desktop = nullptr;

void SFMLGraphicSystem::start() {
    sf_desktop = new sf::RenderWindow(sf::VideoMode(1920/2, 1080), "Desktop");
    display_desktop();
}

void SFMLGraphicSystem::stop() {
    delete sf_desktop;
}

sf::Vector2f SFMLGraphicSystem::to_sfVect2f(const Vector2d& vect) {
    return sf::Vector2f(vect.x, vect.y);
}

void SFMLGraphicSystem::display_desktop() {
    sf_desktop->display();
    GraphicSystem::desktop()->clear(sf::Color::White);
}

sf::RenderWindow* SFMLGraphicSystem::desktop() {
    return sf_desktop;
}

bool SFMLGraphicSystem::is_running() {

    return desktop()->isOpen();
}

void SFMLGraphicSystem::draw_rect(const Vector2d& pos, const Vector2d& size) {
    auto sf_rect = sf::RectangleShape();
    sf_rect.setSize(to_sfVect2f(size));
    sf_rect.setPosition(to_sfVect2f(pos));
    sf_rect.setFillColor(sf::Color::Red);

    sf_desktop->draw(sf_rect);
}

void SFMLGraphicSystem::draw_text(const char* text, const Vector2d& pos, size_t size) {
    auto sf_text = sf::Text();
    auto sf_font = sf::Font();

    sf_font.loadFromFile("Misc/SanFrancisco.ttf");
    sf_text.setString(text);
    sf_text.setFont(sf_font);
    sf_text.setCharacterSize(size);
    sf_text.setFillColor(sf::Color::Black);
    sf_text.setPosition(to_sfVect2f(pos));

    sf_desktop->draw(sf_text);
}
