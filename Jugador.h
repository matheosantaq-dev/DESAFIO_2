#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>

class Jugador {
private:
    std::string nombre;
    std::string apellido;
    int dorsal;

    // Estadísticas históricas
    int golesHistoricos;
    int asistenciasHistoricas;
    int amarillasHistoricas;
    int rojasHistoricas;
    int faltasHistoricas;
    int minutosHistoricos;
    int partidosJugadosHistoricos;

    // Estadísticas temporales (para el partido actual)
    int golesTemp;
    int asistenciasTemp;
    int amarillasTemp;
    int rojasTemp;
    int faltasTemp;
    int minutosTemp;

public:
    Jugador(const std::string& nombre, const std::string& apellido, int dorsal);
    Jugador(const Jugador& otro); // Constructor de copia

    // Métodos para el juego
    void resetTemp();
    void consolidarPartido(int minutos);
    std::string toString() const; // Para mostrar datos
};

#endif
