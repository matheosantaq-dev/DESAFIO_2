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
        if (p) {
            delete p;
        }
    }
}

// Agregar equipo con restricción de confederación
bool Grupo::agregarEquipo(Equipo* equipo) {
    if (!equipo || equipos.getTamanio() >= 4) {
        return false;
    }

    int mismaConf = 0;

    for (int i = 0; i < equipos.getTamanio(); i++) {
        Medidor::it();

        Equipo* actual = equipos.obtener(i);

        if (actual &&
            actual->getConfederacion() == equipo->getConfederacion()) {
            mismaConf++;
        }
    }

    // Restricción:
    // UEFA máximo 2
    // otras máximo 1
    if (equipo->getConfederacion() == "UEFA") {
        if (mismaConf >= 2) return false;
    }
    else {
        if (mismaConf >= 1) return false;
    }

    equipos.insertarAlFinal(equipo);
    return true;
}

// Organizar encuentros
void Grupo::organizarEncuentros(const std::string& fechaInicio) {
    if (equipos.getTamanio() < 4) {
        return;
    }

    // Limpiar partidos previos
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

    for (int i = 0; i < 6; i++) {
        Medidor::it();

        Equipo* e1 = equipos.obtener(emparejamientos[i][0]);
        Equipo* e2 = equipos.obtener(emparejamientos[i][1]);

        if (e1 && e2) {
            Partido* nuevo = new Partido(
                e1,
                e2,
                fechaInicio,
                "nombreSede"
            );

            partidos.insertarAlFinal(nuevo);
            numPartidos++;
        }
    }
}

// Simular fase grupal
void Grupo::simularFaseGrupal() {
    for (int i = 0; i < partidos.getTamanio(); i++) {
        Medidor::it();

        Partido* p = partidos.obtener(i);
        if (p) {
            p->simular();
        }
    }
}

// Mostrar resultados
void Grupo::mostrarResultados() const {
    std::cout << "\nResultados Grupo " << id << ":\n";

    for (int i = 0; i < partidos.getTamanio(); i++) {
        Partido* p = partidos.obtener(i);

        if (p) {
            p->printResumen();
        }
    }
}

// Ordenar tabla
void Grupo::ordenarTabla() {
    for (int i = 0; i < equipos.getTamanio(); i++) {
        for (int j = i + 1; j < equipos.getTamanio(); j++) {
            Medidor::it();

            Equipo* a = equipos.obtener(i);
            Equipo* b = equipos.obtener(j);

            if (!a || !b) continue;

            int dgA = a->getGolesFavor() - a->getGolesContra();
            int dgB = b->getGolesFavor() - b->getGolesContra();

            bool cambiar = false;

            if (b->getPuntos() > a->getPuntos()) {
                cambiar = true;
            }
            else if (b->getPuntos() == a->getPuntos() && dgB > dgA) {
                cambiar = true;
            }
            else if (b->getPuntos() == a->getPuntos() &&
                     dgB == dgA &&
                     b->getGolesFavor() > a->getGolesFavor()) {
                cambiar = true;
            }

            if (cambiar) {
                equipos.intercambiar(i, j);
            }
        }
    }
}

// Mostrar tabla
void Grupo::mostrarTabla() {
    ordenarTabla();

    std::cout << "\n--- TABLA GRUPO " << id << " ---\n";
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

// Getters
char Grupo::getId() const {
    return id;
}

int Grupo::getNumEquipos() const {
    return equipos.getTamanio();
}

int Grupo::getNumPartidos() const {
    return numPartidos;
}

Equipo* Grupo::getEquipo(int index) {
    return equipos.obtener(index);
}
