#include "SFMLGraphics.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>


sf::RenderWindow* SFMLGraphicSystem::sf_desktop = nullptr;

void SFMLGraphicSystem::start() {
    sf_desktop = new sf::RenderWindow(sf::VideoMode(1920/2, 1080), "Desktop");
}

void SFMLGraphicSystem::stop() {
    delete sf_desktop;
}

sf::Vector2f SFMLGraphicSystem::to_sfVect2f(const Vector2d& vect){
    return sf::Vector2f(vect.x, vect.y);
}

sf::Vector2f SFMLGraphicSystem::to_sfVect2f(const Vector2sz& vect){
    return sf::Vector2f(vect.x, vect.y);
}

void SFMLGraphicSystem::draw_rect(const Vector2d& pos, const Vector2sz& size){
    auto rect = sf::RectangleShape();
    rect.setSize(to_sfVect2f(size));
    rect.setPosition(to_sfVect2f(pos));
    rect.setFillColor(sf::Color::Black);

    sf_desktop->draw(rect);
}

void SFMLGraphicSystem::display_desktop(){
    sf_desktop->display();
}

sf::RenderWindow* SFMLGraphicSystem::desktop(){
    return sf_desktop;
}
