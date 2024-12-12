#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <SFML/Graphics.hpp>

class Projectile {
public:
    sf::RectangleShape shape;
    sf::Vector2f direction;

    Projectile(sf::Vector2f startPos, sf::Vector2f dir);
    void move();
    bool outOfBounds(/*int width, int height*/);
};

#endif
