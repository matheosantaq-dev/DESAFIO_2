#ifndef GRUPO_H
#define GRUPO_H

#include "ListaDinamica.h"
#include "Equipo.h"
#include "Partido.h"
#include <string>

class Grupo {
private:
    char id;
    int numPartidos;

    ListaDinamica<Equipo*> equipos;
    ListaDinamica<Partido*> partidos;

public:
    // Constructor y destructor
    Grupo(char id);
    ~Grupo();

    // Gestión de equipos
    void agregarEquipo(Equipo* equipo);

    // Organización y simulación
    void organizarEncuentros(const std::string& fechaInicio);
    void simularFaseGrupal();

    // Resultados
    void mostrarResultados() const;
    void mostrarTabla();

    // Getters
    char getId() const;
    int getNumEquipos() const;
};

#endif
