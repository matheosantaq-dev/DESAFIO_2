#ifndef PARTIDO_H
#define PARTIDO_H

#include "Equipo.h"

class Partido {
private:
    Equipo* local;
    Equipo* visitante;

    int golesLocal;
    int golesVisitante;

    double posesionLocal;
    double posesionVisitante;

    // Modelo de generación de goles
    double calcularLambda(Equipo* ataque, Equipo* defensa);

public:
    // Constructor
    Partido(Equipo* l, Equipo* v);

    // Simulación completa del partido
    void simular();

    // Mostrar resultado
    void printResumen() const;

    // Getters
    Equipo* getLocal() const;
    Equipo* getVisitante() const;
    int getGolesLocal() const;
    int getGolesVisitante() const;
};

#endif
