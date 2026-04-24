#include "Grupo.h"
#include <iostream>
#include <sstream>

Grupo::Grupo(char id) : id(id), numPartidos(0) {}

Grupo::~Grupo() {

}

void Grupo::agregarEquipo(Equipo* equipo) {
    if (equipos.getTamanio() < 4) {
        equipos.insertarAlFinal(equipo);
    }
}

void Grupo::organizarEncuentros(const std::string& fechaInicio) {
    if (equipos.getTamanio() < 4) return;


    int dia = (fechaInicio[0]-'0')*10 + (fechaInicio[1]-'0');
    int mes = (fechaInicio[3]-'0')*10 + (fechaInicio[4]-'0');
    int anio = (fechaInicio[6]-'0')*1000 + (fechaInicio[7]-'0')*100 + (fechaInicio[8]-'0')*10 + (fechaInicio[9]-'0');

    int offsetGrupo = (id - 'A') / 2;
    int jornadasDias[3] = { offsetGrupo, offsetGrupo + 6, offsetGrupo + 12 };
    
    int emparejamientos[6][2] = { {0,1}, {2,3}, {0,2}, {1,3}, {0,3}, {1,2} };

    for (int p = 0; p < 6; p++) {
        int diaRelativo = jornadasDias[p / 2];
        
  
        int d = dia + diaRelativo; 
        int m = mes; int a = anio;
      

        int iE = emparejamientos[p][0];
        int jE = emparejamientos[p][1];

        Partido* nuevoPartido = new Partido(equipos.obtener(iE), equipos.obtener(jE));
        
        partidos.insertarAlFinal(nuevoPartido);
        numPartidos++;
    }
}

void Grupo::simularFaseGrupal() {
    for (int i = 0; i < partidos.getTamanio(); i++) {
        Partido* p = partidos.obtener(i);
        if (p != nullptr) {
            p->simular(); /
        }
    }
}

void Grupo::mostrarResultados() const {
    std::cout << "\nResultados Grupo " << id << ":\n";
    for (int i = 0; i < partidos.getTamanio(); i++) {
        partidos.obtener(i)->printResumen(); 
    }
}


void Grupo::mostrarTabla() const {
    std::cout << "Tabla de Posiciones Grupo " << id << "\n";
  
}

