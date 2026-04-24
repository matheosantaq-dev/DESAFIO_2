#include "Jugador.h"
#include <sstream>

// ─────────────────────────────────────────────
// Constructor principal
// ─────────────────────────────────────────────
Jugador::Jugador(const std::string& nombre, const std::string& apellido, int dorsal)
    : nombre(nombre), apellido(apellido), dorsal(dorsal),
      golesHistoricos(0), asistenciasHistoricas(0),
      amarillasHistoricas(0), rojasHistoricas(0),
      faltasHistoricas(0), minutosHistoricos(0),
      partidosJugadosHistoricos(0),
      golesTemp(0), asistenciasTemp(0),
      amarillasTemp(0), rojasTemp(0),
      faltasTemp(0), minutosTemp(0)
{}

// ─────────────────────────────────────────────
// Constructor de copia
// ─────────────────────────────────────────────
Jugador::Jugador(const Jugador& otro)
    : nombre(otro.nombre), apellido(otro.apellido), dorsal(otro.dorsal),
      golesHistoricos(otro.golesHistoricos),
      asistenciasHistoricas(otro.asistenciasHistoricas),
      amarillasHistoricas(otro.amarillasHistoricas),
      rojasHistoricas(otro.rojasHistoricas),
      faltasHistoricas(otro.faltasHistoricas),
      minutosHistoricos(otro.minutosHistoricos),
      partidosJugadosHistoricos(otro.partidosJugadosHistoricos),
      golesTemp(otro.golesTemp), asistenciasTemp(otro.asistenciasTemp),
      amarillasTemp(otro.amarillasTemp), rojasTemp(otro.rojasTemp),
      faltasTemp(otro.faltasTemp), minutosTemp(otro.minutosTemp)
{}

// ─────────────────────────────────────────────
// Destructor (no hay memoria dinámica propia en Jugador)
// ─────────────────────────────────────────────
Jugador::~Jugador() {}

// ─────────────────────────────────────────────
// Getters
// ─────────────────────────────────────────────
std::string Jugador::getNombre() const { return nombre; }
std::string Jugador::getApellido() const { return apellido; }
std::string Jugador::getNombreCompleto() const { return nombre + " " + apellido; }
int Jugador::getDorsal() const { return dorsal; }

int Jugador::getGolesHistoricos() const { return golesHistoricos; }
int Jugador::getAsistenciasHistoricas() const { return asistenciasHistoricas; }
int Jugador::getAmarillasHistoricas() const { return amarillasHistoricas; }
int Jugador::getRojasHistoricas() const { return rojasHistoricas; }
int Jugador::getFaltasHistoricas() const { return faltasHistoricas; }
int Jugador::getMinutosHistoricos() const { return minutosHistoricos; }
int Jugador::getPartidosJugadosHistoricos() const { return partidosJugadosHistoricos; }

int Jugador::getGolesTemp() const { return golesTemp; }
int Jugador::getAmarillasTemp() const { return amarillasTemp; }
int Jugador::getFaltasTemp() const { return faltasTemp; }

// ─────────────────────────────────────────────
// Setters
// ─────────────────────────────────────────────
void Jugador::setGolesHistoricos(int g) { golesHistoricos = g; }
void Jugador::setPartidosJugadosHistoricos(int p) { partidosJugadosHistoricos = p; }

// ─────────────────────────────────────────────
// registrarAccion
// Discrimina por string para mapear eventos del partido a estadísticas.
// Decisión: se prefiere string sobre enum para mantener extensibilidad
// sin modificar la firma del método (según UML).
// ─────────────────────────────────────────────
void Jugador::registrarAccion(const std::string& accion) {
    if (accion == "gol") {
        golesTemp++;
    } else if (accion == "asistencia") {
        asistenciasTemp++;
    } else if (accion == "amarilla") {
        registrarAmarilla(); // delega para manejar la lógica de roja
    } else if (accion == "falta") {
        faltasTemp++;
    }
    // "minutos:<N>" se maneja en consolidarPartido con parámetro explícito
}

// ─────────────────────────────────────────────
// registrarAmarilla
// La segunda amarilla en el mismo partido produce tarjeta roja.
// ─────────────────────────────────────────────
void Jugador::registrarAmarilla() {
    amarillasTemp++;
    if (amarillasTemp == 2) {
        rojasTemp++; // roja por doble amarilla
    }
}

// ─────────────────────────────────────────────
// getFichaTecnica
// Retorna un resumen legible del jugador con datos históricos.
// ─────────────────────────────────────────────
std::string Jugador::getFichaTecnica() const {
    std::ostringstream oss;
    oss << "─────────────────────────────\n";
    oss << "Jugador #" << dorsal << ": " << nombre << " " << apellido << "\n";
    oss << "  Partidos jugados : " << partidosJugadosHistoricos << "\n";
    oss << "  Goles            : " << golesHistoricos << "\n";
    oss << "  Asistencias      : " << asistenciasHistoricas << "\n";
    oss << "  Amarillas        : " << amarillasHistoricas << "\n";
    oss << "  Rojas            : " << rojasHistoricas << "\n";
    oss << "  Faltas           : " << faltasHistoricas << "\n";
    oss << "  Minutos jugados  : " << minutosHistoricos << "\n";
    oss << "─────────────────────────────\n";
    return oss.str();
}

// ─────────────────────────────────────────────
// resetTemp
// Limpia SOLO las estadísticas del partido actual.
// Se llama al inicio de cada partido para preparar al jugador.
// ─────────────────────────────────────────────
void Jugador::resetTemp() {
    golesTemp       = 0;
    asistenciasTemp = 0;
    amarillasTemp   = 0;
    rojasTemp       = 0;
    faltasTemp      = 0;
    minutosTemp     = 0;
}

// ─────────────────────────────────────────────
// consolidarPartido
// Cierra un partido: suma temporales al histórico y resetea.
// Parámetro minutos: 90 (normal) o 120 (prórroga).
// ─────────────────────────────────────────────
void Jugador::consolidarPartido(int minutos) {
    golesHistoricos          += golesTemp;
    asistenciasHistoricas    += asistenciasTemp;
    amarillasHistoricas      += amarillasTemp;
    rojasHistoricas          += rojasTemp;
    faltasHistoricas         += faltasTemp;
    minutosHistoricos        += minutos;
    partidosJugadosHistoricos++;
    resetTemp();
}
