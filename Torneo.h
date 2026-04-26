#ifndef TORNEO_H
#define TORNEO_H

#include "ListaDinamica.h"
#include "Grupo.h"
#include "Equipo.h"
#include "Partido.h"

class Torneo {
private:
    ListaDinamica<Grupo*> grupos;

    // Bombos oficiales
    Equipo* bombos[4][12];

    // Clasificados
    ListaDinamica<Equipo*> clasificados;

    // Estadísticas generales
    int totalGoles;
    Equipo* campeon;
    Equipo* subcampeon;
    Equipo* tercerLugar;

    // Métodos auxiliares
    void avanzarRonda(
        ListaDinamica<Equipo*>& participantes,
        ListaDinamica<Equipo*>& ganadores,
        const std::string& fase
    );

public:
    // Constructor / Destructor
    Torneo();
    ~Torneo();

    // Organización
    void organizarBombos(ListaDinamica<Equipo*>& listaEquipos);
    void crearGrupos();

    // Simulación
    void simularFaseGrupos();
    void clasificarEquipos();
    void simularEliminatorias();

    // Estadísticas
    void generarEstadisticas();
    void mostrarPodio();

    // Getters
    ListaDinamica<Grupo*>& getGrupos();
};

#endif
