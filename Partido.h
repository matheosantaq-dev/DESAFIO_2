#ifndef TORNEO_H
#define TORNEO_H

#include "ListaDinamica.h"
#include "Grupo.h"
#include "Equipo.h"
#include "Partido.h"
#include <string>

class Torneo {
private:
    ListaDinamica<Grupo*> grupos;

    Equipo* bombos[4][12];

    ListaDinamica<Equipo*> clasificados;

    int totalGoles;
    Equipo* campeon;
    Equipo* subcampeon;
    Equipo* tercerLugar;

    void avanzarRonda(
        ListaDinamica<Equipo*>& participantes,
        ListaDinamica<Equipo*>& ganadores,
        const std::string& fase
        );

public:
    Torneo();
    ~Torneo();

    void organizarBombos(ListaDinamica<Equipo*>& listaEquipos);
    void crearGrupos();

    void simularFaseGrupos();
    void clasificarEquipos();
    void simularEliminatorias();

    void generarEstadisticas();
    void mostrarPodio();

    ListaDinamica<Grupo*>& getGrupos();
};

#endif
