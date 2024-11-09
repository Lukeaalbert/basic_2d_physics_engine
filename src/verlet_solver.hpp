#ifndef VERLET_SOLVER_HPP
#define VERLET_SOLVER_HPP

#include "SFML/Graphics.hpp"

// g++ verlet_object.hpp -I/opt/homebrew/Cellar/sfml/2.6.1/include -o vo -L/opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-graphics -lsfml-system -lsfml-window

struct verletObject {
    sf::Vector2f current_position;
    sf::Vector2f last_position; 
    sf::Vector2f acceleration;

    verletObject(sf::Vector2f position_):
        current_position(position_),
        last_position(position_),
        acceleration(0.f, 0.f) {}

    // updates object position based on dt using verlet integration
    void updatePosition(float dt) {
        const sf::Vector2f velocity = current_position - last_position;
        last_position = current_position;
        // Verlet Integration
        current_position = current_position + velocity + acceleration * (dt * dt);
        // reset acceleration
        acceleration = sf::Vector2f(0.f, 0.f);
    }

    // updates acceleration based on new acceleration information
    void accelerate (sf::Vector2f acc_new) {
        acceleration += acc_new;
    }
};

class verlet_solver {
    public:

        void addVerlet(const verletObject& vo) {
            verlet_objects.push_back(vo);
        }

        void update(float dt) {
            applyGravity();
            updatePositions(dt);
            applyConstraint();
        }

        void updatePositions(float dt) {
            for (auto& verlet: verlet_objects) {
                verlet.updatePosition(dt);
            }
        }

        void applyGravity() {
            for (auto& verlet: verlet_objects) {
                verlet.accelerate(gravity);
            }
        }

        void applyConstraint() {
            // "area of constraint", ie, boundaries for circular container
            sf::Vector2f position(500.0f, 450.0f);
            const float radius = 400.0f;

            // check if verlet defies constraint, if so, fix.
            for (auto& verlet: verlet_objects) {
                const sf::Vector2f v = verlet.current_position - position;
                // length of vector
                const float length = sqrt((v.x*v.x) + (v.y*v.y));
                // default radius of 50. maybe 10? 
                if (length > (radius - 10.0f)) {
                    // store velocity so we can calculate proper old vec pos
                    sf::Vector2f velocity = verlet.current_position - verlet.last_position;
                    const sf::Vector2f n = v/length;
                    verlet.current_position = position + n * (radius - 10.0f);

                    const float dot = velocity.x * n.x + velocity.y * n.y;
                    sf::Vector2f normal_vector = dot * n;
                    sf::Vector2f tangent_vector = velocity - normal_vector;
                    // (0.75 = 75% energy preservation)
                    normal_vector *= -0.75f;
                    tangent_vector *= 0.99f;
                    // Update last position to maintain the new velocity
                    sf::Vector2f final_velocity = normal_vector + tangent_vector;
                    verlet.last_position = verlet.current_position - final_velocity;
                }
            }
        }

        verletObject& getVerletObjectAt(size_t idx) {
            return verlet_objects.at(idx);
        }

    private:
        std::vector<verletObject> verlet_objects;
        const sf::Vector2f gravity = sf::Vector2f(0.0, 1000.0f);
};

#endif