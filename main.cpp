#include "Lib/GUILib.cpp"
#include "Lib/Sortable.cpp"
#include "Lib/Algorithms.cpp"
#include <SFML/Graphics/Color.hpp>

template <typename T>
size_t Sortable<T>::cpy_counter = 0;

template <typename T>
size_t Sortable<T>::cmp_counter = 0;

void send_event(const float mouse_pos_x, const float mouse_pos_y, Vector<GUILib::Clickable*>& elements);
void redraw(sf::RenderWindow& window, Vector<GUILib::Clickable*>& elements);

int main(void){

	sf::RenderWindow window(sf::VideoMode(1920/2, 1080), "Hello world");
	auto elements = Vector<GUILib::Clickable*>();

	elements.push_back(new GUILib::Button("Bubble sort",    200, 100, 100, 100, 25));

	elements.push_back(new GUILib::Button("Selection sort", 200, 100, 350, 100, 25, 
	                                      sf::Color(60, 100, 184),
										  sf::Color(81, 129, 184),
										  sf::Color(81, 129, 184)));
	
	elements.push_back(new GUILib::Button("Merge sort",     200, 100, 100, 250, 25, 
	                                      sf::Color(39, 150, 98),
										  sf::Color(39, 176, 98),
										  sf::Color(39, 176, 98)));

	elements.push_back(new GUILib::Button("Quick sort",     200, 100, 350, 250, 25, 
	                                      sf::Color(155, 50, 192),
										  sf::Color(155, 89, 182),
										  sf::Color(155, 89, 182)));

	auto plot = GUILib::Plot(100, 800, 400, 400, 5, 5);

	auto points = Vector<sf::Vector2f>();

	for (int i = 1; i < 50; ++i){
		test_sort(BubbleSort<int>(), i);
		points.push_back(sf::Vector2f(i, Sortable<int>::count_cpy()));
	}

	plot.add(GUILib::Curve(points, points.size(), sf::Color::Red));

	for (int i = 1; i < 50; ++i){
		test_sort(SelectionSort<int>(), i);
		points[i] = (sf::Vector2f(i, Sortable<int>::count_cpy()));
	}

	plot.add(GUILib::Curve(points, points.size(), sf::Color::Blue));

	while (window.isOpen()){
		auto event = sf::Event();

		while (window.pollEvent(event)){
			switch (event.type) {
				case sf::Event::Closed:
					window.close();
					break;

				case sf::Event::MouseMoved:
					send_event(event.mouseMove.x, event.mouseMove.y, elements);
					break;

				case sf::Event::MouseButtonPressed:
				case sf::Event::MouseButtonReleased:
					send_event(event.mouseButton.x, event.mouseButton.y, elements);
					break;

				default: break;
			}
		}

		window.clear(sf::Color::White);
		window.draw(plot);
		redraw(window, elements);
		window.display();
	}

	for (auto elem: elements){
		delete elem;
	}

	return 0;
}

void send_event(const float mous_pos_x, const float mouse_pos_y, Vector<GUILib::Clickable*>& elements){

	for (size_t i = 0; i < elements.size(); ++i) {
		elements[i]->handle_event(sf::Vector2f(mous_pos_x, mouse_pos_y));
	}
}

void redraw(sf::RenderWindow& window, Vector<GUILib::Clickable*>& elements){
	for (size_t i = 0; i < elements.size(); ++i) {
		window.draw(*elements[i]);
	}

};
