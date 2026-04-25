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
    GestorCSV(std::string ruta);

    // Lee el archivo y retorna una lista de punteros a Equipo

    ListaDinamica<Equipo*> cargarEquipos();

    void cerrarArchivo();
};

#endif
