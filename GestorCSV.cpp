#include "GestorCSV.h"
#include "Medidor.h"

#include <sstream>
#include <iostream>

// Constructor
GestorCSV::GestorCSV(std::string ruta)
    : path(ruta) {}

// Destructor
GestorCSV::~GestorCSV() {
    if (archivo.is_open()) archivo.close();
}

ListaDinamica<Equipo*> GestorCSV::cargarEquipos() {

    ListaDinamica<Equipo*> equipos;

    std::cout << "Intentando abrir: " << path << std::endl;
    std::cerr << "Por favor ingrese la ruta COMPLETA del archivo CSV:\n";

    std::string rutaManual;
    std::cout << "C:/des2/untitled13/build/Desktop_Qt_6_10_2_MinGW_64_bit-Debug/selecciones_clasificadas_mundial.csv:";
    std::getline(std::cin >> std::ws, rutaManual);

    archivo.open(rutaManual);

    if (!archivo.is_open()) {
        std::cerr << "ERROR: no se pudo abrir el CSV\n";
        return equipos;
    }

    std::string linea;

    // Saltar título y encabezados
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

        // Limpiar strings (CLAVE)
        auto limpiar = [](std::string& s) {
            s.erase(0, s.find_first_not_of(" \t\r\n"));
            s.erase(s.find_last_not_of(" \t\r\n") + 1);
        };

        limpiar(ranking);
        limpiar(pais);
        limpiar(conf);

        if (ranking.empty() || pais.empty()) continue;

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

            // Crear jugadores
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
            std::cerr << "Error procesando línea\n";
        }
    }

    archivo.close();
    return equipos;
}
