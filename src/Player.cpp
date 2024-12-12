#include "Player.hpp"
#include "Constants.hpp"
#include <iostream>

Player::Player(const std::string &texturePath, sf::Vector2f startPos, int initialLives) : lives(initialLives) {
    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "Error al cargar la textura " << texturePath << std::endl;
        exit(-1);
    }
    sprite.setTexture(texture);
    sprite.setPosition(startPos);
}

void Player::Move() {
    sf::Vector2f newPosition = sprite.getPosition() + direction * MOVE_SPEED;
    if (newPosition.x < 0) newPosition.x = 0;
    if (newPosition.y < 0) newPosition.y = 0;
    if (newPosition.x + sprite.getGlobalBounds().width > WIDTH)
        newPosition.x = WIDTH - sprite.getGlobalBounds().width;
    if (newPosition.y + sprite.getGlobalBounds().height > HEIGHT)
        newPosition.y = HEIGHT - sprite.getGlobalBounds().height;
    sprite.setPosition(newPosition);
}

void Player::shoot(sf::Keyboard::Key fireKey) {
    if (sf::Keyboard::isKeyPressed(fireKey) && !shootRunning) {
        clock.restart();
        shootRunning = true;
        if (direction != sf::Vector2f(0, 0)) {
            sf::Vector2f startpos = sprite.getPosition() + 
                                    sf::Vector2f(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
            projectiles.push_back(Projectile(startpos, direction));
        }
    }
    if (clock.getElapsedTime().asSeconds() >= shootTime) {
        shootRunning = false;
    }
}

void Player::draw(sf::RenderWindow &window) {
    window.draw(sprite);
    for (auto &p : projectiles) {
        window.draw(p.shape);
    }
}

void Player::updateProjectiles() {
    for (auto &p : projectiles) {
        p.move();
    }
    projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(), [](Projectile &p) {
        return p.outofBounds();
    }), projectiles.end());
}
