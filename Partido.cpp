#include "Partido.h"
#include "Medidor.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>

// Constructor
Partido::Partido(Equipo* l, Equipo* v, const std::string& fecha, const std::string& sede)
    : local(l), visitante(v),
    golesLocal(0), golesVisitante(0),
    posesionLocal(0.0), posesionVisitante(0.0),
    huboProrroga(false),
    fecha(fecha), sede(sede),
    tirosLocal(0), tirosVisitante(0),
    tirosArcoLocal(0), tirosArcoVisitante(0),
    faltasLocal(0), faltasVisitante(0),
    amarillasLocal(0), amarillasVisitante(0)
{
    Medidor::add(sizeof(Partido));
}

// Destructor
Partido::~Partido() {
    Medidor::sub(sizeof(Partido));
}

// Lambda (modelo del documento)
double Partido::calcularLambda(Equipo* ataque, Equipo* defensa) {
    if (!ataque || !defensa) return 1.0;

    double GF = ataque->promGF();
    double GC = defensa->promGC();

    return 1.35 * (0.6 * GF + 0.4 * GC);
}

// Selección de jugadores
void Partido::seleccionarTitulares(int titulares[], Equipo* equipo) {
    if (!equipo) return;

    int total = equipo->getCantidadJugadores();
    if (total == 0) return;

    for (int i = 0; i < 11; i++) {
        titulares[i] = rand() % total;
    }
}

// Eventos jugadores
void Partido::simularEventosJugadores(int titulares[], Equipo* equipo, int goles) {
    if (!equipo) return;

    // Goles
    for (int g = 0; g < goles; g++) {
        int idx = titulares[rand() % 11];
        Jugador* j = equipo->getJugador(idx);
        if (j) j->registrarAccion("gol");
    }

    // Faltas y tarjetas
    for (int i = 0; i < 11; i++) {
        Jugador* j = equipo->getJugador(titulares[i]);
        if (!j) continue;

        if (rand() % 100 < 20) j->registrarAccion("falta");
        if (rand() % 100 < 10) j->registrarAccion("amarilla");
    }
}

// Estadísticas realistas
void Partido::generarEstadisticasRealistas() {

    tirosLocal = golesLocal * 3 + rand() % 5;
    tirosVisitante = golesVisitante * 3 + rand() % 5;

    tirosArcoLocal = tirosLocal * (40 + rand() % 30) / 100;
    tirosArcoVisitante = tirosVisitante * (40 + rand() % 30) / 100;

    faltasLocal = 5 + rand() % 10;
    faltasVisitante = 5 + rand() % 10;

    amarillasLocal = rand() % 4;
    amarillasVisitante = rand() % 4;

    int base = 50 + (golesLocal - golesVisitante) * 5 + (rand() % 11 - 5);

    if (base < 30) base = 30;
    if (base > 70) base = 70;

    posesionLocal = base;
    posesionVisitante = 100 - base;
}

// Empate en eliminación
void Partido::resolverEmpate() {
    huboProrroga = true;

    if (rand() % 2 == 0) golesLocal++;
    else golesVisitante++;
}

// Simulación principal
void Partido::simular(bool eliminacionDirecta) {

    if (!local || !visitante) return;

    // Reset jugadores
    for (int i = 0; i < local->getCantidadJugadores(); i++) {
        Jugador* j = local->getJugador(i);
        if (j) j->resetTemp();
    }

    for (int i = 0; i < visitante->getCantidadJugadores(); i++) {
        Jugador* j = visitante->getJugador(i);
        if (j) j->resetTemp();
    }

    // Titulares
    int titularesLocal[11] = {0};
    int titularesVisitante[11] = {0};

    seleccionarTitulares(titularesLocal, local);
    seleccionarTitulares(titularesVisitante, visitante);

    // Lambda
    double lambdaLocal = calcularLambda(local, visitante);
    double lambdaVisitante = calcularLambda(visitante, local);

    // GOLES
    golesLocal = std::max(0, (int)(lambdaLocal + (rand() % 3 - 1)));
    golesVisitante = std::max(0, (int)(lambdaVisitante + (rand() % 3 - 1)));

    if (golesLocal > 4) golesLocal = 4;
    if (golesVisitante > 4) golesVisitante = 4;

    // Eventos
    simularEventosJugadores(titularesLocal, local, golesLocal);
    simularEventosJugadores(titularesVisitante, visitante, golesVisitante);

    // Stats tipo FIFA
    generarEstadisticasRealistas();

    // Eliminación
    if (eliminacionDirecta && golesLocal == golesVisitante) {
        resolverEmpate();
    }

    int minutos = huboProrroga ? 120 : 90;

    // Consolidar jugadores
    for (int i = 0; i < local->getCantidadJugadores(); i++) {
        Jugador* j = local->getJugador(i);
        if (j) j->consolidarPartido(minutos);
    }

    for (int i = 0; i < visitante->getCantidadJugadores(); i++) {
        Jugador* j = visitante->getJugador(i);
        if (j) j->consolidarPartido(minutos);
    }

    // Equipos
    local->actualizarResultado(golesLocal, golesVisitante);
    visitante->actualizarResultado(golesVisitante, golesLocal);
}

// Resumen
void Partido::printResumen() const {
    if (!local || !visitante) return;

    std::cout << fecha << " | "
              << local->getPais() << " "
              << golesLocal << " - "
              << golesVisitante << " "
              << visitante->getPais();

    if (huboProrroga) std::cout << " (Prorroga)";

    std::cout << "\n";

    std::cout << "Posesion: "
              << posesionLocal << "% - "
              << posesionVisitante << "%\n";

    std::cout << "Tiros: "
              << tirosLocal << " - "
              << tirosVisitante << "\n";

    std::cout << "Al arco: "
              << tirosArcoLocal << " - "
              << tirosArcoVisitante << "\n";

    std::cout << "Faltas: "
              << faltasLocal << " - "
              << faltasVisitante << "\n";

    std::cout << "Amarillas: "
              << amarillasLocal << " - "
              << amarillasVisitante << "\n";

    std::cout << "-----------------------------------\n";
}

// Getters
Equipo* Partido::getLocal() const { return local; }
Equipo* Partido::getVisitante() const { return visitante; }
int Partido::getGolesLocal() const { return golesLocal; }
int Partido::getGolesVisitante() const { return golesVisitante; }
bool Partido::getHuboProrroga() const { return huboProrroga; }
