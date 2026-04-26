#ifndef EQUIPO_H
#define EQUIPO_H

#include <string>
#include <iostream>
#include "Jugador.h"
#include "ListaDinamica.h"

class Equipo {
private:
    // Identificación
    std::string pais;
    std::string confederacion;
    std::string directorTecnico;
    int rankingFIFA;

    // Estadísticas históricas
    int golesFavor;
    int golesContra;
    int puntos;
    int victorias;
    int empates;
    int derrotas;
    int amarillas;
    int rojas;
    int faltas;

    // Plantilla
    ListaDinamica<Jugador*> plantilla;

public:
    // Constructores
    Equipo(std::string nombre = "", int ranking = 0);
    Equipo(const Equipo& otro);

    // Destructor
    ~Equipo();

    // Setters
    void setGolesFavor(int g);
    void setGolesContra(int g);
    void setPuntos(int p);
    void setVictorias(int v);
    void setEmpates(int e);
    void setDerrotas(int d);
    void setConfederacion(const std::string& conf);
    void setDirectorTecnico(const std::string& dt);

    // Getters
    std::string getPais() const;
    std::string getConfederacion() const;
    std::string getDirectorTecnico() const;
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

    // Simulación
    double promGF() const;
    double promGC() const;
    void resetStats();
    void actualizarResultado(int gf, int gc);

    // Sobrecarga
    bool operator<(const Equipo& otro) const;
    bool operator>(const Equipo& otro) const;

    // Función amiga
    friend std::ostream& operator<<(std::ostream& os, const Equipo& equipo);
};

#endif
