#include "GestorCSV.h"
#include "Medidor.h"
#include <sstream>
#include <iostream>

// Constructor
GestorCSV::GestorCSV(std::string ruta) : path(ruta) {}

// Destructor
GestorCSV::~GestorCSV() {
    if (archivo.is_open()) {
        archivo.close();
    }
}

// Cargar equipos
ListaDinamica<Equipo*> GestorCSV::cargarEquipos() {
    ListaDinamica<Equipo*> equiposCargados;

    archivo.open(path.c_str());

    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << path << std::endl;
        return equiposCargados;
    }

    std::string linea;

    // Saltar encabezados
    std::getline(archivo, linea);

    while (std::getline(archivo, linea)) {
        Medidor::it();

        if (linea.empty()) continue;

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

        if (pais.empty() || ranking.empty()) {
            continue;
        }

        try {
            int rankingInt = std::stoi(ranking);

            Equipo* nuevo = new Equipo(pais, rankingInt);

            // Datos extra
            nuevo->setDirectorTecnico(tecnico);
            nuevo->setConfederacion(conf);

            // Estadísticas históricas
            int golesFavor = gf.empty() ? 0 : std::stoi(gf);
            int golesContra = gc.empty() ? 0 : std::stoi(gc);
            int victorias = pg.empty() ? 0 : std::stoi(pg);
            int empates = pe.empty() ? 0 : std::stoi(pe);
            int derrotas = pp.empty() ? 0 : std::stoi(pp);

            nuevo->setGolesFavor(golesFavor);
            nuevo->setGolesContra(golesContra);
            nuevo->setVictorias(victorias);
            nuevo->setEmpates(empates);
            nuevo->setDerrotas(derrotas);

            // Distribución uniforme de goles entre 26 jugadores
            int golesBase = golesFavor / 26;
            int sobrantes = golesFavor % 26;

            for (int i = 1; i <= 26; i++) {
                Medidor::it();

                Jugador* jugador = new Jugador(
                    "nombre" + std::to_string(i),
                    "apellido" + std::to_string(i),
                    i
                );

                jugador->setPartidosJugadosHistoricos(0);

                int golesJugador = golesBase;
                if (sobrantes > 0) {
                    golesJugador++;
                    sobrantes--;
                }

                jugador->setGolesHistoricos(golesJugador);

                nuevo->agregarJugador(jugador);
            }

            equiposCargados.insertarAlFinal(nuevo);
        }
        catch (...) {
            std::cerr << "Error procesando línea: " << linea << std::endl;
        }
    }

    archivo.close();

    return equiposCargados;
}
