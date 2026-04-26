#ifndef PARTIDO_H
#define PARTIDO_H

#include <string>
#include "Equipo.h"

class Partido {
private:
    Equipo* local;
    Equipo* visitante;

    int golesLocal;
    int golesVisitante;

    double posesionLocal;
    double posesionVisitante;

    bool huboProrroga;

    std::string fecha;
    std::string sede;

    // Estadísticas tipo FIFA
    int tirosLocal;
    int tirosVisitante;
    int tirosArcoLocal;
    int tirosArcoVisitante;
    int faltasLocal;
    int faltasVisitante;
    int amarillasLocal;
    int amarillasVisitante;

public:
    Partido(Equipo* l, Equipo* v, const std::string& fecha, const std::string& sede);
    ~Partido();

    // Simulación
    void simular(bool eliminacionDirecta);
    void printResumen() const;

    // Cálculos
    double calcularLambda(Equipo* ataque, Equipo* defensa);
    void seleccionarTitulares(int titulares[], Equipo* equipo);
    void simularEventosJugadores(int titulares[], Equipo* equipo, int goles);
    void generarEstadisticasRealistas();
    void resolverEmpate();

    // Getters
    Equipo* getLocal() const;
    Equipo* getVisitante() const;
    int getGolesLocal() const;
    int getGolesVisitante() const;
    bool getHuboProrroga() const;
};

#endif
