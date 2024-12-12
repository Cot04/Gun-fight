#include "Juego.hpp"
#include <iostream>

#define WIDTH 800
#define HEIGHT 600

Juego::Juego()
    : ventana(sf::VideoMode(WIDTH, HEIGHT), "Gunfight"),
      p1("./assets/images/gunfight.png", {100, HEIGHT / 2}, 10),
      p2("./assets/images/gunfight2.png", {WIDTH - 100, HEIGHT / 2}, 10) {

    if (!fuente.loadFromFile("./assets/fonts/Ring.ttf")) {
        std::cerr << "Error al cargar la fuente" << std::endl;
        exit(-1);
    }

    p1.sprite.setScale(0.2f, 0.2f);
    p2.sprite.setScale(0.2f, 0.2f);

    configurarTexto(textoVidasP1, {0, 0});
    configurarTexto(textoVidasP2, {0, 60});
}

void Juego::configurarTexto(sf::Text &texto, sf::Vector2f posicion) {
    texto.setFont(fuente);
    texto.setCharacterSize(24);
    texto.setFillColor(sf::Color::White);
    texto.setPosition(posicion);
}

void Juego::procesarEventos() {
    sf::Event evento;
    while (ventana.pollEvent(evento)) {
        if (evento.type == sf::Event::Closed)
            ventana.close();

        if (finDelJuego && sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            reiniciar();
        }
    }
}

void Juego::actualizar() {
    if (finDelJuego) return;

    // Movimiento y disparos de jugadores
    p1.direccion = {0, 0};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) p1.direccion.y = -1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) p1.direccion.y = 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) p1.direccion.x = -1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) p1.direccion.x = 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
        p1.disparar(p1.direccion, p1.sprite.getPosition());

    p2.direccion = {0, 0};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) p2.direccion.y = -1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) p2.direccion.y = 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) p2.direccion.x = -1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
        p2.direccion.x = 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) 
        p2.disparar(p2.direccion, p2.sprite.getPosition());

    p1.mover();
    p2.mover();
    p1.actualizarProyectiles();
    p2.actualizarProyectiles();

    // Manejo de colisiones
    Colision::manejarColisiones(p1, p2, puntuacionRojo);
    Colision::manejarColisiones(p2, p1, puntuacionAzul);

    if (p1.vidas <= 0 || p2.vidas <= 0) {
        finDelJuego = true;
    }

    textoVidasP1.setString("Vidas Jugador 1: " + std::to_string(p1.vidas));
    textoVidasP2.setString("Vidas Jugador 2: " + std::to_string(p2.vidas));
}

void Juego::renderizar() {
    ventana.clear();
    p1.dibujar(ventana);
    p2.dibujar(ventana);
    ventana.draw(textoVidasP1);
    ventana.draw(textoVidasP2);

    if (finDelJuego) {
        sf::Text textoFin;
        textoFin.setFont(fuente);
        textoFin.setCharacterSize(30);
        textoFin.setFillColor(sf::Color::White);
        textoFin.setString((p1.vidas <= 0) ? "Jugador 2 Gana" : "Jugador 1 Gana");
        textoFin.setPosition(WIDTH / 2 - textoFin.getLocalBounds().width / 2, HEIGHT / 2);
        ventana.draw(textoFin);
    }

    ventana.display();
}

void Juego::reiniciar() {
    p1.sprite.setPosition({100, HEIGHT / 2});
    p2.sprite.setPosition({WIDTH - 100, HEIGHT / 2});
    p1.vidas = 10;
    p2.vidas = 10;
    p1.proyectiles.clear();
    p2.proyectiles.clear();
    puntuacionRojo = 0;
    puntuacionAzul = 0;
    finDelJuego = false;
}

void Juego::ejecutar() {
    while (ventana.isOpen()) {
        procesarEventos();
        actualizar();
        renderizar();
    }
}
