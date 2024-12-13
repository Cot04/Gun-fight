#include "Juego.hpp"
#include "Musica.hpp"
#include <iostream>

int main() {
    Musica musica;

    if(!musica.cargarMusica("./assets/music/Music.ogg")){
        std::cerr <<"No se pudo cargar la música."<< std::endl;
        return -1;
    }

    musica.reproducir();
    
    Juego juego;
    juego.ejecutar();
    return 0;
}
