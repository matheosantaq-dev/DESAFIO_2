#include "Grupo.h"
#include "Medidor.h"
#include <iostream>
#include <iomanip>

// Constructor
Grupo::Grupo(char id) : id(id), numPartidos(0) {}

// Destructor
Grupo::~Grupo() {
    for (int i = 0; i < partidos.getTamanio(); i++) {
        Partido* p = partidos.obtener(i);
        if (p) delete p;
    }
}

// Agregar equipo
bool Grupo::agregarEquipo(Equipo* equipo) {
    if (!equipo || equipos.getTamanio() >= 4) return false;


    equipos.insertarAlFinal(equipo);
    return true;
}

// Organizar partidos
void Grupo::organizarEncuentros(const std::string& fechaInicio) {

    if (equipos.getTamanio() < 4) {
        std::cout << "Grupo " << id << " incompleto\n";
        return;
    }

    partidos.limpiar();
    numPartidos = 0;

    int emp[6][2] = {
        {0,1}, {2,3},
        {0,2}, {1,3},
        {0,3}, {1,2}
    };

    for (int i = 0; i < 6; i++) {

        Equipo* a = equipos.obtener(emp[i][0]);
        Equipo* b = equipos.obtener(emp[i][1]);

        if (!a || !b) continue;

        Partido* p = new Partido(a, b, fechaInicio, "Estadio");
        partidos.insertarAlFinal(p);
        numPartidos++;
    }
}

// Simular
void Grupo::simularFaseGrupal() {
    for (int i = 0; i < partidos.getTamanio(); i++) {
        Partido* p = partidos.obtener(i);
        if (p) p->simular(false);
    }
}

// Resultados
void Grupo::mostrarResultados() const {
    std::cout << "\nResultados Grupo " << id << ":\n";
    for (int i = 0; i < partidos.getTamanio(); i++) {
        Partido* p = partidos.obtener(i);
        if (p) p->printResumen();
    }
}

// Ordenar tabla
void Grupo::ordenarTabla() {
    for (int i = 0; i < equipos.getTamanio(); i++) {
        for (int j = i + 1; j < equipos.getTamanio(); j++) {

            Equipo* a = equipos.obtener(i);
            Equipo* b = equipos.obtener(j);

            if (!a || !b) continue;

            int dgA = a->getGolesFavor() - a->getGolesContra();
            int dgB = b->getGolesFavor() - b->getGolesContra();

            bool cambiar = false;

            if (b->getPuntos() > a->getPuntos()) cambiar = true;
            else if (b->getPuntos() == a->getPuntos() && dgB > dgA) cambiar = true;
            else if (b->getPuntos() == a->getPuntos() && dgB == dgA &&
                     b->getGolesFavor() > a->getGolesFavor()) cambiar = true;

            if (cambiar) equipos.intercambiar(i, j);
        }
    }
}

void Grupo::mostrarTabla() {
    ordenarTabla();

    std::cout << "\n--- TABLA GRUPO " << id << " ---\n";

    std::cout << std::left << std::setw(28) << "Equipo"
              << std::setw(6) << "PTS"
              << std::setw(6) << "DG"
              << std::setw(6) << "GF" << "\n";

    for (int i = 0; i < equipos.getTamanio(); i++) {
        Equipo* e = equipos.obtener(i);
        if (e) {
            std::cout << std::left << std::setw(28) << e->getPais()
            << std::setw(6) << e->getPuntos()
            << std::setw(6) << (e->getGolesFavor() - e->getGolesContra())
            << std::setw(6) << e->getGolesFavor()
            << "\n";
        }
    }

    std::cout << "-------------------------------------------\n";
}

// Getters
char Grupo::getId() const { return id; }
int Grupo::getNumEquipos() const { return equipos.getTamanio(); }
int Grupo::getNumPartidos() const { return numPartidos; }
Equipo* Grupo::getEquipo(int index) { return equipos.obtener(index); }

// Clasificados
Equipo** Grupo::getClasificados() {
    ordenarTabla();
    Equipo** top2 = new Equipo*[2];
    top2[0] = equipos.obtener(0);
    top2[1] = equipos.obtener(1);
    return top2;
}
