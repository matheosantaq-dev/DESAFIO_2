#include "Partido.h"
#include "Medidor.h"
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

    
    // RESET DE TODOS LOS JUGADORES

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

   
    // SELECCIÓN DE TITULARES

    int titularesLocal[11];
    int titularesVisitante[11];

    for (int i = 0; i < 11; i++) {
        Medidor::it();
        titularesLocal[i] = rand() % local->getCantidadJugadores();
        titularesVisitante[i] = rand() % visitante->getCantidadJugadores();
    }

    
    // GENERAR GOLES (MODELO)
  
    double lambdaLocal = calcularLambda(local, visitante);
    double lambdaVisitante = calcularLambda(visitante, local);

    golesLocal = static_cast<int>(lambdaLocal) + rand() % 2;
    golesVisitante = static_cast<int>(lambdaVisitante) + rand() % 2;

    
    // EVENTOS EN JUGADORES
   

    // Goles local
    for (int g = 0; g < golesLocal; g++) {
        Medidor::it();
        int idx = titularesLocal[rand() % 11];
        Jugador* j = local->getJugador(idx);
        if (j) j->registrarAccion("gol");
    }

    // Goles visitante
    for (int g = 0; g < golesVisitante; g++) {
        Medidor::it();
        int idx = titularesVisitante[rand() % 11];
        Jugador* j = visitante->getJugador(idx);
        if (j) j->registrarAccion("gol");
    }

    // Faltas y tarjetas
    for (int i = 0; i < 22; i++) {
        Medidor::it();

        int idxA = titularesLocal[rand() % 11];
        int idxB = titularesVisitante[rand() % 11];

        if (rand() % 100 < 20) {
            Jugador* j = local->getJugador(idxA);
            if (j) j->registrarAccion("falta");
        }

        if (rand() % 100 < 20) {
            Jugador* j = visitante->getJugador(idxB);
            if (j) j->registrarAccion("falta");
        }

        if (rand() % 100 < 10) {
            Jugador* j = local->getJugador(idxA);
            if (j) j->registrarAccion("amarilla");
        }

        if (rand() % 100 < 10) {
            Jugador* j = visitante->getJugador(idxB);
            if (j) j->registrarAccion("amarilla");
        }
    }

    
    // CONSOLIDAR PARTIDO 
   
    for (int i = 0; i < local->getCantidadJugadores(); i++) {
        Medidor::it();
        Jugador* j = local->getJugador(i);
        if (j) j->consolidarPartido(90);
    }

    for (int i = 0; i < visitante->getCantidadJugadores(); i++) {
        Medidor::it();
        Jugador* j = visitante->getJugador(i);
        if (j) j->consolidarPartido(90);
    }

    
    // ACTUALIZAR EQUIPOS
  
    local->setGolesFavor(local->getGolesFavor() + golesLocal);
    local->setGolesContra(local->getGolesContra() + golesVisitante);

    visitante->setGolesFavor(visitante->getGolesFavor() + golesVisitante);
    visitante->setGolesContra(visitante->getGolesContra() + golesLocal);

    if (golesLocal > golesVisitante) {
        local->setPuntos(local->getPuntos() + 3);
        local->setVictorias(local->getVictorias() + 1);
        visitante->setDerrotas(visitante->getDerrotas() + 1);
    }
    else if (golesLocal < golesVisitante) {
        visitante->setPuntos(visitante->getPuntos() + 3);
        visitante->setVictorias(visitante->getVictorias() + 1);
        local->setDerrotas(local->getDerrotas() + 1);
    }
    else {
        local->setPuntos(local->getPuntos() + 1);
        visitante->setPuntos(visitante->getPuntos() + 1);
        local->setEmpates(local->getEmpates() + 1);
        visitante->setEmpates(visitante->getEmpates() + 1);
    }

    Medidor::it();
}

void Partido::printResumen() const {
    std::cout << local->getPais() << " "
              << golesLocal << " - "
              << golesVisitante << " "
              << visitante->getPais() << std::endl;
}
