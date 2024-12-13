// Musica.cpp
#include "Musica.hpp"
#include <iostream>

Musica::Musica() {}

Musica::~Musica() {}

bool Musica::cargarMusica(const std::string &rutaArchivo)
{
    if (!musica.openFromFile(rutaArchivo))
    {
        std::cerr << "Error al cargar el archivo de música: " << rutaArchivo << std::endl;
        return false;
    }
    return true;
}

void Musica::reproducir()
{
    musica.play();
}

sf::Music::Status Musica::obtenerEstado() const
{
    return musica.getStatus();
}
