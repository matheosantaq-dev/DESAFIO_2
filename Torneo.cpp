#include "Torneo.h"
#include "Medidor.h"
#include <iostream>

// Constructor
Torneo::Torneo()
    : totalGoles(0), campeon(nullptr),
    subcampeon(nullptr), tercerLugar(nullptr)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 12; j++)
            bombos[i][j] = nullptr;
}

// Destructor
Torneo::~Torneo() {
    for (int i = 0; i < grupos.getTamanio(); i++) {
        delete grupos.obtener(i);
    }
}

// Bombos
void Torneo::organizarBombos(ListaDinamica<Equipo*>& listaEquipos) {

    listaEquipos.ordenarPorRanking();

    int k = 0;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 12; j++)
            bombos[i][j] = listaEquipos.obtener(k++);
}

// Crear grupos
void Torneo::crearGrupos() {

    grupos.limpiar();

    for (int i = 0; i < 12; i++) {

        Grupo* g = new Grupo('A' + i);

        for (int b = 0; b < 4; b++) {
            g->agregarEquipo(bombos[b][i]);
        }

        g->organizarEncuentros("01/06/2026");
        grupos.insertarAlFinal(g);
    }

    std::cout << "Grupos creados correctamente\n";
}

// Fase grupos
void Torneo::simularFaseGrupos() {

    for (int i = 0; i < grupos.getTamanio(); i++) {
        Grupo* g = grupos.obtener(i);
        g->simularFaseGrupal();
        g->mostrarResultados();
    }

    clasificarEquipos();
}

// Clasificación
void Torneo::clasificarEquipos() {

    clasificados.limpiar();

    for (int i = 0; i < grupos.getTamanio(); i++) {

        Grupo* g = grupos.obtener(i);

        Equipo** top2 = g->getClasificados();

        clasificados.insertarAlFinal(top2[0]);
        clasificados.insertarAlFinal(top2[1]);

        delete[] top2;
    }

    std::cout << "\nClasificados: "
              << clasificados.getTamanio()
              << " equipos.\n";
}

//  FUNCIÓN CLAVE
Equipo* jugarPartido(Equipo* a, Equipo* b, Equipo*& perdedor) {

    Partido p(a, b, "20/06/2026", "Estadio");
    p.simular(true);
    p.printResumen();

    if (p.getGolesLocal() > p.getGolesVisitante()) {
        perdedor = b;
        return a;
    } else {
        perdedor = a;
        return b;
    }
}

void Torneo::simularEliminatorias() {

    ListaDinamica<Equipo*> ronda = clasificados;

    //  PRIMER FILTRO: 24 → 16
    ListaDinamica<Equipo*> ronda16;

    std::cout << "\n=== DIECISEISAVOS ===\n";

    for (int i = 0; i < 16; i++) {
        ronda16.insertarAlFinal(ronda.obtener(i));
    }

    ronda = ronda16;

    // RONDAS NORMALES
    while (ronda.getTamanio() > 4) {

        ListaDinamica<Equipo*> siguiente;

        std::cout << "\n=== RONDA ===\n";

        for (int i = 0; i < ronda.getTamanio(); i += 2) {

            Equipo* perdedor;
            Equipo* ganador = jugarPartido(
                ronda.obtener(i),
                ronda.obtener(i + 1),
                perdedor
                );

            siguiente.insertarAlFinal(ganador);
        }

        ronda = siguiente;
    }

    //  SEMIFINALES
    std::cout << "\n=== SEMIFINALES ===\n";

    Equipo* perd1;
    Equipo* finalista1 = jugarPartido(ronda.obtener(0), ronda.obtener(1), perd1);

    Equipo* perd2;
    Equipo* finalista2 = jugarPartido(ronda.obtener(2), ronda.obtener(3), perd2);

    //  TERCER PUESTO
    std::cout << "\n=== TERCER PUESTO ===\n";

    Equipo* basura;
    tercerLugar = jugarPartido(perd1, perd2, basura);

    // FINAL
    std::cout << "\n=== FINAL ===\n";

    Equipo* perdFinal;
    campeon = jugarPartido(finalista1, finalista2, perdFinal);
    subcampeon = perdFinal;
}

// Estadísticas
void Torneo::generarEstadisticas() {

    for (int i = 0; i < grupos.getTamanio(); i++) {
        grupos.obtener(i)->mostrarTabla();
    }

    mostrarPodio();
}

// Podio
void Torneo::mostrarPodio() {

    std::cout << "\n=========== PODIO MUNDIAL ===========\n";

    if (campeon)
        std::cout << "Campeon: " << campeon->getPais() << "\n";
    else
        std::cout << "Campeon: N/A\n";

    if (subcampeon)
        std::cout << "Subcampeon: " << subcampeon->getPais() << "\n";

    if (tercerLugar)
        std::cout << "Tercer Lugar: " << tercerLugar->getPais() << "\n";

    std::cout << "=====================================\n";
}

// Getter
ListaDinamica<Grupo*>& Torneo::getGrupos() {
    return grupos;
}
