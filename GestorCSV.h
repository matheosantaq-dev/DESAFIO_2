#ifndef GESTORCSV_H
#define GESTORCSV_H

#include <string>
#include <fstream>
#include "ListaDinamica.h"
#include "Equipo.h"

class GestorCSV {
private:
    std::string path;

public:
    // Constructor
    GestorCSV(std::string ruta);

  
    // retorna punteros 
    ListaDinamica<Equipo*> cargarEquipos();
};

#endif
