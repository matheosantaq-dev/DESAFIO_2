#include "Torneo.h"
#include "Medidor.h"
#include <iostream>
#include <cstdlib>

// Constructor
Torneo::Torneo()
    : totalGoles(0),
    campeon(nullptr),
    subcampeon(nullptr),
    tercerLugar(nullptr)
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 12; j++) {
            bombos[i][j] = nullptr;
        }
    }
}

// Destructor
Torneo::~Torneo() {
    for (int i = 0; i < grupos.getTamanio(); i++) {
        Medidor::it();

        Grupo* g = grupos.obtener(i);
        if (g) {
            delete g;
        }
    }
}

// Organizar bombos
void Torneo::organizarBombos(ListaDinamica<Equipo*>& listaEquipos) {
    if (listaEquipos.getTamanio() < 48) {
        std::cerr << "Error: Se requieren 48 equipos.\n";
        return;
    }

    listaEquipos.ordenarPorRanking();

    int index = 0;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 12; j++) {
            Medidor::it();

            bombos[i][j] = listaEquipos.obtener(index);
            index++;
        }
    }

    std::cout << "Bombos organizados correctamente.\n";
}

// Crear grupos
void Torneo::crearGrupos() {
    for (int i = 0; i < 12; i++) {
        Medidor::it();

        Grupo* grupo = new Grupo('A' + i);

        for (int b = 0; b < 4; b++) {
            if (bombos[b][i]) {
                grupo->agregarEquipo(bombos[b][i]);
            }
        }

        grupo->organizarEncuentros("01/06/2026");

        grupos.insertarAlFinal(grupo);
    }
}

// Simular grupos
void Torneo::simularFaseGrupos() {
    for (int i = 0; i < grupos.getTamanio(); i++) {
        Medidor::it();

        Grupo* grupo = grupos.obtener(i);

        if (grupo) {
            grupo->simularFaseGrupal();
            grupo->mostrarResultados();
        }
    }

    clasificarEquipos();
}

// Clasificar primeros 2 de cada grupo
void Torneo::clasificarEquipos() {
    clasificados.limpiar();

    for (int i = 0; i < grupos.getTamanio(); i++) {
        Medidor::it();

        Grupo* grupo = grupos.obtener(i);

        if (!grupo) continue;

        grupo->ordenarTabla();

        Equipo* primero = grupo->getEquipo(0);
        Equipo* segundo = grupo->getEquipo(1);

        if (primero) clasificados.insertarAlFinal(primero);
        if (segundo) clasificados.insertarAlFinal(segundo);
    }

    std::cout << "\nClasificados a dieciseisavos: "
              << clasificados.getTamanio()
              << " equipos.\n";
}

// Simular ronda eliminatoria
void Torneo::avanzarRonda(
    ListaDinamica<Equipo*>& participantes,
    ListaDinamica<Equipo*>& ganadores,
    const std::string& fase
    ) {
    std::cout << "\n=== " << fase << " ===\n";

    for (int i = 0; i < participantes.getTamanio(); i += 2) {
        Medidor::it();

        Equipo* a = participantes.obtener(i);
        Equipo* b = participantes.obtener(i + 1);

        if (!a || !b) continue;

        Partido partido(a, b);
        partido.simular(true);
        partido.printResumen();

        Equipo* ganador =
            (partido.getGolesLocal() > partido.getGolesVisitante())
                ? a
                : b;

        ganadores.insertarAlFinal(ganador);
    }
}

// Eliminatorias completas
void Torneo::simularEliminatorias() {
    ListaDinamica<Equipo*> rondaActual = clasificados;

    ListaDinamica<Equipo*> dieciseisavos;
    avanzarRonda(rondaActual, dieciseisavos, "Dieciseisavos");

    ListaDinamica<Equipo*> octavos;
    avanzarRonda(dieciseisavos, octavos, "Octavos");

    ListaDinamica<Equipo*> cuartos;
    avanzarRonda(octavos, cuartos, "Cuartos");

    ListaDinamica<Equipo*> semifinalistas;
    avanzarRonda(cuartos, semifinalistas, "Semifinales");

    // Tercer lugar
    Partido tercerPuesto(
        semifinalistas.obtener(0),
        semifinalistas.obtener(1)
        );

    tercerPuesto.simular(true);

    tercerLugar =
        (tercerPuesto.getGolesLocal() >
         tercerPuesto.getGolesVisitante())
            ? semifinalistas.obtener(0)
            : semifinalistas.obtener(1);

    // Final
    ListaDinamica<Equipo*> finalistas;
    avanzarRonda(semifinalistas, finalistas, "Final");

    if (finalistas.getTamanio() >= 2) {
        Partido final(finalistas.obtener(0), finalistas.obtener(1));
        final.simular(true);

        if (final.getGolesLocal() > final.getGolesVisitante()) {
            campeon = finalistas.obtener(0);
            subcampeon = finalistas.obtener(1);
        } else {
            campeon = finalistas.obtener(1);
            subcampeon = finalistas.obtener(0);
        }

        std::cout << "\n=== FINAL ===\n";
        final.printResumen();
    }
}

// Estadísticas
void Torneo::generarEstadisticas() {
    for (int i = 0; i < grupos.getTamanio(); i++) {
        Medidor::it();

        Grupo* grupo = grupos.obtener(i);

        if (grupo) {
            grupo->mostrarTabla();
        }
    }

    mostrarPodio();
}

// Mostrar podio
void Torneo::mostrarPodio() {
    std::cout << "\n=========== PODIO MUNDIAL ===========\n";

    if (campeon) {
        std::cout << "🥇 Campeón: " << campeon->getPais() << "\n";
    }

    if (subcampeon) {
        std::cout << "🥈 Subcampeón: " << subcampeon->getPais() << "\n";
    }

    if (tercerLugar) {
        std::cout << "🥉 Tercer Lugar: " << tercerLugar->getPais() << "\n";
    }

    std::cout << "=====================================\n";
}

// Getter
ListaDinamica<Grupo*>& Torneo::getGrupos() {
    return grupos;
}

