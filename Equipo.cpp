#include "Equipo.h"
#include "Medidor.h"


// Constructor

Equipo::Equipo(std::string nombre, int ranking)
    : pais(nombre), rankingFIFA(ranking),
      golesFavor(0), golesContra(0), puntos(0),
      victorias(0), empates(0), derrotas(0) {

    Medidor::add(sizeof(Equipo));
}


// Destructor

Equipo::~Equipo() {
    Medidor::sub(sizeof(Equipo));
}


// Jugadores

Jugador* Equipo::getJugador(int i) {
    Medidor::it();
    return plantilla.obtener(i);
}

int Equipo::getCantidadJugadores() const {
    return plantilla.getTamanio();
}


// Setters

void Equipo::setGolesFavor(int g) { golesFavor = g; }
void Equipo::setGolesContra(int g) { golesContra = g; }
void Equipo::setPuntos(int p) { puntos = p; }

void Equipo::setVictorias(int v) { victorias = v; }
void Equipo::setEmpates(int e) { empates = e; }
void Equipo::setDerrotas(int d) { derrotas = d; }


// Getters

std::string Equipo::getPais() const { return pais; }
int Equipo::getRanking() const { return rankingFIFA; }
int Equipo::getPuntos() const { return puntos; }

int Equipo::getGolesFavor() const { return golesFavor; }
int Equipo::getGolesContra() const { return golesContra; }

int Equipo::getVictorias() const { return victorias; }
int Equipo::getEmpates() const { return empates; }
int Equipo::getDerrotas() const { return derrotas; }


// PROMEDIOS 

double Equipo::promGF() const {
    return golesFavor / 3.0 + 1;
}

double Equipo::promGC() const {
    return golesContra / 3.0 + 1;
}


// RESET DE EQUIPO

void Equipo::resetStats() {
    golesFavor = 0;
    golesContra = 0;
    puntos = 0;
    victorias = 0;
    empates = 0;
    derrotas = 0;

    for (int i = 0; i < plantilla.getTamanio(); i++) {
        Medidor::it();
        Jugador* j = plantilla.obtener(i);
        if (j) j->resetTemp();
    }
}
