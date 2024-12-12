#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Projectile.hpp"

class Player {
public:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f direction = {0, 0};
    std::vector<Projectile> projectiles;
    int lives;
    sf::Clock clock;
    float shootTime = 0.2f;
    bool shootRunning = false;

    Player(const std::string &texturePath, sf::Vector2f startPos, int initialLives = 10);
    void Move();
    void shoot(sf::Keyboard::Key fireKey);
    void draw(sf::RenderWindow &window);
    void updateProjectiles();
};

#endif
