#ifndef EQUIPO_H
#define EQUIPO_H

#include <string>
#include "Jugador.h"
#include "ListaDinamica.h"

class Equipo {
private:
    // Identificación
    std::string pais;
    int rankingFIFA;

    // Estadísticas
    int golesFavor;
    int golesContra;
    int puntos;
    int victorias;
    int empates;
    int derrotas;

    // Jugadores
    ListaDinamica<Jugador*> plantilla;

public:
    // Constructor y destructor
    Equipo(std::string nombre, int ranking);
    ~Equipo();

    // Setters
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

    // Jugadores
    Jugador* getJugador(int i);
    int getCantidadJugadores() const;
    void agregarJugador(Jugador* j);

    // Lógica para simulación
    double promGF() const;
    double promGC() const;
    void resetStats();
};

#endif
