#include "Colision.hpp"

void Colision::manejarColisiones(Jugador &atacante, Jugador &objetivo, int &puntuacion) {
    auto &proyectiles = atacante.proyectiles;

    proyectiles.erase(std::remove_if(proyectiles.begin(), proyectiles.end(), [&](Proyectil &p) {
        if (objetivo.sprite.getGlobalBounds().intersects(p.shape.getGlobalBounds())) {
            if (objetivo.vidas > 0) {
                objetivo.vidas--;
                puntuacion++;
            }
            return true;
        }
        return false;
    }), proyectiles.end());
}
