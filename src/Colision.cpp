#include "Colision.hpp"
#include <iostream>

void Colision::manejarColisiones(Jugador &atacante, Jugador &objetivo, int &puntuacion)
{
    for (auto it = atacante.proyectiles.begin(); it != atacante.proyectiles.end();)
    {
        if (it->shape.getGlobalBounds().intersects(objetivo.sprite.getGlobalBounds()))
        {
            objetivo.vidas--;
            puntuacion++;
            it = atacante.proyectiles.erase(it);
        }
        else
        {
            ++it;
        }
    }
    auto &proyectiles = atacante.proyectiles;

    proyectiles.erase(std::remove_if(proyectiles.begin(), proyectiles.end(), [&](Proyectil &p)
                                     {
        if (objetivo.sprite.getGlobalBounds().intersects(p.shape.getGlobalBounds())) {
            if (objetivo.vidas > 0) {
                objetivo.vidas--;
                puntuacion++;
            }
            return true;
        }
        return false; }),
                      proyectiles.end());
}
