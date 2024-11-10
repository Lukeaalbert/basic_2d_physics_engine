#ifndef VERLET_SOLVER_HPP
#define VERLET_SOLVER_HPP

#include "SFML/Graphics.hpp"

// g++ verlet_object.hpp -I/opt/homebrew/Cellar/sfml/2.6.1/include -o vo -L/opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-graphics -lsfml-system -lsfml-window

struct verletObject {
    sf::Vector2f current_position;
    sf::Vector2f last_position; 
    sf::Vector2f acceleration;
    float radius;

    verletObject(sf::Vector2f position_, float radius_):
        current_position(position_),
        last_position(position_),
        radius(radius_),
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

    float getRadius() {
        return radius;
    }
};

class verlet_solver {
    public:

        void addVerlet(const verletObject& vo) {
            verlet_objects.push_back(vo);
        }

        void update(float dt) {
            const int substeps = 2;
            const float sub_dt = dt/(static_cast<float>(substeps));
            for (int i = substeps; i > 0; i--){
                applyGravity();
                updatePositions(sub_dt);
                handleCollisions();
                applyConstraint();
            }
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
            // check if verlet defies constraint, if so, fix.
            for (auto& verlet: verlet_objects) {
                const sf::Vector2f v = verlet.current_position - constraint_position;
                // length of vector
                const float length = sqrt((v.x*v.x) + (v.y*v.y));
                // default radius of 50. maybe 10? 
                if (length > (constraint_radius - verlet.radius)) {
                    // store velocity so we can calculate proper old vec pos
                    sf::Vector2f velocity = verlet.current_position - verlet.last_position;
                    const sf::Vector2f n = v/length;
                    verlet.current_position = constraint_position + n * (constraint_radius - verlet.radius);

                    const float dot = velocity.x * n.x + velocity.y * n.y;
                    sf::Vector2f normal_vector = dot * n;
                    sf::Vector2f tangent_vector = velocity - normal_vector;
                    normal_vector *= -0.15f;
                    tangent_vector *= 0.999f;
                    // Update last position to maintain the new velocity
                    sf::Vector2f final_velocity = normal_vector + tangent_vector;
                    verlet.last_position = verlet.current_position - final_velocity;
                }
            }
        }

    void handleCollisions() {
        const size_t verlet_count = verlet_objects.size();
        const float response_coef = 0.6f;
        
        for (size_t v1 = 0; v1 < verlet_count; ++v1) {
            verletObject& verlet_1 = verlet_objects[v1];
            for (size_t v2 = v1 + 1; v2 < verlet_count; ++v2) {

                verletObject& verlet_2 = verlet_objects[v2];

                const sf::Vector2f v = verlet_1.current_position - verlet_2.current_position;
                const float thresh = v.x * v.x + v.y * v.y;
                const float min_dist = verlet_1.radius + verlet_2.radius;
                
                if (thresh < min_dist * min_dist) {
                    const float dist = std::sqrt(thresh);
                    const sf::Vector2f n = v / dist;
                    const float mass_ratio_1 = verlet_1.radius / (verlet_1.radius + verlet_2.radius);
                    const float mass_ratio_2 = verlet_2.radius / (verlet_1.radius + verlet_2.radius);
                    const float delta = 0.5f * response_coef * (dist - min_dist);
                    
                    // Apply position corrections
                    verlet_1.current_position -= n * (mass_ratio_2 * delta);
                    verlet_2.current_position += n * (mass_ratio_1 * delta);
                }
            }
        }
    }

        verletObject& getVerletObjectAt(size_t idx) {
            return verlet_objects.at(idx);
        }

        std::vector<verletObject> getVerletObjects() {
            return verlet_objects;
        }

        std::vector<float> getConstraints() {
            std::vector<float> constraints;
            constraints.push_back(constraint_position.x);
            constraints.push_back(constraint_position.y);
            constraints.push_back(constraint_radius);
            return constraints;
        }
        

    private:
        std::vector<verletObject> verlet_objects;
        const sf::Vector2f gravity = sf::Vector2f(0.0, 1000.0f);
        const sf::Vector2f constraint_position =  sf::Vector2f(500.0f, 450.0f);
        const float constraint_radius = 400.0f;
};

#endif