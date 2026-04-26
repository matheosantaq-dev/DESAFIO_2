#include "Torneo.h"
#include "Medidor.h"
#include <iostream>


// Constructor

Torneo::Torneo() : totalGoles(0) {
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
        if (g) delete g;
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

            Equipo* e = listaEquipos.obtener(index);
            if (e) {
                bombos[i][j] = e;
            }

            index++;
        }
    }

    std::cout << "Bombos organizados correctamente.\n";
}


// Crear grupos

void Torneo::crearGrupos() {

    for (int i = 0; i < 12; i++) {

        Medidor::it();

        char id = 'A' + i;
        Grupo* nuevoGrupo = new Grupo(id);

        Medidor::add(sizeof(Grupo));

        for (int b = 0; b < 4; b++) {
            if (bombos[b][i]) {
                nuevoGrupo->agregarEquipo(bombos[b][i]);
            }
        }

        nuevoGrupo->organizarEncuentros("01/06/2026");

        grupos.insertarAlFinal(nuevoGrupo);
    }
}


// Simular fase de grupos

void Torneo::simularFaseGrupos() {

    for (int i = 0; i < grupos.getTamanio(); i++) {

        Medidor::it();

        Grupo* g = grupos.obtener(i);
        if (g) {
            g->simularFaseGrupal();
            g->mostrarResultados();  
        }
    }
}


// Mostrar estadísticas

void Torneo::generarEstadisticas() {

    for (int i = 0; i < grupos.getTamanio(); i++) {

        Medidor::it();

        Grupo* g = grupos.obtener(i);
        if (g) {
            g->mostrarTabla();
        }
    }
}


// Eliminatorias 

void Torneo::simularEliminatorias() {
    std::cout << "Simulando eliminatorias...\n";
}
