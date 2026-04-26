#include "Equipo.h"
#include "Medidor.h"

// Constructor
Equipo::Equipo(std::string nombre, int ranking)
    : pais(nombre), confederacion(""),
    directorTecnico(""),
    rankingFIFA(ranking),
    golesFavor(0), golesContra(0),
    puntos(0), victorias(0),
    empates(0), derrotas(0),
    amarillas(0), rojas(0), faltas(0)
{
    Medidor::add(sizeof(Equipo));
}

// Constructor copia
Equipo::Equipo(const Equipo& otro)
    : pais(otro.pais),
    confederacion(otro.confederacion),
    directorTecnico(otro.directorTecnico),
    rankingFIFA(otro.rankingFIFA),
    golesFavor(otro.golesFavor),
    golesContra(otro.golesContra),
    puntos(otro.puntos),
    victorias(otro.victorias),
    empates(otro.empates),
    derrotas(otro.derrotas),
    amarillas(otro.amarillas),
    rojas(otro.rojas),
    faltas(otro.faltas)
{
    for (int i = 0; i < otro.plantilla.getTamanio(); i++) {
        Jugador* copia = new Jugador(*otro.plantilla.obtener(i));
        plantilla.insertarAlFinal(copia);
    }

    Medidor::add(sizeof(Equipo));
}

// Destructor
Equipo::~Equipo() {
    for (int i = 0; i < plantilla.getTamanio(); i++) {
        delete plantilla.obtener(i);
    }

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

void Equipo::agregarJugador(Jugador* j) {
    plantilla.insertarAlFinal(j);
}

// Setters
void Equipo::setGolesFavor(int g) { golesFavor = g; }
void Equipo::setGolesContra(int g) { golesContra = g; }
void Equipo::setPuntos(int p) { puntos = p; }
void Equipo::setVictorias(int v) { victorias = v; }
void Equipo::setEmpates(int e) { empates = e; }
void Equipo::setDerrotas(int d) { derrotas = d; }

void Equipo::setConfederacion(const std::string& conf) {
    confederacion = conf;
}

void Equipo::setDirectorTecnico(const std::string& dt) {
    directorTecnico = dt;
}

// Getters
std::string Equipo::getPais() const { return pais; }
std::string Equipo::getConfederacion() const { return confederacion; }
std::string Equipo::getDirectorTecnico() const { return directorTecnico; }

int Equipo::getRanking() const { return rankingFIFA; }
int Equipo::getPuntos() const { return puntos; }
int Equipo::getGolesFavor() const { return golesFavor; }
int Equipo::getGolesContra() const { return golesContra; }

int Equipo::getVictorias() const { return victorias; }
int Equipo::getEmpates() const { return empates; }
int Equipo::getDerrotas() const { return derrotas; }

// Promedios
double Equipo::promGF() const {
    return golesFavor / 3.0 + 1;
}

double Equipo::promGC() const {
    return golesContra / 3.0 + 1;
}

// Actualizar resultado
void Equipo::actualizarResultado(int gf, int gc) {
    golesFavor += gf;
    golesContra += gc;

    if (gf > gc) {
        victorias++;
        puntos += 3;
    }
    else if (gf == gc) {
        empates++;
        puntos += 1;
    }
    else {
        derrotas++;
    }
}

// Reset
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
        if (j) {
            j->resetTemp();
        }
    }
}

// Sobrecarga <
bool Equipo::operator<(const Equipo& otro) const {
    return rankingFIFA < otro.rankingFIFA;
}

// Sobrecarga >
bool Equipo::operator>(const Equipo& otro) const {
    return rankingFIFA > otro.rankingFIFA;
}

// Operador <<
std::ostream& operator<<(std::ostream& os, const Equipo& equipo) {
    os << equipo.pais
       << " | Ranking FIFA: " << equipo.rankingFIFA
       << " | Puntos: " << equipo.puntos;

    return os;
}
