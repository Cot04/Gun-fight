#include "Projectile.hpp"
#include "Constants.hpp"

Projectile::Projectile(sf::Vector2f startPos, sf::Vector2f dir)
{
    shape.setSize({PROJECTILE_SIZE, PROJECTILE_SIZE});
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(startPos);
    direction = dir;
}

void Projectile::move()
{
    shape.move(direction * (float)PROJECTILE_SPEED);
}

bool Projectile::outofBounds()
{
    sf::Vector2f pos = shape.getPosition();
    return (pos.x < 0 || pos.x > WIDTH || pos.y < 0 || pos.y > HEIGHT);
}
