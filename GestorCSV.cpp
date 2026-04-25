#include "GestorCSV.h"
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

    std::getline(archivo, linea);
    std::getline(archivo, linea);

    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string dato;


        std::string ranking, pais, tecnico, federacion, conf, gf, gc, pg, pe, pp;

        std::getline(ss, ranking, ';');
        std::getline(ss, pais, ';');
        std::getline(ss, tecnico, ';');

        if (!pais.empty()) {
            // CREACIÓN EN MEMORIA DINÁMICA
            int rankingInt = std::stoi(ranking);
            Equipo* nuevo = new Equipo(pais, rankingInt);

            // Crear 26 jugadores
            for (int i = 1; i <= 26; i++) {
                Jugador* j = new Jugador(
                    "nombre" + std::to_string(i),
                    "apellido" + std::to_string(i),
                    i
                    );
                nuevo->agregarJugador(j);
            }
            equiposCargados.insertarAlFinal(nuevo);
        }
    }

    archivo.close();
    return equiposCargados;

}
