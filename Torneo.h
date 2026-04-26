#ifndef TORNEO_H
#define TORNEO_H

#include "ListaDinamica.h"
#include "Grupo.h"
#include "Equipo.h"

class Torneo {
private:
    ListaDinamica<Grupo*> grupos;

    // 4 bombos de 12 equipos (48 equipos total)
    Equipo* bombos[4][12];

    int totalGoles;

public:
    // Constructor y destructor
    Torneo();
    ~Torneo();

    // Organización
    void organizarBombos(ListaDinamica<Equipo*>& listaEquipos);
    void crearGrupos();

    // Simulación
    void simularFaseGrupos();
    void simularEliminatorias();

    // Estadísticas
    void generarEstadisticas();

    // Getters (IMPORTANTE)
    ListaDinamica<Grupo*>& getGrupos();
};

#endif
