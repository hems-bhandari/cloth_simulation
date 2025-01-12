#ifndef INPUT_H_H
#define INPUT_H_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "particle.h"
#include "resistance.h"

const float MOUSE_SENSITIVITY = 5.0f;

class InputHandler {
public:
    static void process_mouse_click(const sf::Event& event, std::vector<Particle>& particles,
                                     std::vector<Resistance>& constraints) {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            float mouse_x = static_cast<float>(event.mouseButton.x);
            float mouse_y = static_cast<float>(event.mouseButton.y);
            modify_cloth(mouse_x, mouse_y, particles, constraints);
        }
    }

private:
    static float distance_to_segment(float px, float py, float x1, float y1, float x2, float y2) {
        float ABx = x2 - x1;
        float ABy = y2 - y1;
        float APx = px - x1;
        float APy = py - y1;
        float t = (ABx * APx + ABy * APy) / (ABx * ABx + ABy * ABy);

        if (t < 0.0f) return std::hypot(APx, APy);
        if (t > 1.0f) return std::hypot(px - x2, py - y2);
        float proj_x = x1 + t * ABx;
        float proj_y = y1 + t * ABy;
        return std::hypot(px - proj_x, py - proj_y);
    }

    static Resistance* closest_constraint(float mouse_x, float mouse_y, const std::vector<Resistance>& constraints) {
        Resistance* nearest = nullptr;
        float closest_dist = MOUSE_SENSITIVITY;

        for (const auto& constraint : constraints) {
            float dist = distance_to_segment(mouse_x, mouse_y, constraint.start->position.x,
                                             constraint.start->position.y, constraint.end->position.x,
                                             constraint.end->position.y);
            if (dist < closest_dist) {
                closest_dist = dist;
                nearest = const_cast<Resistance*>(&constraint);
            }
        }
        return nearest;
    }

    static void modify_cloth(float mouse_x, float mouse_y, const std::vector<Particle>& particles,
                              std::vector<Resistance>& constraints) {
        Resistance* nearest = closest_constraint(mouse_x, mouse_y, constraints);
        if (nearest) {
            nearest->deactivate();
        }
    }
};

#endif