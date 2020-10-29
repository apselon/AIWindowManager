CXX = clang++
CXXFLAGS = -Wall -Weffc++ -Wfloat-equal -Wconversion -Wpedantic -Wextra -ftrapv -fverbose-asm --std=c++17 -pg -ggdb -DDEBUG -fsanitize=address
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system
OBJFILES_DIR = .objects

app.run: main.cpp $(OBJFILES_DIR)/Application.o $(OBJFILES_DIR)/SFMLEvents.o $(OBJFILES_DIR)/SFMLGraphics.o $(OBJFILES_DIR)/Window.o $(OBJFILES_DIR)/Button.o
	$(CXX) $(CXXFLAGS) main.cpp $(OBJFILES_DIR)/Application.o $(OBJFILES_DIR)/SFMLEvents.o $(OBJFILES_DIR)/SFMLGraphics.o $(OBJFILES_DIR)/Window.o $(OBJFILES_DIR)/Button.o $(LDLIBS) -o app.run

$(OBJFILES_DIR)/Application.o: Lib/Engine/Application.cpp Lib/Engine/Application.hpp
	$(CXX) $(CXXFLAGS) -c Lib/Engine/Application.cpp -o $(OBJFILES_DIR)/Application.o

$(OBJFILES_DIR)/SFMLEvents.o: Lib/Engine/SFMLEvents.cpp Lib/Engine/SFMLEvents.hpp
	$(CXX) $(CXXFLAGS) -c Lib/Engine/SFMLEvents.cpp -o $(OBJFILES_DIR)/SFMLEvents.o

$(OBJFILES_DIR)/SFMLGraphics.o: Lib/Engine/SFMLGraphics.cpp Lib/Engine/SFMLGraphics.hpp
	$(CXX) $(CXXFLAGS) -c Lib/Engine/SFMLGraphics.cpp -o $(OBJFILES_DIR)/SFMLGraphics.o

$(OBJFILES_DIR)/Window.o: Lib/Window/Window.cpp Lib/Window/Window.hpp
	$(CXX) $(CXXFLAGS) -c Lib/Window/Window.cpp -o $(OBJFILES_DIR)/Window.o

$(OBJFILES_DIR)/Button.o: Lib/GUIElems/Button.cpp Lib/GUIElems/Button.hpp
	$(CXX) $(CXXFLAGS) -c Lib/GUIElems/Button.cpp -o $(OBJFILES_DIR)/Button.o
