#include "Partido.h"
#include <cstdlib>
#include <iostream>

Partido::Partido(Equipo* l, Equipo* v) 
    : local(l), visitante(v), golesLocal(0), golesVisitante(0) {}

void Partido::simular() {
    // Generar resultados aleatorios
    golesLocal = rand() % 5;     
    golesVisitante = rand() % 5; 

    // Actualizar Goles 
    local->setGolesFavor(local->getGolesAFavor() + golesLocal);
    local->setGolesContra(local->getGolesContra() + golesVisitante);

    visitante->setGolesFavor(visitante->getGolesAFavor() + golesVisitante);
    visitante->setGolesContra(visitante->getGolesContra() + golesLocal);

    // Lógica de Puntos, Victorias, Empates y Derrotas 
    if (golesLocal > golesVisitante) {
        // Gana local
        local->setPuntos(local->getPuntosFaseGrupos() + 3);
        local->setVictorias(local->getVictorias() + 1); 
        visitante->setDerrotas(visitante->getDerrotas() + 1);
    } 
    else if (golesLocal < golesVisitante) {
        // Gana visitante
        visitante->setPuntos(visitante->getPuntosFaseGrupos() + 3);
        visitante->setVictorias(visitante->getVictorias() + 1); //
        local->setDerrotas(local->getDerrotas() + 1);
    } 
    else {
        // Empate
        local->setPuntos(local->getPuntosFaseGrupos() + 1);
        visitante->setPuntos(visitante->getPuntosFaseGrupos() + 1);
        local->setEmpates(local->getEmpates() + 1);
        visitante->setEmpates(visitante->getEmpates() + 1);
    }
}
