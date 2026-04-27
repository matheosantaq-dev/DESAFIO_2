#ifndef TORNEO_H
#define TORNEO_H

#include "ListaDinamica.h"
#include "Equipo.h"
#include "Grupo.h"
#include <string>

class Torneo {
private:
    // Bombos (4 bombos de 12 equipos)
    Equipo* bombos[4][12];

    // Estructura del torneo
    ListaDinamica<Grupo*> grupos;
    ListaDinamica<Equipo*> clasificados;

    // Estadísticas globales
    int totalGoles;

    // Podio
    Equipo* campeon;
    Equipo* subcampeon;
    Equipo* tercerLugar;

public:
    // Constructor / Destructor
    Torneo();
    ~Torneo();

    // Organización
    void organizarBombos(ListaDinamica<Equipo*>& listaEquipos);
    void crearGrupos();

    // Fase de grupos
    void simularFaseGrupos();
    void clasificarEquipos();

    // Eliminatorias
    void simularEliminatorias();

    // Estadísticas
    void generarEstadisticas();
    void mostrarPodio();

    // guardar resultados en CSV
    void guardarCSV(const std::string& ruta, ListaDinamica<Equipo*>& equipos);

    // Getter
    ListaDinamica<Grupo*>& getGrupos();
};

#endif
