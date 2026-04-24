#include "Torneo.h"
#include <iostream>

Torneo::Torneo() : totalGoles(0) {
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 12; j++) {
            bombos[i][j] = nullptr;
        }
    }
}

Torneo::~Torneo() {
    

void Torneo::organizarBombos(ListaDinamica<Equipo*>& listaEquipos) {
   
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 12; j++) {
            int indice = i * 12 + j;
            if (indice < listaEquipos.getTamanio()) {
                bombos[i][j] = listaEquipos[indice];
            }
        }
    }
    std::cout << "Equipos distribuidos en bombos exitosamente." << std::endl;
}

void Torneo::crearGrupos() {
    // Crear 12 grupos ('A' al 'L')
    for (int i = 0; i < 12; i++) {
        char id = 'A' + i;
        Grupo* nuevoGrupo = new Grupo(id);
        
        
        
        grupos.insertarAlFinal(nuevoGrupo);
    }
}
