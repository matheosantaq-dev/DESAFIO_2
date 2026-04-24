#ifndef EQUIPO_H
#define EQUIPO_H

#include <string>
#include "Jugador.h"
#include "ListaDinamica.h" // Incluir la clase ListaDinamica para su uso

class Equipo {
private:
    std::string pais;
    int golesFavor;
    int puntos;
    // Lista requerida por el UML. Implementar como template de tipo Jugador*.
    ListaDinamica<Jugador*> plantilla;

public:
    Equipo(std::string nombre);

    // Implementar métodos de acceso (getters/setters) para los atributos.
    void setGoles(int g);
    std::string getPais() const;

    // Método para agregar jugadores a la estructura dinámica.
    void agregarJugador(Jugador* j);
};

#endif
