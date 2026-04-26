#include "Jugador.h"
#include "Medidor.h"
#include <sstream>

// Constructor principal
Jugador::Jugador(const std::string& nombre, const std::string& apellido, int dorsal)
    : nombre(nombre), apellido(apellido), dorsal(dorsal),
    golesHistoricos(0), asistenciasHistoricas(0),
    amarillasHistoricas(0), rojasHistoricas(0),
    faltasHistoricas(0), minutosHistoricos(0),
    partidosJugadosHistoricos(0),
    golesTemp(0), asistenciasTemp(0),
    amarillasTemp(0), rojasTemp(0),
    faltasTemp(0), minutosTemp(0)
{
    Medidor::add(sizeof(Jugador));
}

// Constructor copia
Jugador::Jugador(const Jugador& otro)
    : nombre(otro.nombre), apellido(otro.apellido), dorsal(otro.dorsal),
    golesHistoricos(otro.golesHistoricos),
    asistenciasHistoricas(otro.asistenciasHistoricas),
    amarillasHistoricas(otro.amarillasHistoricas),
    rojasHistoricas(otro.rojasHistoricas),
    faltasHistoricas(otro.faltasHistoricas),
    minutosHistoricos(otro.minutosHistoricos),
    partidosJugadosHistoricos(otro.partidosJugadosHistoricos),
    golesTemp(otro.golesTemp),
    asistenciasTemp(otro.asistenciasTemp),
    amarillasTemp(otro.amarillasTemp),
    rojasTemp(otro.rojasTemp),
    faltasTemp(otro.faltasTemp),
    minutosTemp(otro.minutosTemp)
{
    Medidor::add(sizeof(Jugador));
}

// Destructor
Jugador::~Jugador() {
    Medidor::sub(sizeof(Jugador));
}

// Getters
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

// Setters
void Jugador::setGolesHistoricos(int g) {
    golesHistoricos = g;
}

void Jugador::setPartidosJugadosHistoricos(int p) {
    partidosJugadosHistoricos = p;
}

// Registrar acción
void Jugador::registrarAccion(const std::string& accion) {
    Medidor::it();

    if (accion == "gol") {
        golesTemp++;
    }
    else if (accion == "asistencia") {
        asistenciasTemp++;
    }
    else if (accion == "amarilla") {
        registrarAmarilla();
    }
    else if (accion == "falta") {
        faltasTemp++;
    }
}

// Amarilla
void Jugador::registrarAmarilla() {
    Medidor::it();

    amarillasTemp++;

    if (amarillasTemp == 2) {
        rojasTemp++;
    }
}

// Reset partido
void Jugador::resetTemp() {
    Medidor::it();

    golesTemp = 0;
    asistenciasTemp = 0;
    amarillasTemp = 0;
    rojasTemp = 0;
    faltasTemp = 0;
    minutosTemp = 0;
}

// Consolidar partido
void Jugador::consolidarPartido(int minutos) {
    Medidor::it();

    golesHistoricos += golesTemp;
    asistenciasHistoricas += asistenciasTemp;
    amarillasHistoricas += amarillasTemp;
    rojasHistoricas += rojasTemp;
    faltasHistoricas += faltasTemp;
    minutosHistoricos += minutos;
    partidosJugadosHistoricos++;

    resetTemp();
}

// Ficha técnica
std::string Jugador::getFichaTecnica() const {
    std::ostringstream oss;

    oss << "─────────────────────────────\n";
    oss << "Jugador #" << dorsal << ": " << nombre << " " << apellido << "\n";
    oss << "Partidos: " << partidosJugadosHistoricos << "\n";
    oss << "Goles: " << golesHistoricos << "\n";
    oss << "Asistencias: " << asistenciasHistoricas << "\n";
    oss << "Amarillas: " << amarillasHistoricas << "\n";
    oss << "Rojas: " << rojasHistoricas << "\n";
    oss << "Faltas: " << faltasHistoricas << "\n";
    oss << "Minutos: " << minutosHistoricos << "\n";
    oss << "─────────────────────────────\n";

    return oss.str();
}

// Sobrecarga >
bool Jugador::operator>(const Jugador& otro) const {
    return golesHistoricos > otro.golesHistoricos;
}

// Sobrecarga <
bool Jugador::operator<(const Jugador& otro) const {
    return golesHistoricos < otro.golesHistoricos;
}

// Operador <<
std::ostream& operator<<(std::ostream& os, const Jugador& jugador) {
    os << jugador.getNombreCompleto()
    << " (#" << jugador.getDorsal() << ") "
    << "- Goles: " << jugador.getGolesHistoricos();

    return os;
}

