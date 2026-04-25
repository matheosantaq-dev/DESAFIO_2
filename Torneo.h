#ifndef TORNEO_H
#define TORNEO_H

#include "ListaDinamica.h"
#include "Grupo.h"
#include "Equipo.h"

class Torneo {
private:
    ListaDinamica<Grupo*> grupos;
    // La matriz de bombos: 4 bombos 12 equipos
    Equipo* bombos[4][12];
    int totalGoles;

public:
    Torneo();
    ~Torneo();

    void organizarBombos(ListaDinamica<Equipo*>& listaEquipos);
    void crearGrupos();
    void simularFaseGrupos();
    void simularEliminatorias();
    void generarEstadisticas();
};

#endif
