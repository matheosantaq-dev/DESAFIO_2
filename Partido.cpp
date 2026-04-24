#include "Partido.h"
#include <cstdlib>
#include <iostream>

Partido::Partido(Equipo* l, Equipo* v) 
    : local(l), visitante(v), golesLocal(0), golesVisitante(0) {}

void Partido::simular() {
   
    golesLocal = rand() % 5;      
    golesVisitante = rand() % 5;  

    // Actualizar Goles a Favor y en Contra
    local->setGolesFavor(local->getGolesAFavor() + golesLocal);
    local->setGolesContra(local->getGolesContra() + golesVisitante);

    visitante->setGolesFavor(visitante->getGolesAFavor() + golesVisitante);
    visitante->setGolesContra(visitante->getGolesContra() + golesLocal);

    // Lógica de Puntos, Victorias, Empates y Derrotas
    if (golesLocal > golesVisitante) {
        // Gana local
        local->setPuntos(local->getPuntosFaseGrupos() + 3);
        local->setVictorias(1); 
        visitante->setDerrotas(1);
    } 
    else if (golesLocal < golesVisitante) {
        // Gana visitante
        visitante->setPuntos(visitante->getPuntosFaseGrupos() + 3);
        visitante->setVictorias(1);
        local->setDerrotas(1);
    } 
    else {
        // Empate
        local->setPuntos(local->getPuntosFaseGrupos() + 1);
        visitante->setPuntos(visitante->getPuntosFaseGrupos() + 1);
        local->setEmpates(1);
        visitante->setEmpates(1);
    }
}
