#pragma once

#include <SFML/Window/Mouse.hpp>
#include <cstdio>
#include <cstdlib>
#include <assert.h>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Window.hpp>

class Label {
protected:
	const char* text_buf = nullptr;
	sf::Text presented_text = sf::Text();

	double pos_x = 0;
	double pos_y = 0;

	size_t char_size = 12;

	const char* font_filename = nullptr;
	sf::Font font = sf::Font();

	sf::Color color = sf::Color();

public:
	Label(const char* text, double x = 0, double y = 0, size_t size = 12, 
				const char* font_filename = "Misc/SanFrancisco.ttf", 
				sf::Color color = sf::Color::Black) 

				:text_buf(text), pos_x(x), pos_y(y), char_size(size), 
				font_filename(font_filename), color(color) {

		presented_text.setString(text_buf);

		font.loadFromFile(font_filename);

		presented_text.setFont(font);
		presented_text.setCharacterSize(char_size);

		presented_text.setFillColor(color);
		presented_text.setPosition(x, y);
	}

	void render(sf::RenderTarget& target){

		target.draw(presented_text);
	}

	sf::Text display(void){
		return presented_text;
	}
};

class Button: protected Label {
protected:
	double width  = 0;
	double height = 0;

	sf::RectangleShape button_box = sf::RectangleShape();

	sf::Color color_active   = sf::Color();
	sf::Color border_color   = sf::Color();
	sf::Color color_inactive = sf::Color();

	bool is_pressed = 0;
	bool is_hovered = 0;
	
public:
	Button(const char* text, double width, double height, 
				double x = 0, double y = 0, size_t font_size = 12,
				sf::Color color_incactive = sf::Color::White, 
				sf::Color color_active    = sf::Color::Cyan,
				sf::Color border_color    = sf::Color::Black)

				:Label(text, x, y, font_size), width(width), height(height),
				color_active(color_active), border_color(border_color),
				color_inactive(color_incactive)                                                   {

		auto text_bounds = Label::presented_text.getLocalBounds();

		Label::presented_text.setPosition(x + width/2  - text_bounds.width  / 2,
		                                  y + height/2 - text_bounds.height / 2);
					
		button_box.setSize(sf::Vector2f(width, height));		
		button_box.setPosition(x, y);

		button_box.setFillColor(color_inactive);

		button_box.setOutlineThickness(2);
		button_box.setOutlineColor(border_color);

	}

	void update(const sf::Vector2f& mouse_pos){
		if (button_box.getGlobalBounds().contains(mouse_pos)){
			button_box.setFillColor(color_active);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				printf("Clicked\n");
			}
		}

		else {
			button_box.setFillColor(color_active);
		}
	}

	void render(sf::RenderTarget& target){

		target.draw(button_box);
		Label::render(target);
	}

	sf::RectangleShape display(void){
		return button_box;
	}
};
