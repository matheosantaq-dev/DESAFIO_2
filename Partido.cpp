#include "Partido.h"
#include "Medidor.h"
#include <cstdlib>
#include <iostream>

// Constructor
Partido::Partido(
    Equipo* l,
    Equipo* v,
    const std::string& fecha,
    const std::string& sede
)
    : local(l),
      visitante(v),
      golesLocal(0),
      golesVisitante(0),
      posesionLocal(0.0),
      posesionVisitante(0.0),
      huboProrroga(false),
      fecha(fecha),
      sede(sede),
      arbitro1("codArbitro1"),
      arbitro2("codArbitro2"),
      arbitro3("codArbitro3")
{
    Medidor::add(sizeof(Partido));
}

// Destructor
Partido::~Partido() {
    Medidor::sub(sizeof(Partido));
}

// Modelo de goles esperados
double Partido::calcularLambda(Equipo* ataque, Equipo* defensa) {
    if (!ataque || !defensa) return 1.0;

    double GF = ataque->promGF();
    double GC = defensa->promGC();

    double alpha = 0.6;
    double beta = 0.4;
    double mu = 1.35;

    return mu * (alpha * GF + beta * GC);
}

// Seleccionar 11 titulares seguros
void Partido::seleccionarTitulares(int titulares[], Equipo* equipo) {
    if (!equipo) return;

    int total = equipo->getCantidadJugadores();
    if (total == 0) return;

    for (int i = 0; i < 11; i++) {
        Medidor::it();
        titulares[i] = rand() % total;
    }
}

// Simular eventos por jugador
void Partido::simularEventosJugadores(int titulares[], Equipo* equipo, int goles) {
    if (!equipo) return;

    // Goles
    for (int g = 0; g < goles; g++) {
        Medidor::it();

        int idx = titulares[rand() % 11];
        Jugador* jugador = equipo->getJugador(idx);

        if (jugador) {
            jugador->registrarAccion("gol");
        }
    }

    // Faltas y tarjetas
    for (int i = 0; i < 11; i++) {
        Medidor::it();

        Jugador* jugador = equipo->getJugador(titulares[i]);
        if (!jugador) continue;

        if (rand() % 100 < 15) jugador->registrarAccion("falta");
        if (rand() % 100 < 5)  jugador->registrarAccion("falta");

        if (rand() % 100 < 8)  jugador->registrarAccion("amarilla");
        if (rand() % 100 < 3)  jugador->registrarAccion("amarilla");
    }
}

// Resolver empate en eliminación directa
void Partido::resolverEmpate() {
    huboProrroga = true;

    if (!local || !visitante) return;

    int rankingLocal = local->getRanking();
    int rankingVisitante = visitante->getRanking();

    int probLocal = rankingVisitante;
    int probVisitante = rankingLocal;

    int total = probLocal + probVisitante;
    if (total <= 0) total = 1;

    int r = rand() % total;

    if (r < probLocal) {
        golesLocal++;
    } else {
        golesVisitante++;
    }
}

// Simulación completa
void Partido::simular(bool eliminacionDirecta) {
    if (!local || !visitante) return;

    // Reset jugadores
    for (int i = 0; i < local->getCantidadJugadores(); i++) {
        Medidor::it();
        Jugador* j = local->getJugador(i);
        if (j) j->resetTemp();
    }

    for (int i = 0; i < visitante->getCantidadJugadores(); i++) {
        Medidor::it();
        Jugador* j = visitante->getJugador(i);
        if (j) j->resetTemp();
    }

    // Titulares
    int titularesLocal[11] = {0};
    int titularesVisitante[11] = {0};

    seleccionarTitulares(titularesLocal, local);
    seleccionarTitulares(titularesVisitante, visitante);

    // Goles base
    double lambdaLocal = calcularLambda(local, visitante);
    double lambdaVisitante = calcularLambda(visitante, local);

    golesLocal = static_cast<int>(lambdaLocal) + rand() % 3;
    golesVisitante = static_cast<int>(lambdaVisitante) + rand() % 3;

    if (golesLocal < 0) golesLocal = 0;
    if (golesVisitante < 0) golesVisitante = 0;

    // Posesión
    int rA = local->getRanking();
    int rB = visitante->getRanking();

    if (rA + rB > 0) {
        posesionLocal = static_cast<double>(rB) / (rA + rB);
        posesionVisitante = 1.0 - posesionLocal;
    } else {
        posesionLocal = 0.5;
        posesionVisitante = 0.5;
    }

    // Eventos
    simularEventosJugadores(titularesLocal, local, golesLocal);
    simularEventosJugadores(titularesVisitante, visitante, golesVisitante);

    // Empate en eliminación
    if (eliminacionDirecta && golesLocal == golesVisitante) {
        resolverEmpate();
    }

    // Consolidar jugadores
    int minutos = huboProrroga ? 120 : 90;

    for (int i = 0; i < local->getCantidadJugadores(); i++) {
        Medidor::it();
        Jugador* j = local->getJugador(i);
        if (j) j->consolidarPartido(minutos);
    }

    for (int i = 0; i < visitante->getCantidadJugadores(); i++) {
        Medidor::it();
        Jugador* j = visitante->getJugador(i);
        if (j) j->consolidarPartido(minutos);
    }

    // Actualizar equipos
    local->actualizarResultado(golesLocal, golesVisitante);
    visitante->actualizarResultado(golesVisitante, golesLocal);

    Medidor::it();
}

// Mostrar resultado
void Partido::printResumen() const {
    if (!local || !visitante) return;

    std::cout << fecha << " | "
              << local->getPais() << " "
              << golesLocal << " - "
              << golesVisitante << " "
              << visitante->getPais();

    if (huboProrroga) {
        std::cout << " (Prórroga)";
    }

    std::cout << "\n";
}

// Getters
Equipo* Partido::getLocal() const { return local; }
Equipo* Partido::getVisitante() const { return visitante; }
int Partido::getGolesLocal() const { return golesLocal; }
int Partido::getGolesVisitante() const { return golesVisitante; }
bool Partido::getHuboProrroga() const { return huboProrroga; }
