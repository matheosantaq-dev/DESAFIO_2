#ifndef GRUPO_H
#define GRUPO_H

#include <string>
#include "Equipo.h"
#include "Partido.h"

/**
 * Clase Grupo
 * Representa uno de los 12 grupos de la fase clasificatoria del mundial.
 *
 * Decisiones de diseño:
 * - equipos[4]: arreglo estático de punteros. El Grupo NO es dueño de los
 *   objetos Equipo; solo los referencia (relación de asociación).
 * - partidos: arreglo estático de punteros a Partido (6 por grupo: round-robin).
 *   El Grupo SÍ es dueño de los Partido* que crea (los libera en el destructor).
 * - tablaPuntos[4], golesDiferencia[4], golesAFavor[4]: índices paralelos
 *   al arreglo equipos[], para evitar duplicar datos y mantener eficiencia.
 * - clasificados[3]: los 3 primeros de grupo (1°, 2° y 3°) después de ordenar.
 *   Se llena al llamar construirTablaClasificacion().
 *
 * Relaciones:
 *   Grupo ──asocia──▶ Equipo*[4]
 *   Grupo ──posee──▶  Partido*[6]  (crea y destruye los partidos)
 */
class Grupo {
private:
    char   id;                   // Letra del grupo: 'A', 'B', ..., 'L'
    Equipo* equipos[4];          // Los 4 equipos del grupo (no propietario)
    int    numEquipos;           // Cuántos equipos se han añadido (0..4)

    // 6 partidos por grupo (round-robin: C(4,2) = 6).
    // El Grupo crea estos objetos con new → los destruye en el destructor.
    static const int MAX_PARTIDOS = 6;
    Partido* partidos[MAX_PARTIDOS];
    int numPartidos;

    // Tabla de clasificación (índices paralelos a equipos[])
    int tablaPuntos[4];          // puntos acumulados en la fase de grupos
    int tablaGolesDif[4];        // diferencia de goles (GF - GC del grupo)
    int tablaGolesAFavor[4];     // goles a favor (usados como desempate)

    // Orden de clasificación (índices dentro de equipos[]) tras ordenar
    // clasificados[0] = índice del 1° lugar, [1] = 2°, [2] = 3°, [3] = 4°
    int clasificados[4];

    // ── Métodos privados ──────────────────────────────────────
    /**
     * obtenerIndice: retorna el índice (0..3) del equipo dentro del arreglo,
     * o -1 si no está. Permite acceder a su fila en las tablas paralelas.
     */
    int obtenerIndice(const Equipo* equipo) const;

    /**
     * ordenarTabla: ordena clasificados[] por (puntos DESC, difGoles DESC,
     * golesAFavor DESC). Usa selección simple (O(n²) con n=4 → eficiente).
     */
    void ordenarTabla();

    /**
     * intercambiarClasificados: helper para el sort.
     */
    void intercambiarClasificados(int i, int j);

public:
    // Constructor: recibe la letra identificadora del grupo
    explicit Grupo(char id);

    // Destructor: libera los 6 objetos Partido* creados por el Grupo
    ~Grupo();

    // ── Getters ──────────────────────────────────────────────
    char getId() const;
    int  getNumEquipos() const;
    int  getNumPartidos() const;
    Equipo*  getEquipo(int indice) const;
    Partido* getPartido(int indice) const;

    /**
     * getClasificado: retorna el equipo en la posición pos (0=1°, 1=2°, 2=3°, 3=4°)
     * según la tabla de clasificación. Requiere haber llamado primero a
     * construirTablaClasificacion().
     */
    Equipo* getClasificado(int pos) const;

    int getPuntos(int indiceEquipo) const;
    int getDiferenciaGoles(int indiceEquipo) const;

    // ── Métodos requeridos por el UML ────────────────────────

    /**
     * agregarEquipo: añade un equipo al grupo (máx. 4).
     * Retorna false si ya están los 4.
     */
    bool agregarEquipo(Equipo* equipo);

    /**
     * organizarEncuentros: genera los 6 partidos del round-robin
     * (todos contra todos una vez) y los guarda en partidos[].
     * Asigna sede, árbitros y hora fijos según el enunciado.
     * @param fechaInicio Fecha base (formato "DD/MM/YYYY") del torneo
     */
    void organizarEncuentros(const std::string& fechaInicio);

    /**
     * simularFaseGrupal: simula los 6 partidos del grupo secuencialmente.
     * Cada partido llama a simularProbabilidades(false) (no es eliminatoria).
     */
    void simularFaseGrupal();

    /**
     * actualizarTabla: recalcula tablaPuntos[], tablaGolesDif[] y
     * tablaGolesAFavor[] leyendo el estado actual de cada Equipo*.
     * Se llama después de simular todos los partidos.
     */
    void actualizarTabla();

    /**
     * construirTablaClasificacion: llama a actualizarTabla() y luego
     * ordena clasificados[] aplicando los criterios de desempate del enunciado.
     */
    void construirTablaClasificacion();

    /**
     * resolverEmpates: aplica criterios de desempate cuando dos equipos
     * tienen los mismos puntos. Llamado internamente por ordenarTabla().
     * Criterios: 1) DG, 2) GF, 3) sorteo (rand).
     */
    void resolverEmpates();

    /**
     * mostrarResultados: imprime en consola todos los partidos del grupo
     * con sus resultados y goleadores (dorsales).
     */
    void mostrarResultados() const;

    /**
     * mostrarTabla: imprime la tabla de clasificación del grupo.
     * Requiere haber llamado construirTablaClasificacion() antes.
     */
    void mostrarTabla() const;

    /**
     * operator<< (función amiga): imprime un resumen del grupo.
     */
    friend std::ostream& operator<<(std::ostream& os, const Grupo& g);
};

#include <ostream>
std::ostream& operator<<(std::ostream& os, const Grupo& g);

#endif // GRUPO_H
