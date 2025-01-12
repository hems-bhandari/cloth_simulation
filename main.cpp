#include <SFML/Graphics.hpp>
#include <vector>
#include "particle.h"
#include "resistance.h"
#include "input_h.h"

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 640;
const float PARTICLE_SIZE = 1.0f;
const float GRAVITY_FORCE = 10.0f;
const float SIMULATION_STEP = 0.1f;

const int GRID_ROWS = 100;
const int GRID_COLS = 100;
const float LINK_DISTANCE = 4.0f;

int main() {
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Cloth Simulation");
    window.setFramerateLimit(60);

    std::vector<Particle> particles;
    std::vector<Resistance> constraints;

    for (int row = 0; row < GRID_ROWS; ++row) {
        for (int col = 0; col < GRID_COLS; ++col) {
            float x = col * LINK_DISTANCE + SCREEN_WIDTH / 4;
            float y = row * LINK_DISTANCE + SCREEN_HEIGHT / 4;
            bool pinned = (row == 0);
            particles.emplace_back(x, y, pinned);
        }
    }

    for (int row = 0; row < GRID_ROWS; ++row) {
        for (int col = 0; col < GRID_COLS; ++col) {
            if (col < GRID_COLS - 1) constraints.emplace_back(&particles[row * GRID_COLS + col], &particles[row * GRID_COLS + col + 1]);
            if (row < GRID_ROWS - 1) constraints.emplace_back(&particles[row * GRID_COLS + col], &particles[(row + 1) * GRID_COLS + col]);
        }
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            InputHandler::process_mouse_click(event, particles, constraints);
        }

        for (auto& particle : particles) {
            particle.add_force(sf::Vector2f(0, GRAVITY_FORCE));
            particle.simulate(SIMULATION_STEP);
            particle.keep_within_bounds(SCREEN_WIDTH, SCREEN_HEIGHT);
        }

        for (int i = 0; i < 5; ++i) {
            for (auto& constraint : constraints) {
                constraint.enforce();
            }
        }

        window.clear(sf::Color::Black);

        for (const auto& particle : particles) {
            sf::CircleShape circle(PARTICLE_SIZE);
            circle.setFillColor(sf::Color::White);
            circle.setPosition(particle.position.x - PARTICLE_SIZE, particle.position.y - PARTICLE_SIZE);
            window.draw(circle);
        }

        for (const auto& constraint : constraints) {
            if (!constraint.is_active) continue;
            sf::Vertex line[] = { sf::Vertex(constraint.start->position, sf::Color::White),
                                  sf::Vertex(constraint.end->position, sf::Color::White) };
            window.draw(line, 2, sf::Lines);
        }

        window.display();
    }

    return 0;
}
