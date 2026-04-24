#include "Torneo.h"
#include <iostream>

Torneo::Torneo() : totalGoles(0) {
    // Inicializar bombos como nullptr
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 12; j++) {
            bombos[i][j] = nullptr;
        }
    }
}

//  Destructor para liberar los grupos creados con 'new'
Torneo::~Torneo() {
    for (int i = 0; i < grupos.getTamanio(); i++) {
        delete grupos.obtener(i);
    }
}

void Torneo::organizarBombos(ListaDinamica<Equipo*>& listaEquipos) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 12; j++) {
            int indice = i * 12 + j;
            if (indice < listaEquipos.getTamanio()) {
                bombos[i][j] = listaEquipos.obtener(indice);
            }
        }
    }
    std::cout << "Equipos distribuidos en bombos exitosamente." << std::endl;
}

//  Implementación de la distribución de equipos
void Torneo::crearGrupos() {
    for (int i = 0; i < 12; i++) {
        char id = 'A' + i;
        Grupo* nuevoGrupo = new Grupo(id);
        
        // Distribuir 1 equipo de cada bombo al grupo actual
        for (int b = 0; b < 4; b++) {
            if (bombos[b][i] != nullptr) {
                nuevoGrupo->agregarEquipo(bombos[b][i]);
            }
        }
        
        // Organizar los encuentros al crear el grupo
        nuevoGrupo->organizarEncuentros("01/06/2026"); 
        
        grupos.insertarAlFinal(nuevoGrupo);
    }
}

//  Implementación de simulación global
void Torneo::simularFaseGrupos() {
    for (int i = 0; i < grupos.getTamanio(); i++) {
        grupos.obtener(i)->simularFaseGrupal();
    }
}

//  Implementación de estadísticas finales
void Torneo::generarEstadisticas() {
    for (int i = 0; i < grupos.getTamanio(); i++) {
        grupos.obtener(i)->mostrarTabla();
    }
}
