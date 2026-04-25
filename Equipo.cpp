#include "Equipo.h"

//Constructor
Equipo::Equipo(std::string nombre, int ranking)
    : pais(nombre), rankingFIFA(ranking),
    golesFavor(0), golesContra(0), puntos(0),
    victorias(0), empates(0), derrotas(0) {}

//agrega jugadores
Jugador* Equipo::getJugador(int i) {
    return plantilla.obtener(i);
}

int Equipo::getCantidadJugadores() const {
    return plantilla.getTamanio();
}

//Setters
void Equipo::setGolesFavor(int g) {
    golesFavor = g;
}
void Equipo::setGolesContra(int g) {
    golesContra = g;
}
void Equipo::setPuntos(int p) {
    puntos = p;
}

//Getters
std::string Equipo::getPais() const {
    return pais;
}
int Equipo::getRanking() const {
    return rankingFIFA;
}
int Equipo::getPuntos() const {
    return puntos;
}

//Goles
int Equipo::getGolesFavor() const {
    return golesFavor;
}
int Equipo::getGolesContra() const {
    return golesContra;
}

//Estadísticas de partidos
void Equipo::setVictorias(int v) {
    victorias = v;
}
void Equipo::setEmpates(int e) {
    empates = e;
}
void Equipo::setDerrotas(int d) {
    derrotas = d;
}

int Equipo::getVictorias() const {
    return victorias;
}
int Equipo::getEmpates() const {
    return empates;
}
int Equipo::getDerrotas() const {
    return derrotas;
}
/*implementan getters y setters necesarios para manejar las estadísticas del equipo (goles, puntos, victorias, etc.).
Esto permite que otras clases como Partido puedan modificar y consultar estos valores sin acceder directamente a los atributos,
manteniendo el principio de encapsulamiento.*/
