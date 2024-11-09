CXX = g++

SRC = main.cpp
HEADERS = verlet_solver.hpp renderer.hpp

SFML_INCLUDE = /opt/homebrew/Cellar/sfml/2.6.1/include
SFML_LIB = /opt/homebrew/Cellar/sfml/2.6.1/lib

CXXFLAGS = -I$(SFML_INCLUDE)
LDFLAGS = -L$(SFML_LIB) -lsfml-graphics -lsfml-system -lsfml-window

TARGET = simulator

$(TARGET): $(SRC) $(HEADERS)
	$(CXX) $(SRC) $(CXXFLAGS) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f simulator