#pragma once

#include "GUILib.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>

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
	
	Label(const Label& another)            = delete;
	Label& operator=(const Label& another) = delete;

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

class ThickLine: public sf::Drawable {
private:
	sf::VertexArray vertices = sf::VertexArray(sf::Quads, 4);
	sf::Color color = sf::Color();

public:
	ThickLine()  = default;

	ThickLine(const sf::Vector2f& start, const sf::Vector2f& finish,
			  const sf::Color& color = sf::Color::Black, 
			  const float& thickness = 1)
			  : color(color)                                         {

		sf::Vector2f dir_vect  = (finish - start);
		dir_vect = dir_vect / std::sqrt(dir_vect.x * dir_vect.x + dir_vect.y * dir_vect.y);

		sf::Vector2f norm_vect = {-dir_vect.y, dir_vect.x};

		sf::Vector2f thickness_offset = (thickness / 2) * norm_vect;

		vertices[0].position = start  + thickness_offset;
		vertices[1].position = finish + thickness_offset;
		vertices[2].position = finish - thickness_offset;
		vertices[3].position = start  - thickness_offset;

		for (int i = 0; i < 4; ++i){
			vertices[i].color = color;
		}
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		
		target.draw(vertices);
	}

};

class Arrow: public sf::Drawable {
private:
	ThickLine line = ThickLine();

public:
	Arrow() = default;
	Arrow(const sf::Vector2f& start, const sf::Vector2f& finish, 
	      sf::Color color = sf::Color::Black)
	      :line(start, finish, color, 3){

	}

	void draw(sf::RenderTarget& target, sf::RenderStates) const override {
		target.draw(line);
	}
};


class Curve: public sf::Drawable {
private:
	sf::VertexArray curve = sf::VertexArray();
	size_t num_points = 0;

public:
	Curve(Vector<sf::Vector2f> points, size_t num_points, sf::Color curve_color = sf::Color::Black)
				:num_points(num_points) {

		curve = sf::VertexArray(sf::LineStrip, num_points);			

		for (size_t i = 0; i < num_points; ++i){

			curve[i].position = { points[i].x, points[i].y };
			curve[i].color = curve_color;
		}
	}

	void recolor(sf::Color new_color){
		for (size_t i = 0; i < num_points; ++i){
			curve[i].color = new_color;
		}
	}

	void reshape(const sf::Vector2f& start, float x_sec_len, float y_sec_len){
		for (size_t i = 0; i < num_points; ++i){

			curve[i].position = {start.x + curve[i].position.x * x_sec_len, start.y - curve[i].position.y * y_sec_len};
		}
	}

	void draw(sf::RenderTarget& target, sf::RenderStates) const override {

		target.draw(curve);
	}

};

class Plot: public sf::Drawable {
private:
	
	//TODO List of Curves
	Vector<Curve> curves = Vector<Curve>();

	float x_sec_len = 0;
	float y_sec_len = 0;

	sf::RectangleShape back = sf::RectangleShape();
	sf::Color back_color    = sf::Color::White;

	Arrow x_axis = Arrow(); 
	Arrow y_axis = Arrow(); 


public:
	Plot(float x, float y, float width, float height, 
				float x_sec_len = 1, float y_sec_len = 1,
				sf::Color back_color  = sf::Color::White)
				:x_sec_len(x_sec_len), y_sec_len(y_sec_len),
				back(sf::RectangleShape()),
				x_axis(Arrow(sf::Vector2f(x, y), sf::Vector2f(x + width, y         ))),
				y_axis(Arrow(sf::Vector2f(x, y), sf::Vector2f(x        , y - height))) {



		back.setSize(sf::Vector2f(width, height));
		back.setPosition(x, y);
		back.setFillColor(back_color);

	}

	void add(Curve new_curve){

		new_curve.reshape(back.getPosition(), x_sec_len, y_sec_len);
		curves.push_back(new_curve);
	}

	void draw(sf::RenderTarget& target, sf::RenderStates) const override {

		target.draw(back);
		target.draw(x_axis);
		target.draw(y_axis);

		for (size_t i = 0; i < curves.size(); ++i){
			target.draw(curves[i]);
		}
	}

};
}
