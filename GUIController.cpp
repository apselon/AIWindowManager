#pragma once

#include <SFML/Window/Mouse.hpp>
#include <cstdio>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Window.hpp>
#include "GUILib.cpp"

int main(void){

	sf::RenderWindow window(sf::VideoMode(640, 480), "Hellow World");

	auto button = Button("Hello world", 100, 200);

	while (window.isOpen()){
		auto event = sf::Event();

		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::MouseButtonPressed){
				auto mouse_pos = sf::Mouse::getPosition(window);
				auto mouse_posf = sf::Vector2f(mouse_pos.x, mouse_pos.y);
				button.update(mouse_posf);
			}
		}

		window.clear();
		window.draw(button.display());
		window.display();
	}
	return 0;
}

