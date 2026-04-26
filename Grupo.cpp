#include "Grupo.h"
#include "Medidor.h"
#include <iostream>


// Constructor

Grupo::Grupo(char id) : id(id), numPartidos(0) {}


// Destructor

Grupo::~Grupo() {
    for (int i = 0; i < partidos.getTamanio(); i++) {
        Medidor::it();

        Partido* p = partidos.obtener(i);
        if (p) delete p;
    }
}


// Agregar equipo

void Grupo::agregarEquipo(Equipo* equipo) {
    if (equipos.getTamanio() < 4) {
        Medidor::it();
        equipos.insertarAlFinal(equipo);
    }
}


// Organizar partidos (round-robin)

void Grupo::organizarEncuentros(const std::string& fechaInicio) {

    if (equipos.getTamanio() < 4) return;

    // Limpiar partidos anteriores 
    for (int i = 0; i < partidos.getTamanio(); i++) {
        Partido* p = partidos.obtener(i);
        if (p) delete p;
    }
    partidos.limpiar(); 
    numPartidos = 0;

    int emparejamientos[6][2] = {
        {0,1}, {2,3},
        {0,2}, {1,3},
        {0,3}, {1,2}
    };

    for (int p = 0; p < 6; p++) {
        Medidor::it();

        Equipo* e1 = equipos.obtener(emparejamientos[p][0]);
        Equipo* e2 = equipos.obtener(emparejamientos[p][1]);

        if (e1 && e2) {
            Partido* nuevo = new Partido(e1, e2);
            partidos.insertarAlFinal(nuevo);
            numPartidos++;

            Medidor::add(sizeof(Partido));
        }
    }
}


void Grupo::simularFaseGrupal() {
    for (int i = 0; i < partidos.getTamanio(); i++) {
        Medidor::it();

        Partido* p = partidos.obtener(i);
        if (p) p->simular();
    }
}


// Mostrar resultados

void Grupo::mostrarResultados() const {
    std::cout << "\nResultados Grupo " << id << ":\n";

    for (int i = 0; i < partidos.getTamanio(); i++) {
        Partido* p = partidos.obtener(i);
        if (p) p->printResumen();
    }
}


// Tabla de posiciones 

void Grupo::mostrarTabla() {

    std::cout << "\n--- TABLA GRUPO " << id << " ---\n";

    // Ordenamiento tipo burbuja
    for (int i = 0; i < equipos.getTamanio(); i++) {
        for (int j = i + 1; j < equipos.getTamanio(); j++) {

            Medidor::it();

            Equipo* a = equipos.obtener(i);
            Equipo* b = equipos.obtener(j);

            if (!a || !b) continue;

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

    std::cout << "Equipo\tPTS\tDG\tGF\n";

    for (int i = 0; i < equipos.getTamanio(); i++) {
        Equipo* e = equipos.obtener(i);

        if (e) {
            int dg = e->getGolesFavor() - e->getGolesContra();

            std::cout << e->getPais() << "\t"
                      << e->getPuntos() << "\t"
                      << dg << "\t"
                      << e->getGolesFavor() << "\n";
        }
    }

    std::cout << "-----------------------------\n";
}
