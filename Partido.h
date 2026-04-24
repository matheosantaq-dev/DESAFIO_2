#ifndef PARTIDO_H
#define PARTIDO_H

#include "Equipo.h"

class Partido {
private:
    Equipo* local;
    Equipo* visitante;
    int golesLocal;
    int golesVisitante;

public:
    Partido(Equipo* l, Equipo* v);

    // Método principal para la lógica de simulación del encuentro.
    void simular();
};

#endif
