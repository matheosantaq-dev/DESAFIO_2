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
    Grupo(char id);
    ~Grupo();

    void agregarEquipo(Equipo* equipo);
    void organizarEncuentros(const std::string& fechaInicio);
    void simularFaseGrupal();
    void construirTablaClasificacion();
    void mostrarResultados() const;
    void mostrarTabla() const;
    
   
    char getId() const { return id; }
    int getNumEquipos() const { return equipos.getTamanio(); }
};

#endif
   
