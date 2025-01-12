#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/Graphics.hpp>

class Particle {
public:
    sf::Vector2f position;
    sf::Vector2f prev_position;
    sf::Vector2f force;
    bool is_pinned;

    Particle(float x, float y, bool pinned = false) : position(x, y), prev_position(x, y), force(0, 0), is_pinned(pinned) {}

    void add_force(const sf::Vector2f& applied_force) {
        if (!is_pinned) force += applied_force;
    }

    void simulate(float time_step) {
        if (!is_pinned) {
            sf::Vector2f velocity = position - prev_position;
            prev_position = position;
            position += velocity + force * time_step * time_step;
            force = sf::Vector2f(0, 0);
        }
    }

    void keep_within_bounds(float width, float height) {
        if (position.x < 0) position.x = 0;
        if (position.x > width) position.x = width;
        if (position.y < 0) position.y = 0;
        if (position.y > height) position.y = height;
    }
};

#endif
