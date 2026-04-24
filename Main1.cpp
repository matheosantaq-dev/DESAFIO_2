#include <iostream>
#include "Jugador.h"
#include "Equipo.h"
#include "Partido.h"
#include "Grupo.h"

int main() {
    // Uso de punteros para gestión de memoria dinámica, según requerimientos del desafío.
    Equipo* e1 = new Equipo("Colombia");
    Equipo* e2 = new Equipo("Argentina");

    // Prueba de simulación del partido.
    Partido* p = new Partido(e1, e2);
    p->simular();

    // Liberar memoria asignada dinámicamente para evitar memory leaks.
    delete p;
    delete e1;
    delete e2;

    std::cout << "\nSistema funcional." << std::endl;
    return 0;
}
