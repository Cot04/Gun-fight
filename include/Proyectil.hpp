#ifndef PROYECTIL_HPP
#define PROYECTIL_HPP

#include <SFML/Graphics.hpp>

class Proyectil {
public:
    sf::RectangleShape shape;
    sf::Vector2f direction;

    Proyectil(sf::Vector2f startPos, sf::Vector2f dir);
    void mover();
    bool fueraDeLimites();
};

#endif // PROYECTIL_HPP
