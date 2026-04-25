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
    void setVictorias(int v);
    void setEmpates(int e);
    void setDerrotas(int d);

    // Getters
    std::string getPais() const;
    int getRanking() const;
    int getPuntos() const;
    int getGolesFavor() const;
    int getGolesContra() const;
    int getVictorias() const;
    int getEmpates() const;
    int getDerrotas() const;

    /*se agregan estos setters y getters por que se necesita modificar y consultar estadisticas*/
    Jugador* getJugador(int i);
    int getCantidadJugadores() const;
    Jugador* getJugador(int index) const;
    // Metodo para agregar jugadores
    void agregarJugador(Jugador* j);
};

#endif

#endif
