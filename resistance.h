#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include "particle.h"
#include <cmath>
#include <limits>

class Resistance {
public:
    Particle* start;
    Particle* end;
    float rest_length;
    bool is_active;

    Resistance(Particle* start, Particle* end) : start(start), end(end), is_active(true) {
        rest_length = std::hypot(end->position.x - start->position.x,
                                end->position.y - start->position.y);
    }

    void enforce() {
        if (!is_active) return;

        sf::Vector2f diff = end->position - start->position;
        float current_length = std::hypot(diff.x, diff.y);
        float delta = (current_length - rest_length) / current_length;
        sf::Vector2f adjust = diff * 0.5f * delta;

        if (!start->is_pinned) start->position += adjust;
        if (!end->is_pinned) end->position -= adjust;
    }

    void deactivate() { is_active = false; }
};

#endif