#ifndef GESTORCSV_H
#define GESTORCSV_H

#include <string>
#include <fstream>
#include "ListaDinamica.h"
#include "Equipo.h"

class GestorCSV {
private:
    std::string path;
    std::ifstream archivo;

public:
    // Constructor
    GestorCSV(std::string ruta = "selecciones_clasificadas_mundial.csv");

    // Destructor
    ~GestorCSV();

    // Cargar equipos desde CSV
    ListaDinamica<Equipo*> cargarEquipos();
};

#endif
