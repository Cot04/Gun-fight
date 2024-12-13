#ifndef JUGADOR_HPP
#define JUGADOR_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Proyectil.hpp"

class Jugador {
public:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f direccion;
    std::vector<Proyectil> proyectiles;
    sf::Clock clock;
    float cooldownDisparo;
    int vidas;

    Jugador(const std::string &texturePath, sf::Vector2f startPos, int vidasIniciales, float cooldown = 0.1f);
    void mover();
    void disparar(const sf::Vector2f &direccion, const sf::Vector2f &startPos);
    void actualizarProyectiles();
    void dibujar(sf::RenderWindow &ventana);
};

#endif // JUGADOR_HPP
