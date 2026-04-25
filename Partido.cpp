#include "Partido.h"
#include <cstdlib>
#include <iostream>

Partido::Partido(Equipo* l, Equipo* v)
    : local(l), visitante(v), golesLocal(0), golesVisitante(0) {}

double Partido::calcularLambda(Equipo* ataque, Equipo* defensa) {
    double GF = ataque->getGolesFavor() + 1;
    double GC = defensa->getGolesContra() + 1;

    double alpha = 0.6;
    double beta = 0.4;
    double mu = 1.35;

    return mu * (alpha * GF + beta * GC) / 2.0;
}

void Partido::simular() {
    //RESET DE JUGADORES (ANTES DEL PARTIDO)
    int iteraciones = 0;
    int titularesLocal[11];
    for (int i = 0; i < 11; i++) {
        iteraciones++;
        titularesLocal[i] = rand() % local->getCantidadJugadores();
    }
    for (int i = 0; i < local->getCantidadJugadores(); i++) {
        iteraciones++;
        Jugador* j = local->getJugador(i);
        if (j != nullptr) j->resetTemp();
    }

    for (int i = 0; i < visitante->getCantidadJugadores(); i++) {
        iteraciones++;
        Jugador* j = visitante->getJugador(i);
        if (j != nullptr) j->resetTemp();
    }
    for (int i = 0; i < 11; i++) {
        iteraciones++;
        int idx = rand() % local->getCantidadJugadores();
        Jugador* j = local->getJugador(idx);
        j->resetTemp();
    }
    for (int i = 0; i < 11; i++) {
        iteraciones++;
        Jugador* j = local->getJugador(i);
        j->consolidarPartido(90);
    }
    // Generar resultados aleatorios
    double lambdaLocal = calcularLambda(local, visitante);
    double lambdaVisitante = calcularLambda(visitante, local);

    // Aproximación simple (puedes mejorar luego)
    golesLocal = static_cast<int>(lambdaLocal) + rand() % 2;
    golesVisitante = static_cast<int>(lambdaVisitante) + rand() % 2;

    int rankingA = local->getRanking();
    int rankingB = visitante->getRanking();

    posesionLocal = (double)rankingB / (rankingA + rankingB);
    posesionVisitante = 1.0 - posesionLocal;

    for (int g = 0; g < golesLocal; g++) {
        iteraciones++;
        int idx = rand() % 11;
        Jugador* j = local->getJugador(idx);
        j->registrarAccion("gol");
    }
    // Actualizar Goles
    local->setGolesFavor(local->getGolesFavor() + golesLocal);
    local->setGolesContra(local->getGolesContra() + golesVisitante);

    visitante->setGolesFavor(visitante->getGolesFavor() + golesVisitante);
    visitante->setGolesContra(visitante->getGolesContra() + golesLocal);
    for (int g = 0; g < golesLocal; g++) {
        iteraciones++;
    }
    // Lógica de Puntos, Victorias, Empates y Derrotas
    if (golesLocal > golesVisitante) {
        // Gana local
        local->setPuntos(local->getPuntos() + 3);
        local->setVictorias(local->getVictorias() + 1);
        visitante->setDerrotas(visitante->getDerrotas() + 1);
    }
    else if (golesLocal < golesVisitante) {
        // Gana visitante
        visitante->setPuntos(visitante->getPuntos() + 3);
        visitante->setVictorias(visitante->getVictorias() + 1); //
        local->setDerrotas(local->getDerrotas() + 1);
    }
    else {
        // Empate
        local->setPuntos(local->getPuntos() + 1);
        visitante->setPuntos(visitante->getPuntos() + 1);
        local->setEmpates(local->getEmpates() + 1);
        visitante->setEmpates(visitante->getEmpates() + 1);
    }
    std::cout << "Iteraciones: " << iteraciones << std::endl;
}
void Partido::printResumen() const {
    std::cout << local->getPais() << " " << golesLocal << " - " << golesVisitante << " " << visitante->getPais() << std::endl;
}
