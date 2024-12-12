#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Player.hpp"

class Game {
public:
    Game();
    void run();

private:
    sf::RenderWindow window;
    Player player1;
    Player player2;
    sf::Font font;
    sf::Sprite background;
    sf::Texture backgroundTexture;

    void handleEvents();
    void update();
    void render();
    bool checkCollision(Player &shooter, Player &target);
    void handleCollisions(Player &shooter, Player &target);
};

#endif
