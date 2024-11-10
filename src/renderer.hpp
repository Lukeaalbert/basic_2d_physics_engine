
// renderer.hpp
#ifndef RENDERER_HPP
#define RENDERER_HPP 
#include "verlet_solver.hpp"

class Renderer {
public:
    explicit Renderer(sf::RenderTarget& target)
        : renderTarget(target) {}

    void render(verlet_solver& solver) const {
        
        std::vector<float> constraints = solver.getConstraints();
        sf::CircleShape constraint_background(constraints[2]);
        constraint_background.setOrigin(constraints[2], constraints[2]);
        constraint_background.setFillColor(sf::Color::White);
        constraint_background.setPosition(constraints[0], constraints[1]);
        constraint_background.setPointCount(128);
        renderTarget.draw(constraint_background);

        std::vector<verletObject> verlet_objects = solver.getVerletObjects();

        for (auto& vo: verlet_objects)
        {
            const float radius = vo.getRadius();
            sf::CircleShape circle(radius);
            circle.setPointCount(32);
            circle.setOrigin(radius, radius);
            circle.setPosition(vo.current_position);
            circle.setFillColor(sf::Color::Red);
            renderTarget.draw(circle);
        }
    }

private:
    sf::RenderTarget& renderTarget;
};

#endif