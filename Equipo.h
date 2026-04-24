#ifndef EQUIPO_H
#define EQUIPO_H

#include <string>
#include "Jugador.h"
#include "ListaDinamica.h"

class Equipo {
private:
    // Atributos de identificación
    std::string pais;
    int rankingFIFA;

    // Estadisticas requeridas por el UML
    int golesFavor;
    int golesContra;
    int puntos;
    int victorias;
    int empates;
    int derrotas;

    // Estructura de datos 
    ListaDinamica<Jugador*> plantilla;

public:
    // Constructor 
    Equipo(std::string nombre, int ranking);

    // Métodos de acceso (Getters y Setters)
    // Estos van en la sección public para que otras clases puedan consultarlos
    void setGolesFavor(int g);
    void setGolesContra(int g);
    void setPuntos(int p);
    
    // Getters
    std::string getPais() const;
    int getRanking() const;
    int getPuntos() const;
    
    // Metodo para agregar jugadores
    void agregarJugador(Jugador* j); 
};

#endif
