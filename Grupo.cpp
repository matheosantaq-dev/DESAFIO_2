#include "Grupo.h"
#include <iostream>
#include <cstdlib>   // rand()
#include <sstream>

// ─────────────────────────────────────────────
// Constructor
// ─────────────────────────────────────────────
Grupo::Grupo(char id)
    : id(id), numEquipos(0), numPartidos(0)
{
    // Inicializar arreglos de equipos y partidos a nullptr
    for (int i = 0; i < 4; i++) {
        equipos[i]           = nullptr;
        tablaPuntos[i]       = 0;
        tablaGolesDif[i]     = 0;
        tablaGolesAFavor[i]  = 0;
        clasificados[i]      = i; // orden inicial: 0,1,2,3
    }
    for (int i = 0; i < MAX_PARTIDOS; i++) {
        partidos[i] = nullptr;
    }
}

// ─────────────────────────────────────────────
// Destructor
// El Grupo SÍ es dueño de los Partido* → los libera.
// Los Equipo* son ajenos → NO se liberan aquí.
// ─────────────────────────────────────────────
Grupo::~Grupo() {
    for (int i = 0; i < numPartidos; i++) {
        delete partidos[i];
        partidos[i] = nullptr;
    }
}

// ─────────────────────────────────────────────
// Getters
// ─────────────────────────────────────────────
char   Grupo::getId() const         { return id; }
int    Grupo::getNumEquipos() const  { return numEquipos; }
int    Grupo::getNumPartidos() const { return numPartidos; }

Equipo* Grupo::getEquipo(int indice) const {
    if (indice < 0 || indice >= numEquipos) return nullptr;
    return equipos[indice];
}

Partido* Grupo::getPartido(int indice) const {
    if (indice < 0 || indice >= numPartidos) return nullptr;
    return partidos[indice];
}

Equipo* Grupo::getClasificado(int pos) const {
    if (pos < 0 || pos >= 4) return nullptr;
    return equipos[clasificados[pos]];
}

int Grupo::getPuntos(int indiceEquipo) const {
    if (indiceEquipo < 0 || indiceEquipo >= 4) return 0;
    return tablaPuntos[indiceEquipo];
}

int Grupo::getDiferenciaGoles(int indiceEquipo) const {
    if (indiceEquipo < 0 || indiceEquipo >= 4) return 0;
    return tablaGolesDif[indiceEquipo];
}

// ─────────────────────────────────────────────
// obtenerIndice (privado)
// Busca el índice del equipo en el arreglo equipos[].
// O(4) fijo → eficiente.
// ─────────────────────────────────────────────
int Grupo::obtenerIndice(const Equipo* equipo) const {
    for (int i = 0; i < numEquipos; i++) {
        if (equipos[i] == equipo) return i;
    }
    return -1;
}

// ─────────────────────────────────────────────
// agregarEquipo
// ─────────────────────────────────────────────
bool Grupo::agregarEquipo(Equipo* equipo) {
    if (numEquipos >= 4 || equipo == nullptr) return false;
    equipos[numEquipos] = equipo;
    numEquipos++;
    return true;
}

// ─────────────────────────────────────────────
// organizarEncuentros
// Genera los 6 partidos del round-robin.
// Restricciones del enunciado:
//   - Máx. 4 partidos por día.
//   - Ningún equipo juega más de 1 partido cada 3 días.
//   - Duración de la etapa: 19 días desde fechaInicio.
//
// Estrategia de fecha:
//   Se generan los 6 emparejamientos del round-robin con índices (i,j).
//   Se asignan días de forma que se respete la restricción de 3 días entre
//   partidos del mismo equipo. Con 4 equipos y 6 partidos en 19 días esto
//   se puede resolver con un esquema fijo de 3 jornadas:
//     Jornada 1 (día 0): E0 vs E1, E2 vs E3
//     Jornada 2 (día 4): E0 vs E2, E1 vs E3
//     Jornada 3 (día 8): E0 vs E3, E1 vs E2
//   Cada jornada tiene 2 partidos (≤4) y todos los equipos descansan ≥3 días.
//
// La fecha base se pasa en formato "DD/MM/YYYY".
// ─────────────────────────────────────────────
void Grupo::organizarEncuentros(const std::string& fechaInicio) {
    if (numEquipos < 4) return; // el grupo debe estar completo

    // Parsear fecha de inicio DD/MM/YYYY
    int dia  = (fechaInicio[0]-'0')*10 + (fechaInicio[1]-'0');
    int mes  = (fechaInicio[3]-'0')*10 + (fechaInicio[4]-'0');
    int anio = (fechaInicio[6]-'0')*1000 + (fechaInicio[7]-'0')*100
             + (fechaInicio[8]-'0')*10   + (fechaInicio[9]-'0');

    // Días de cada jornada desde la fecha de inicio del torneo
    // El grupo puede empezar en días distintos según su id para distribuir
    // los partidos a lo largo de los 19 días del torneo.
    // Offset por letra de grupo: 0,0,1,1,2,2,3,3,4,4,5,5
    int offsetGrupo = (id - 'A') / 2;  // grupos A-B: 0, C-D: 1, ..., K-L: 5

    // Jornadas internas del grupo (días relativos al inicio del torneo)
    int jornadasDias[3] = {
        offsetGrupo,          // jornada 1
        offsetGrupo + 6,      // jornada 2 (al menos 3 días de descanso + margen)
        offsetGrupo + 12      // jornada 3
    };

    // Helper lambda-like para construir fecha sumando N días
    // Se implementa como función inline simple (sin lambdas C++11 para compatibilidad)
    // Los 6 emparejamientos en 3 jornadas de 2 partidos:
    //   Jornada 1: [E0 vs E1], [E2 vs E3]
    //   Jornada 2: [E0 vs E2], [E1 vs E3]
    //   Jornada 3: [E0 vs E3], [E1 vs E2]
    int emparejamientos[6][2] = {
        {0,1},{2,3},
        {0,2},{1,3},
        {0,3},{1,2}
    };

    for (int p = 0; p < 6; p++) {
        // Calcular día del partido (días relativos al inicio del torneo)
        int diaRelativo = jornadasDias[p / 2]; // 2 partidos por jornada

        // Sumar diaRelativo a la fecha de inicio (aritmética de fechas simple)
        // Usamos días por mes (sin años bisiestos para simplificar, como pide el enunciado)
        int diasPorMes[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
        int d = dia + diaRelativo;
        int m = mes;
        int a = anio;
        while (d > diasPorMes[m]) {
            d -= diasPorMes[m];
            m++;
            if (m > 12) { m = 1; a++; }
        }

        // Formatear fecha como "DD/MM/YYYY"
        std::ostringstream fechaOss;
        if (d < 10) fechaOss << "0";
        fechaOss << d << "/";
        if (m < 10) fechaOss << "0";
        fechaOss << m << "/" << a;

        int iE = emparejamientos[p][0];
        int jE = emparejamientos[p][1];

        // Crear el partido (el Grupo es propietario de este objeto)
        Partido* partido = new Partido(
            equipos[iE],       // local
            equipos[jE],       // visitante
            "nombreSede",      // sede fija según enunciado
            fechaOss.str(),    // fecha calculada
            "00:00"            // hora fija según enunciado
        );
        // Árbitros fijos según enunciado
        partido->setArbitro("codArbitro1", 0);
        partido->setArbitro("codArbitro2", 1);
        partido->setArbitro("codArbitro3", 2);

        partidos[numPartidos] = partido;
        numPartidos++;
    }
}

// ─────────────────────────────────────────────
// simularFaseGrupal
// Simula los 6 partidos secuencialmente.
// La simulación no es eliminatoria (empate queda como empate).
// ─────────────────────────────────────────────
void Grupo::simularFaseGrupal() {
    for (int i = 0; i < numPartidos; i++) {
        if (partidos[i] != nullptr && !partidos[i]->estaSimulado()) {
            partidos[i]->simularProbabilidades(false);
        }
    }
}

// ─────────────────────────────────────────────
// actualizarTabla
// Lee el estado actual de cada Equipo* y rellena las tablas paralelas.
// IMPORTANTE: solo cuenta los puntos que el equipo acumuló EN ESTE GRUPO.
// Los equipos ya llevan el acumulado en puntosFaseGrupos internamente
// (Partido::simularProbabilidades() llama a equipo->sumarPuntosGrupo()).
// ─────────────────────────────────────────────
void Grupo::actualizarTabla() {
    for (int i = 0; i < numEquipos; i++) {
        if (equipos[i] == nullptr) continue;
        tablaPuntos[i]      = equipos[i]->getPuntosFaseGrupos();
        tablaGolesDif[i]    = equipos[i]->getDiferenciaGoles();
        tablaGolesAFavor[i] = equipos[i]->getGolesAFavor();
    }
}

// ─────────────────────────────────────────────
// intercambiarClasificados (privado)
// Intercambia dos posiciones en el arreglo clasificados[].
// ─────────────────────────────────────────────
void Grupo::intercambiarClasificados(int i, int j) {
    int tmp = clasificados[i];
    clasificados[i] = clasificados[j];
    clasificados[j] = tmp;
}

// ─────────────────────────────────────────────
// ordenarTabla (privado)
// Selection sort descendente sobre clasificados[] usando los criterios:
//   1. Puntos (mayor primero)
//   2. Diferencia de goles (mayor primero)
//   3. Goles a favor (mayor primero)
//   4. Sorteo aleatorio
// O(16) = O(1) para n=4 fijo → eficiente.
// ─────────────────────────────────────────────
void Grupo::ordenarTabla() {
    for (int i = 0; i < 3; i++) {          // 3 pasadas para 4 elementos
        int mejor = i;
        for (int j = i + 1; j < 4; j++) {
            int iE = clasificados[j];
            int mE = clasificados[mejor];

            // Criterio 1: puntos
            if (tablaPuntos[iE] > tablaPuntos[mE]) {
                mejor = j;
            } else if (tablaPuntos[iE] == tablaPuntos[mE]) {
                // Criterio 2: diferencia de goles
                if (tablaGolesDif[iE] > tablaGolesDif[mE]) {
                    mejor = j;
                } else if (tablaGolesDif[iE] == tablaGolesDif[mE]) {
                    // Criterio 3: goles a favor
                    if (tablaGolesAFavor[iE] > tablaGolesAFavor[mE]) {
                        mejor = j;
                    } else if (tablaGolesAFavor[iE] == tablaGolesAFavor[mE]) {
                        // Criterio 4: sorteo (50/50)
                        if (rand() % 2 == 0) mejor = j;
                    }
                }
            }
        }
        if (mejor != i) intercambiarClasificados(i, mejor);
    }
}

// ─────────────────────────────────────────────
// resolverEmpates
// Expuesto públicamente como indica el UML.
// Internamente delega en ordenarTabla() que ya incluye los criterios.
// ─────────────────────────────────────────────
void Grupo::resolverEmpates() {
    ordenarTabla();
}

// ─────────────────────────────────────────────
// construirTablaClasificacion
// ─────────────────────────────────────────────
void Grupo::construirTablaClasificacion() {
    actualizarTabla();
    ordenarTabla();
}

// ─────────────────────────────────────────────
// mostrarResultados
// Imprime los 6 partidos del grupo con datos y goleadores.
// ─────────────────────────────────────────────
void Grupo::mostrarResultados() const {
    std::cout << "\n═══════════════════════════════════════\n";
    std::cout << "  GRUPO " << id << " — Resultados\n";
    std::cout << "═══════════════════════════════════════\n";
    for (int i = 0; i < numPartidos; i++) {
        if (partidos[i] != nullptr) {
            partidos[i]->printResumen();
        }
    }
}

// ─────────────────────────────────────────────
// mostrarTabla
// Imprime la tabla de clasificación estilo FIFA.
// Requiere haber llamado construirTablaClasificacion() antes.
// ─────────────────────────────────────────────
void Grupo::mostrarTabla() const {
    std::cout << "\n┌─────────────────────────────────────────────────────┐\n";
    std::cout << "│  TABLA GRUPO " << id
              << "   PJ  PG  PE  PP  GF  GC  DG  PTS │\n";
    std::cout << "├─────────────────────────────────────────────────────┤\n";

    for (int pos = 0; pos < numEquipos; pos++) {
        int idx = clasificados[pos];
        if (equipos[idx] == nullptr) continue;

        Equipo* e = equipos[idx];
        int pj = e->getPartidosGanados() + e->getPartidosEmpatados() + e->getPartidosPerdidos();
        int gf = tablaGolesAFavor[idx];
        int gc = gf - tablaGolesDif[idx]; // gc = gf - dg  → dg = gf - gc
        int dg = tablaGolesDif[idx];
        int pts = tablaPuntos[idx];

        std::cout << "│ " << (pos+1) << ". ";
        // Nombre del país (padding simple)
        std::string nombre = e->getPais();
        if (nombre.size() > 14) nombre = nombre.substr(0,14);
        std::cout << nombre;
        for (int s = (int)nombre.size(); s < 14; s++) std::cout << " ";

        // Estadísticas
        auto printCol = [](int v, int w) {
            // Imprime número con padding
            std::string s = std::to_string(v);
            for (int i = (int)s.size(); i < w; i++) std::cout << " ";
            std::cout << s;
        };
        std::cout << "  ";
        printCol(pj, 2); std::cout << "  ";
        printCol(e->getPartidosGanados(), 2); std::cout << "  ";
        printCol(e->getPartidosEmpatados(), 2); std::cout << "  ";
        printCol(e->getPartidosPerdidos(), 2); std::cout << "  ";
        printCol(gf, 2); std::cout << "  ";
        printCol(gc, 2); std::cout << "  ";
        if (dg >= 0) std::cout << " ";
        std::cout << dg << "  ";
        printCol(pts, 3);
        std::cout << " │\n";
    }
    std::cout << "└─────────────────────────────────────────────────────┘\n";
}

// ─────────────────────────────────────────────
// operator<<  (función amiga — sobrecarga #4 del sistema)
// ─────────────────────────────────────────────
std::ostream& operator<<(std::ostream& os, const Grupo& g) {
    os << "Grupo " << g.id << " [";
    for (int i = 0; i < g.numEquipos; i++) {
        if (g.equipos[i]) os << g.equipos[i]->getPais();
        if (i < g.numEquipos - 1) os << ", ";
    }
    os << "]";
    return os;
}
