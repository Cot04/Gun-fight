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
    int vidas;

    Jugador(const std::string &texturePath, sf::Vector2f startPos, int vidasIniciales);
    void mover();
    void disparar(const sf::Vector2f &direccion, const sf::Vector2f &startPos);
    void actualizarProyectiles();
    void dibujar(sf::RenderWindow &ventana);
};

#endif // JUGADOR_HPP
