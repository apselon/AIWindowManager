CXX = clang++
CXXFLAGS = -Wall -Weffc++ -Wfloat-equal -Wconversion -Wpedantic -Wextra -ftrapv -fverbose-asm --std=c++17 -pg -ggdb -DDEBUG -fsanitize=address
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system
OBJDIR = .objects

app.run: main.cpp $(OBJDIR)/Application.o $(OBJDIR)/SFMLEvents.o $(OBJDIR)/SFMLGraphics.o $(OBJDIR)/Window.o $(OBJDIR)/Button.o $(OBJDIR)/Label.o $(OBJDIR)/Scroll.o
	$(CXX) $(CXXFLAGS) $^ $(LDLIBS) -o app.run

$(OBJDIR)/Scroll.o: Lib/GUIElems/Scroll.cpp Lib/GUIElems/Scroll.hpp
	$(CXX) $(CXXFLAGS) -c Lib/GUIElems/Scroll.cpp -o $(OBJDIR)/Scroll.o

$(OBJDIR)/Application.o: Lib/Engine/Application.cpp Lib/Engine/Application.hpp
	$(CXX) $(CXXFLAGS) -c Lib/Engine/Application.cpp -o $(OBJDIR)/Application.o

$(OBJDIR)/SFMLEvents.o: Lib/Engine/SFMLEvents.cpp Lib/Engine/SFMLEvents.hpp
	$(CXX) $(CXXFLAGS) -c Lib/Engine/SFMLEvents.cpp -o $(OBJDIR)/SFMLEvents.o

$(OBJDIR)/SFMLGraphics.o: Lib/Engine/SFMLGraphics.cpp Lib/Engine/SFMLGraphics.hpp
	$(CXX) $(CXXFLAGS) -c Lib/Engine/SFMLGraphics.cpp -o $(OBJDIR)/SFMLGraphics.o

$(OBJDIR)/Window.o: Lib/Window/Window.cpp Lib/Window/Window.hpp
	$(CXX) $(CXXFLAGS) -c Lib/Window/Window.cpp -o $(OBJDIR)/Window.o

$(OBJDIR)/Button.o: Lib/GUIElems/Button.cpp Lib/GUIElems/Button.hpp
	$(CXX) $(CXXFLAGS) -c Lib/GUIElems/Button.cpp -o $(OBJDIR)/Button.o

$(OBJDIR)/Label.o: Lib/GUIElems/Label.cpp Lib/GUIElems/Label.hpp
	$(CXX) $(CXXFLAGS) -c Lib/GUIElems/Label.cpp -o $(OBJDIR)/Label.o
