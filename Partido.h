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
    // Constructor
    Partido(Equipo* l, Equipo* v);

    // Método principal para la lógica de simulación
    void simular();

    // Getters para acceder a la información del partido si se requiere
    Equipo* getLocal() const { return local; }
    Equipo* getVisitante() const { return visitante; }
    int getGolesLocal() const { return golesLocal; }
    int getGolesVisitante() const { return golesVisitante; }
};

#endif
