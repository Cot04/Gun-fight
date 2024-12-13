#ifndef COLISION_HPP
#define COLISION_HPP

#include "Jugador.hpp"

class Colision
{
public:
    static void manejarColisiones(Jugador &atacante, Jugador &objetivo, int &puntuacion);
};

#endif // COLISION_HPP
