template <typename T>
size_t Sortable<T>::cpy_counter = 0;

template <typename T>
size_t Sortable<T>::cmp_counter = 0;

void send_event(const float mouse_pos_x, const float mouse_pos_y, Vector<GUILib::Clickable*>& elements);
void redraw(sf::RenderWindow& window, Vector<GUILib::Clickable*>& elements);

class BubbleSortButton: public GUILib::Button {
private:
	GUILib::Plot& plot; 
public:

	BubbleSortButton(GUILib::Plot& plot, const char* text, double width, double height,    
                     double x = 0, double y = 0, size_t font_size = 15,    
                     sf::Color color_pressed   = sf::Color(236, 96, 64),    
                     sf::Color color_hovered   = sf::Color(248, 128, 64),    
                     sf::Color color_idle      = sf::Color(248, 128, 64),    
                     sf::Color border_color    = sf::Color::Transparent,    
                     sf::Color text_color      = sf::Color::White)    

	                 :Button(text, width, height, x, y, font_size,
					 color_pressed, color_hovered, color_idle,
					 border_color, text_color), plot(plot)         {}

	void click() override {
		
		auto points = Vector<sf::Vector2f>();
	
		for (int i = 1; i < 20; ++i){
			test_sort(BubbleSort<int>(), i);
			points.push_back(sf::Vector2f(i, Sortable<int>::count_cpy()));
		}
	
		plot.add(GUILib::Curve(points, points.size(), sf::Color::Red));
	}
};

class SelectionSortButton: public GUILib::Button {
private:
	GUILib::Plot& plot; 
public:

	SelectionSortButton(GUILib::Plot& plot, const char* text, double width, double height,    
                     double x = 0, double y = 0, size_t font_size = 15,    
                     sf::Color color_pressed   = sf::Color(236, 96, 64),    
                     sf::Color color_hovered   = sf::Color(248, 128, 64),    
                     sf::Color color_idle      = sf::Color(248, 128, 64),    
                     sf::Color border_color    = sf::Color::Transparent,    
                     sf::Color text_color      = sf::Color::White)    

	                 :Button(text, width, height, x, y, font_size,
					 color_pressed, color_hovered, color_idle,
					 border_color, text_color), plot(plot)         {}

	void click() override {
		
		auto points = Vector<sf::Vector2f>();
	
		for (int i = 1; i < 20; ++i){
			test_sort(SelectionSort<int>(), i);
			points.push_back(sf::Vector2f(i, Sortable<int>::count_cpy()));
		}
	
		plot.add(GUILib::Curve(points, points.size(), sf::Color::Red));
	}
};

class MergeSortButton: public GUILib::Button {
private:
	GUILib::Plot& plot; 
public:

	MergeSortButton(GUILib::Plot& plot, const char* text, double width, double height,    
                     double x = 0, double y = 0, size_t font_size = 15,    
                     sf::Color color_pressed   = sf::Color(236, 96, 64),    
                     sf::Color color_hovered   = sf::Color(248, 128, 64),    
                     sf::Color color_idle      = sf::Color(248, 128, 64),    
                     sf::Color border_color    = sf::Color::Transparent,    
                     sf::Color text_color      = sf::Color::White)    

	                 :Button(text, width, height, x, y, font_size,
					 color_pressed, color_hovered, color_idle,
					 border_color, text_color), plot(plot)         {}

	void click() override {
		
		auto points = Vector<sf::Vector2f>();
	
		for (int i = 1; i < 20; ++i){
			test_sort(MergeSort<int>(), i);
			points.push_back(sf::Vector2f(i, Sortable<int>::count_cpy()));
		}
	
		plot.add(GUILib::Curve(points, points.size(), sf::Color::Red));
	}
};

class QuickSortButton: public GUILib::Button {
private:
	GUILib::Plot& plot; 
public:

	QuickSortButton(GUILib::Plot& plot, const char* text, double width, double height,    
                     double x = 0, double y = 0, size_t font_size = 15,    
                     sf::Color color_pressed   = sf::Color(236, 96, 64),    
                     sf::Color color_hovered   = sf::Color(248, 128, 64),    
                     sf::Color color_idle      = sf::Color(248, 128, 64),    
                     sf::Color border_color    = sf::Color::Transparent,    
                     sf::Color text_color      = sf::Color::White)    

	                 :Button(text, width, height, x, y, font_size,
					 color_pressed, color_hovered, color_idle,
					 border_color, text_color), plot(plot)         {}

	void click() override {

		auto points = Vector<sf::Vector2f>();
	
		for (int i = 1; i < 20; ++i){
			test_sort(QuickSort<int>(), i);
			points.push_back(sf::Vector2f(i, Sortable<int>::count_cpy()));
		}
	
		plot.add(GUILib::Curve(points, points.size(), sf::Color::Red));
	}
};
