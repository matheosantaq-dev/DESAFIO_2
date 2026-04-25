#include "Grupo.h"
#include <iostream>
#include <iomanip>
Grupo::Grupo(char id) : id(id), numPartidos(0) {}


Grupo::~Grupo() {
    for (int i = 0; i < partidos.getTamanio(); i++) {
        Partido* p = partidos.obtener(i);
        if (p != nullptr) {
            delete p; //
        }
    }
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
        int iE = emparejamientos[p][0];
        int jE = emparejamientos[p][1];

        // Creación del partido dinámicamente
        Partido* nuevoPartido = new Partido(equipos.obtener(iE), equipos.obtener(jE));
        partidos.insertarAlFinal(nuevoPartido);
        numPartidos++;
    }
}

void Grupo::simularFaseGrupal() {
    for (int i = 0; i < partidos.getTamanio(); i++) {
        Partido* p = partidos.obtener(i);
        if (p != nullptr) {
            p->simular();
        }
    }
}

void Grupo::mostrarResultados() const {
    std::cout << "\nResultados Grupo " << id << ":" << std::endl;
    for (int i = 0; i < partidos.getTamanio(); i++) {
        Partido* p = partidos.obtener(i);
        if (p != nullptr) {
            p->printResumen();
        }
    }
}

//  Implementación lógica de la tabla
void Grupo::mostrarTabla() {
    std::cout << "\n--- TABLA POSICIONES GRUPO " << id << " ---" << std::endl;
    //ORDENAR EQUIPOS ANTES DE MOSTRAR
    for (int i = 0; i < equipos.getTamanio(); i++) {
        for (int j = i + 1; j < equipos.getTamanio(); j++) {

            Equipo* a = equipos.obtener(i);
            Equipo* b = equipos.obtener(j);

            int dgA = a->getGolesFavor() - a->getGolesContra();
            int dgB = b->getGolesFavor() - b->getGolesContra();

             if (b->getPuntos() > a->getPuntos() ||
                (b->getPuntos() == a->getPuntos() && dgB > dgA) ||
                (b->getPuntos() == a->getPuntos() && dgB == dgA &&
                 b->getGolesFavor() > a->getGolesFavor())) {
                equipos.intercambiar(i, j);
            }
        }
    }
    std::cout << "Equipo\t\tPTS\tDG\tGF" << std::endl;

    for (int i = 0; i < equipos.getTamanio(); i++) {
        Equipo* e = equipos.obtener(i);
        if (e != nullptr) {
            // DG (Diferencia de Goles = Favor - Contra)
            int dg = e->getGolesFavor() - e->getGolesContra();

            std::cout << e->getPais() << "\t\t"
                      << e->getPuntos() << "\t"
                      << dg << "\t"
                      << e->getGolesFavor() << std::endl;
        }
    }
    std::cout << "------------------------------------------" << std::endl;
}
