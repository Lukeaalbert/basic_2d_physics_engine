
// renderer.hpp
#ifndef RENDERER_HPP
#define RENDERER_HPP 
#include "verlet_solver.hpp"

class Renderer {
public:
    explicit Renderer(sf::RenderTarget& target)
        : renderTarget(target) {}

    void render(const verletObject& vo) const {

        // DELETE ME. placeholder.
        sf::CircleShape constraint_background(400.0f);
        constraint_background.setOrigin(400.0f, 400.0f);
        constraint_background.setFillColor(sf::Color::White);
        constraint_background.setPosition(500.0f, 450.0f);
        constraint_background.setPointCount(128);
        renderTarget.draw(constraint_background);

        const float radius = 10.0f;
        sf::CircleShape circle(radius);
        circle.setPointCount(32);
        circle.setOrigin(radius, radius);
        circle.setPosition(vo.current_position);
        circle.setFillColor(sf::Color::Red);
        renderTarget.draw(circle);
    }

private:
    sf::RenderTarget& renderTarget;
};

#endif