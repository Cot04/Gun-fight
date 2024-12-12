#include "Jugador.hpp"
#include <iostream>

#define WIDTH 800
#define HEIGHT 600
#define MOVE_SPEED 0.03f

Jugador::Jugador(const std::string &texturePath, sf::Vector2f startPos, int vidasIniciales) 
    : vidas(vidasIniciales), direccion(0, 0) {
    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "Error cargando textura: " << texturePath << std::endl;
        exit(-1);
    }
    sprite.setTexture(texture);
    sprite.setPosition(startPos);
}

void Jugador::mover() {
    sf::Vector2f nuevaPosicion = sprite.getPosition() + direccion * MOVE_SPEED;
    if (nuevaPosicion.x < 0) nuevaPosicion.x = 0;
    if (nuevaPosicion.y < 0) nuevaPosicion.y = 0;
    if (nuevaPosicion.x + sprite.getGlobalBounds().width > WIDTH)
        nuevaPosicion.x = WIDTH - sprite.getGlobalBounds().width;
    if (nuevaPosicion.y + sprite.getGlobalBounds().height > HEIGHT)
        nuevaPosicion.y = HEIGHT - sprite.getGlobalBounds().height;

    sprite.setPosition(nuevaPosicion);
}

void Jugador::disparar(const sf::Vector2f &direccion, const sf::Vector2f &startPos) {
    proyectiles.emplace_back(startPos, direccion);
}

void Jugador::actualizarProyectiles() {
    for (auto &proyectil : proyectiles) {
        proyectil.mover();
    }
    proyectiles.erase(std::remove_if(proyectiles.begin(), proyectiles.end(),
                                     [](Proyectil &p) { return p.fueraDeLimites(); }),
                      proyectiles.end());
}

void Jugador::dibujar(sf::RenderWindow &ventana) {
    ventana.draw(sprite);
    for (auto &proyectil : proyectiles) {
        ventana.draw(proyectil.shape);
    }
}
