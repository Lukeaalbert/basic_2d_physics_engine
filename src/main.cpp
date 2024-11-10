#include <vector>
#include <math.h>
#include <random>
#include <ctime>
#include "SFML/Graphics.hpp"

#include "verlet_solver.hpp"
#include "renderer.hpp"

std::array<sf::Color, 6> COLORS = {
    sf::Color(255, 99, 71),
    sf::Color(255, 165, 0),
    sf::Color(255, 223, 0),
    sf::Color(60, 179, 113),
    sf::Color(70, 130, 180),
    sf::Color(138, 43, 226)
};


std::array<float, 6> SIZES = {5.0f, 8.0f, 12.0f, 15.0f, 22.0f, 29.0f};
float x_init_velo = -3.0f;
int STATE = 0;
int L_TO_R = 0;
int R_TO_L = 1;

verletObject generateNewVerlet(){
    auto now = std::chrono::high_resolution_clock::now();
    auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();
    std::mt19937 gen(nanoseconds); // Mersenne Twister engine
    std::uniform_int_distribution<int> col(0, 5); // Range: 0 to 5 inclusive
    sf::Color color = COLORS[col(gen)];
    std::uniform_int_distribution<int> dist(0, 5);
    float size = SIZES[dist(gen)];
    
    if (x_init_velo >= 3.0f) {
        STATE = R_TO_L;
    }
    else if (x_init_velo <= -3.0f) {
        STATE = L_TO_R;
    }
    if (STATE == L_TO_R) {
        x_init_velo += 0.2;
    }
    else {
        x_init_velo -= 0.2;
    }

    return verletObject(sf::Vector2f(500.0f, 100.0f), size, color, sf::Vector2f(x_init_velo, 3.0f));
}

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

    verlet_solver simulator;
    Renderer renderer(window);

    const float constraint_radius = simulator.getConstraintRadius();
    float constraint_area = M_PI * (constraint_radius*constraint_radius);
    bool add_new_verlets = true;

    const float object_spawn_delay = 0.17f;
    sf::Clock clock;
    const float dt = 1.0f / 60.0f;
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
        }
        if (add_new_verlets && clock.getElapsedTime().asSeconds() >= object_spawn_delay) {
            clock.restart();
            verletObject new_verlet = generateNewVerlet();
            const float new_verlet_radius = new_verlet.getRadius();
            const float new_verlet_area = M_PI * (new_verlet_radius*new_verlet_radius);
            if (constraint_area - new_verlet_area <= 400.0f) {
                add_new_verlets = false;
            }
            else {
                constraint_area -= new_verlet_area;
                simulator.addVerlet(new_verlet);
            }
        }
        
        simulator.update(dt);
        window.clear(sf::Color(211, 211, 211));
        renderer.render(simulator);
        window.display();
    }
    return 0;
}