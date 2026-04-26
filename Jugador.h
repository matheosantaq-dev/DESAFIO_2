#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include <iostream>

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

    // Estadísticas temporales
    int golesTemp;
    int asistenciasTemp;
    int amarillasTemp;
    int rojasTemp;
    int faltasTemp;
    int minutosTemp;

public:
    // Constructores
    Jugador(const std::string& nombre = "", const std::string& apellido = "", int dorsal = 0);
    Jugador(const Jugador& otro);

    // Destructor
    ~Jugador();

    // Getters
    std::string getNombre() const;
    std::string getApellido() const;
    std::string getNombreCompleto() const;
    int getDorsal() const;

    int getGolesHistoricos() const;
    int getAsistenciasHistoricas() const;
    int getAmarillasHistoricas() const;
    int getRojasHistoricas() const;
    int getFaltasHistoricas() const;
    int getMinutosHistoricos() const;
    int getPartidosJugadosHistoricos() const;

    int getGolesTemp() const;
    int getAmarillasTemp() const;
    int getFaltasTemp() const;

    // Setters
    void setGolesHistoricos(int g);
    void setPartidosJugadosHistoricos(int p);

    // Lógica
    void registrarAccion(const std::string& accion);
    void registrarAmarilla();

    // Partido
    void resetTemp();
    void consolidarPartido(int minutos);

    // Utilidad
    std::string getFichaTecnica() const;

    // Sobrecarga
    bool operator>(const Jugador& otro) const;
    bool operator<(const Jugador& otro) const;

    // Función amiga
    friend std::ostream& operator<<(std::ostream& os, const Jugador& jugador);
};

#endif
