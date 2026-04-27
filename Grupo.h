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
    // Constructor
    Grupo(char id);

    // Destructor
    ~Grupo();

    // Gestión
    bool agregarEquipo(Equipo* equipo);

    // Organización
    void organizarEncuentros(const std::string& fechaInicio);
    void simularFaseGrupal();

    // Resultados
    void mostrarResultados() const;
    void mostrarTabla();

    // Getters
    char getId() const;
    int getNumEquipos() const;
    int getNumPartidos() const;

    Equipo* getEquipo(int index);

    // Clasificación
    void ordenarTabla();
    Equipo** getClasificados();
};

#endif
