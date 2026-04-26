#include "GestorCSV.h"
#include "Medidor.h"
#include <sstream>
#include <iostream>

GestorCSV::GestorCSV(std::string ruta) : path(ruta) {}

ListaDinamica<Equipo*> GestorCSV::cargarEquipos() {

    ListaDinamica<Equipo*> equiposCargados;
    archivo.open(path);

    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << path << std::endl;
        return equiposCargados;
    }

    std::string linea;

    // Saltar encabezados
    std::getline(archivo, linea);
    std::getline(archivo, linea);

    while (std::getline(archivo, linea)) {

        Medidor::it();

        std::stringstream ss(linea);
        std::string ranking, pais, tecnico, federacion, conf;
        std::string gf, gc, pg, pe, pp;

        std::getline(ss, ranking, ';');
        std::getline(ss, pais, ';');
        std::getline(ss, tecnico, ';');
        std::getline(ss, federacion, ';');
        std::getline(ss, conf, ';');
        std::getline(ss, gf, ';');
        std::getline(ss, gc, ';');
        std::getline(ss, pg, ';');
        std::getline(ss, pe, ';');
        std::getline(ss, pp, ';');

        // Validación básica
        if (pais.empty() || ranking.empty()) continue;

        try {
            int rankingInt = std::stoi(ranking);

            // Crear equipo
            Equipo* nuevo = new Equipo(pais, rankingInt);
            Medidor::add(sizeof(Equipo));

            // Asignar estadísticas iniciales (
            if (!gf.empty()) nuevo->setGolesFavor(std::stoi(gf));
            if (!gc.empty()) nuevo->setGolesContra(std::stoi(gc));
            if (!pg.empty()) nuevo->setVictorias(std::stoi(pg));
            if (!pe.empty()) nuevo->setEmpates(std::stoi(pe));
            if (!pp.empty()) nuevo->setDerrotas(std::stoi(pp));

            // Crear jugadores (26 por equipo)
            for (int i = 1; i <= 26; i++) {
                Medidor::it();

                Jugador* j = new Jugador(
                    "Jugador" + std::to_string(i),
                    pais,
                    i
                );

                Medidor::add(sizeof(Jugador));
                nuevo->agregarJugador(j);
            }

            equiposCargados.insertarAlFinal(nuevo);

        } catch (...) {
            std::cerr << "Error procesando linea: " << linea << std::endl;
        }
    }

    archivo.close();
    return equiposCargados;
}
