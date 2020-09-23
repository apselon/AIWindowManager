#pragma once

#include <cstdio>
#include <cstdlib>
#include <assert.h>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Window.hpp>

#include "GUILib.hpp"

namespace GUILib {

class Clickable: public sf::Drawable {
public:
	virtual void handle_event(const sf::Vector2f& mouse_pos) = 0;
};

class Label: public sf::Drawable {

	friend class Button;

protected:
	const char* text_buf      = nullptr;
	sf::Text presented_text   = sf::Text();

	const char* font_filename = nullptr;
	sf::Font font             = sf::Font();

public:
	Label(const char* text, double x = 0, double y = 0, size_t size = 20, 
				const char* font_filename = "Misc/SanFranciscoBold.ttf", 
				sf::Color color = sf::Color::White) 

				:text_buf(text), 
				font_filename(font_filename){

		presented_text.setString(text_buf);

		font.loadFromFile(font_filename);

		presented_text.setFont(font);
		presented_text.setCharacterSize(size);

		presented_text.setFillColor(color);
		presented_text.setPosition(x, y);
	}

	void draw(sf::RenderTarget& target, sf::RenderStates) const override{

		target.draw(presented_text);
	}
};


class Button: public Clickable {
protected:
	sf::RectangleShape button_box = sf::RectangleShape();
	Label main_label              = Label(nullptr);

	sf::Color color_pressed   = sf::Color();
	sf::Color color_hovered   = sf::Color();
	sf::Color color_idle      = sf::Color();

	ButtonState state = BTN_IDLE;

public:
	Button(const char* text, double width, double height, 
				double x = 0, double y = 0, size_t font_size = 15,
				sf::Color color_pressed   = sf::Color(236, 96, 64),
				sf::Color color_hovered   = sf::Color(248, 128, 64),
				sf::Color color_idle      = sf::Color(248, 128, 64),
				sf::Color border_color    = sf::Color::Transparent,
				sf::Color text_color      = sf::Color::White)

				:main_label(Label(text, x, y, font_size, "Misc/SanFranciscoBold.ttf", text_color)), 
				color_pressed(color_pressed), 
				color_hovered(color_hovered),
				color_idle(color_idle)                    { 

		auto text_bounds = main_label.presented_text.getLocalBounds();

		main_label.presented_text.setPosition(x + width  / 2  - text_bounds.width  / 2 - text_bounds.left,
		                                  y + height / 2  - text_bounds.height / 2 - text_bounds.top);
					
		button_box.setSize(sf::Vector2f(width, height));		
		button_box.setPosition(x, y);
		button_box.setOutlineThickness(3);
		button_box.setOutlineColor(border_color);

	}

	void handle_event(const sf::Vector2f& mouse_pos) override {

		if (button_box.getGlobalBounds().contains(mouse_pos)){

			state = BTN_HOVERED;
			button_box.setFillColor(color_hovered);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){

				state = BTN_PRESSED;
				button_box.setFillColor(color_pressed);
			}
		}

		else {

			state = BTN_IDLE;
			button_box.setFillColor(color_idle);
		}
	}

	int get_state(void){
		return state;
	}

	void draw(sf::RenderTarget& target, sf::RenderStates) const override {

		target.draw(button_box);
		target.draw(main_label);
	}
};
}
