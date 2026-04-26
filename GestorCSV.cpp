#include "GestorCSV.h"
#include "Medidor.h"

#include <sstream>
#include <iostream>
#include <cctype>

// Constructor
GestorCSV::GestorCSV(std::string ruta)
    : path(ruta) {
}

// Destructor
GestorCSV::~GestorCSV() {
    if (archivo.is_open()) archivo.close();
}


ListaDinamica<Equipo*> GestorCSV::cargarEquipos() {

    ListaDinamica<Equipo*> equipos;

    std::cout << "Intentando abrir: " << path << std::endl;

    archivo.open(path);

    if (!archivo.is_open()) {
        std::cerr << " ERROR: no se pudo abrir el CSV\n";
        return equipos;
    }

    std::string linea;

    std::getline(archivo, linea);
    std::getline(archivo, linea);

    while (std::getline(archivo, linea)) {

        if (linea.empty()) continue;

        std::stringstream ss(linea);

        std::string ranking, pais, tecnico, fed;
        std::string conf, gf, gc, pg, pe, pp;

        std::getline(ss, ranking, ';');
        std::getline(ss, pais, ';');
        std::getline(ss, tecnico, ';');
        std::getline(ss, fed, ';');
        std::getline(ss, conf, ';');
        std::getline(ss, gf, ';');
        std::getline(ss, gc, ';');
        std::getline(ss, pg, ';');
        std::getline(ss, pe, ';');
        std::getline(ss, pp, ';');

        if (ranking.empty() || pais.empty() || conf.empty())
            continue;

        bool valido = true;
        for (char c : ranking) {
            if (!isdigit(c)) {
                valido = false;
                break;
            }
        }
        if (!valido) continue;

        try {
            int rank = std::stoi(ranking);

            Equipo* e = new Equipo(pais, rank);

            e->setConfederacion(conf);
            e->setDirectorTecnico(tecnico);

            if (!gf.empty()) e->setGolesFavor(std::stoi(gf));
            if (!gc.empty()) e->setGolesContra(std::stoi(gc));
            if (!pg.empty()) e->setVictorias(std::stoi(pg));
            if (!pe.empty()) e->setEmpates(std::stoi(pe));
            if (!pp.empty()) e->setDerrotas(std::stoi(pp));

            e->setPuntos(e->getVictorias() * 3 + e->getEmpates());

            for (int i = 1; i <= 26; i++) {
                Jugador* j = new Jugador(
                    "Jugador" + std::to_string(i),
                    "Apellido" + std::to_string(i),
                    i
                    );
                e->agregarJugador(j);
            }

            equipos.insertarAlFinal(e);

        } catch (...) {
            std::cerr << "Error en línea\n";
        }
    }

    archivo.close();
    return equipos;
}
