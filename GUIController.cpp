#pragma once

#include <cstdio>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Window.hpp>

int main(void){

	sf::RenderWindow window(sf::VideoMode(640, 480), "Hellow World");

	auto shape = sf::CircleShape(200);

	while (window.isOpen()){
		auto event = sf::Event();

		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed) window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}
	return 0;
}

