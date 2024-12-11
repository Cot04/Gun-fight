#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Vaqueros");

    // Cargar la textura del vaquero
    sf::Texture cowboyTexture;
    if (!cowboyTexture.loadFromFile("assets/images/Cowboy2.png")) {
        std::cerr << "Error al cargar la imagen del vaquero.\n";
        return -1;
    }

    // Crear el sprite del vaquero
    sf::Sprite cowboy;
    cowboy.setTexture(cowboyTexture);
    cowboy.setPosition(100, 100); // Posición inicial
    cowboy.setScale(0.4f, 0.4f); //tamaño a la micha

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Mover al vaquero con las teclas
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            cowboy.move(0, -1);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            cowboy.move(0, 1);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            cowboy.move(-1, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            cowboy.move(1, 0);

        window.clear();
        window.draw(cowboy);
        window.display();
    }

    return 0;
}
