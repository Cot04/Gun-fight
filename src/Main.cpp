#include <SFML/Graphics.hpp>
#include "Constants.hpp"
#include "Player.hpp"
#include "Collision.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Gunfight");
    Player p1("./assets/images/gunfight.png", {100, HEIGHT / 2}, 10);
    Player p2("assets/images/gunfight2.png", {WIDTH - 100, HEIGHT / 2}, 10);

    int redScore = 0, blueScore = 0;
    // Cargar recursos adicionales, etc.
    // Lógica principal del juego...

    return 0;
}
