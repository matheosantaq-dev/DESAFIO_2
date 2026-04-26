#ifndef MENU_H
#define MENU_H

#include "GestorCSV.h"
#include "Torneo.h"

class Menu {
private:
    GestorCSV gestor;
    ListaDinamica<Equipo*> equipos;
    Torneo torneo;

    // Auxiliares
    void mostrarBanner() const;
    void mostrarOpciones() const;

    void cargarDatos();
    void organizarTorneo();
    void simularMundial();
    void mostrarMetricas();
    void liberarMemoria();

public:
    // Constructor
    Menu();

    // Destructor
    ~Menu();

    // Ejecución principal
    void iniciar();
};

#endif
