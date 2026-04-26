#ifndef PARTIDO_H
#define PARTIDO_H

#include "Equipo.h"
#include <string>

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

    std::string arbitro1;
    std::string arbitro2;
    std::string arbitro3;

    // Modelo
    double calcularLambda(Equipo* ataque, Equipo* defensa);

    // Auxiliares
    void seleccionarTitulares(int titulares[], Equipo* equipo);
    void simularEventosJugadores(int titulares[], Equipo* equipo, int goles);
    void resolverEmpate();

public:
    // Constructor
    Partido(
        Equipo* l,
        Equipo* v,
        const std::string& fecha = "20/06/2026",
        const std::string& sede = "nombreSede"
    );

    // Destructor
    ~Partido();

    // Simulación
    void simular(bool eliminacionDirecta = false);

    // Mostrar
    void printResumen() const;

    // Getters
    Equipo* getLocal() const;
    Equipo* getVisitante() const;
    int getGolesLocal() const;
    int getGolesVisitante() const;
    bool getHuboProrroga() const;
};

#endif
