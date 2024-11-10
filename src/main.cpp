#include <vector>
#include "SFML/Graphics.hpp"

#include "verlet_solver.hpp"
#include "renderer.hpp"

// g++ main.cpp -I/opt/homebrew/Cellar/sfml/2.6.1/include -o vo -L/opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-graphics -lsfml-system -lsfml-window

int main() {

    // -------------------WINDOW SETUP: Begin-------------------
    // Create window
    int32_t window_width  = 1000;
    int32_t window_height = 1000;

    // Setting settings for screen
    sf::ContextSettings settings;
    settings.antialiasingLevel = 1;
    // Render window
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Verlet Simulation", sf::Style::Default, settings);
    const uint32_t frame_rate = 60;
    window.setFramerateLimit(frame_rate);
    // -------------------WINDOW SETUP: End-------------------

    // -------------------OBJECT CREATION: Begin-------------------
    verletObject testVerlet(sf::Vector2f(200.0f, 200.0f), 10.0f);
    verlet_solver simulator;
    simulator.addVerlet(testVerlet);
    Renderer renderer(window);
    const float object_spawn_delay = 0.2f;
    sf::Clock clock;
    // -------------------OBJECT CREATION: End-------------------

    const float dt = 1.0f / 60.0f;
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
        }
        if (clock.getElapsedTime().asSeconds() >= object_spawn_delay) {
            clock.restart();
            verletObject testVerlet2(sf::Vector2f(200.0f, 200.0f), 10.0f);
            simulator.addVerlet(testVerlet2);
        }

        
        simulator.update(dt);
        window.clear(sf::Color::Black);
        renderer.render(simulator);
        window.display();
    }
    return 0;
}