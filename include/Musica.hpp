#ifndef MUSICA_HPP
#define MUSICA_HPP

#include <SFML/Audio.hpp>
#include <string>

// Clase para manejar la reproducción de música
class Musica {
public:
    Musica();                           // Constructor
    ~Musica();                          // Destructor

    // Carga un archivo de música desde una ruta específica
    bool cargarMusica(const std::string& rutaArchivo);

    // Reproduce la música cargada
    void reproducir();

    // Devuelve el estado actual de la música (Playing, Paused, Stopped)
    sf::Music::Status obtenerEstado() const;

private:
    sf::Music musica;                   // Objeto de música de SFML
};

#endif // MUSICA_HPP
