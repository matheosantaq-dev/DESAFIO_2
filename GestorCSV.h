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
    GestorCSV(std::string ruta = "C:/Users/PC/Documents/untitled13/build/Desktop_Qt_6_10_2_MinGW_64_bit-Debug/selecciones_clasificadas_mundial.csv");

    // Destructor
    ~GestorCSV();

    // Cargar equipos
    ListaDinamica<Equipo*> cargarEquipos();
};

#endif
