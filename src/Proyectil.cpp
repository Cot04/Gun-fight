#include "Proyectil.hpp"

#define WIDTH 800
#define HEIGHT 600
#define PROJECTILE_SPEED 0.2

Proyectil::Proyectil(sf::Vector2f startPos, sf::Vector2f dir) {
    shape.setSize({6, 6});
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(startPos);
    direction = dir;
}

void Proyectil::mover() {
    shape.move(direction * (float)PROJECTILE_SPEED);
}

bool Proyectil::fueraDeLimites() {
    sf::Vector2f pos = shape.getPosition();
    return (pos.x < 0 || pos.x > WIDTH || pos.y < 0 || pos.y > HEIGHT);
}
