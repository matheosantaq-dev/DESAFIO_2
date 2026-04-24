#include "Equipo.h"

Equipo::Equipo(std::string nombre) : pais(nombre), golesFavor(0), puntos(0) {
    // Inicializar la estructura de datos si es necesario.
}

void Equipo::agregarJugador(Jugador* j) {
    // Utilizar el método de inserción de la ListaDinamica aquí.
    // plantilla.insertarAlFinal(j);
}

void Equipo::setGoles(int g) {
    golesFavor = g;
}

std::string Equipo::getPais() const {
    return pais;
}
