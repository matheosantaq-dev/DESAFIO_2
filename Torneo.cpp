#include "Torneo.h"
#include "Medidor.h"
#include <iostream>
#include <fstream>

// Constructor
Torneo::Torneo()
    : totalGoles(0), campeon(nullptr),
    subcampeon(nullptr), tercerLugar(nullptr)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 12; j++)
            bombos[i][j] = nullptr;
}

// Destructor
Torneo::~Torneo() {
    for (int i = 0; i < grupos.getTamanio(); i++) {
        delete grupos.obtener(i);
    }
}

// Bombos
void Torneo::organizarBombos(ListaDinamica<Equipo*>& listaEquipos) {

    listaEquipos.ordenarPorRanking();

    int k = 0;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 12; j++)
            bombos[i][j] = listaEquipos.obtener(k++);
}

// Crear grupos
void Torneo::crearGrupos() {

    grupos.limpiar();

    for (int i = 0; i < 12; i++) {

        Grupo* g = new Grupo('A' + i);

        for (int b = 0; b < 4; b++) {
            if (bombos[b][i])
                g->agregarEquipo(bombos[b][i]);
        }

        g->organizarEncuentros("01/06/2026");
        grupos.insertarAlFinal(g);
    }

    std::cout << "Grupos creados correctamente\n";
}

// Fase grupos
void Torneo::simularFaseGrupos() {

    for (int i = 0; i < grupos.getTamanio(); i++) {
        Grupo* g = grupos.obtener(i);
        if (!g) continue;

        g->simularFaseGrupal();
        g->mostrarResultados();
    }

    clasificarEquipos();
}

// Clasificación
void Torneo::clasificarEquipos() {

    clasificados.limpiar();

    for (int i = 0; i < grupos.getTamanio(); i++) {

        Grupo* g = grupos.obtener(i);
        if (!g) continue;

        Equipo** top2 = g->getClasificados();

        if (top2) {
            clasificados.insertarAlFinal(top2[0]);
            clasificados.insertarAlFinal(top2[1]);
            delete[] top2;
        }
    }

    std::cout << "\nClasificados: "
              << clasificados.getTamanio()
              << " equipos.\n";
}

// AHORA COMO MÉTODO PRIVADO (MEJOR DISEÑO)
Equipo* Torneo::jugarPartido(Equipo* a, Equipo* b, Equipo*& perdedor) {

    if (!a || !b) return nullptr;

    Partido p(a, b, "20/06/2026", "Estadio");
    p.simular(true);
    p.printResumen();

    if (p.getGolesLocal() > p.getGolesVisitante()) {
        perdedor = b;
        return a;
    } else {
        perdedor = a;
        return b;
    }
}

// Eliminatorias
void Torneo::simularEliminatorias() {

    ListaDinamica<Equipo*> ronda;

    for (int i = 0; i < clasificados.getTamanio(); i++) {
        ronda.insertarAlFinal(clasificados.obtener(i));
    }

    // 24 → 16
    ListaDinamica<Equipo*> ronda16;

    std::cout << "\n=== DIECISEISAVOS ===\n";

    for (int i = 0; i < 16 && i < ronda.getTamanio(); i++) {
        ronda16.insertarAlFinal(ronda.obtener(i));
    }

    ronda = ronda16;

    // Rondas normales
    while (ronda.getTamanio() > 4) {

        ListaDinamica<Equipo*> siguiente;

        std::cout << "\n=== RONDA ===\n";

        for (int i = 0; i < ronda.getTamanio(); i += 2) {

            Equipo* perdedor = nullptr;

            Equipo* ganador = jugarPartido(
                ronda.obtener(i),
                ronda.obtener(i + 1),
                perdedor
                );

            if (ganador)
                siguiente.insertarAlFinal(ganador);
        }

        ronda = siguiente;
    }

    // Validación extra
    if (ronda.getTamanio() < 4) {
        std::cout << "Error en eliminatorias\n";
        return;
    }

    // Semifinales
    std::cout << "\n=== SEMIFINALES ===\n";

    Equipo* perd1 = nullptr;
    Equipo* finalista1 = jugarPartido(ronda.obtener(0), ronda.obtener(1), perd1);

    Equipo* perd2 = nullptr;
    Equipo* finalista2 = jugarPartido(ronda.obtener(2), ronda.obtener(3), perd2);

    // Tercer puesto
    std::cout << "\n=== TERCER PUESTO ===\n";

    Equipo* basura = nullptr;
    tercerLugar = jugarPartido(perd1, perd2, basura);

    // Final
    std::cout << "\n=== FINAL ===\n";

    Equipo* perdFinal = nullptr;
    campeon = jugarPartido(finalista1, finalista2, perdFinal);
    subcampeon = perdFinal;
}

// Estadísticas
void Torneo::generarEstadisticas() {

    for (int i = 0; i < grupos.getTamanio(); i++) {
        Grupo* g = grupos.obtener(i);
        if (g) g->mostrarTabla();
    }

    mostrarPodio();
}

// Podio
void Torneo::mostrarPodio() {

    std::cout << "\n=========== PODIO MUNDIAL ===========\n";

    std::cout << "Campeon: "
              << (campeon ? campeon->getPais() : "N/A") << "\n";

    std::cout << "Subcampeon: "
              << (subcampeon ? subcampeon->getPais() : "N/A") << "\n";

    std::cout << "Tercer Lugar: "
              << (tercerLugar ? tercerLugar->getPais() : "N/A") << "\n";

    std::cout << "=====================================\n";
}

// Guardar CSV (sobrescribe)
void Torneo::guardarCSV(const std::string& ruta,
                        ListaDinamica<Equipo*>& equipos) {

    std::ofstream file(ruta);

    if (!file.is_open()) {
        std::cout << "Error al guardar CSV\n";
        return;
    }

    file << "Pais,Ranking,GF,GC,Puntos,V,E,D\n";

    for (int i = 0; i < equipos.getTamanio(); i++) {

        Equipo* e = equipos.obtener(i);
        if (!e) continue;

        file << e->getPais() << ","
             << e->getRanking() << ","
             << e->getGolesFavor() << ","
             << e->getGolesContra() << ","
             << e->getPuntos() << ","
             << e->getVictorias() << ","
             << e->getEmpates() << ","
             << e->getDerrotas()
             << "\n";
    }

    file.close();

    std::cout << "CSV actualizado correctamente\n";
}

// Getter
ListaDinamica<Grupo*>& Torneo::getGrupos() {
    return grupos;
}
