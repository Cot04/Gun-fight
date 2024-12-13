#ifndef JUEGO_HPP
#define JUEGO_HPP

#include <SFML/Graphics.hpp>
#include "Jugador.hpp"
#include "Colision.hpp"

class Juego
{
private:
    sf::RenderWindow ventana;
    sf::Font fuente;
    sf::Text textoVidasP1, textoVidasP2;
    Jugador p1, p2;
    int puntuacionRojo = 0;
    int puntuacionAzul = 0;
    bool finDelJuego = false;

    void configurarTexto(sf::Text &texto, sf::Vector2f posicion);
    void procesarEventos();
    void actualizar();
    void renderizar();
    void reiniciar();

public:
    Juego();
    void ejecutar();
};

#endif // JUEGO_HPP
