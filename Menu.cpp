#include "Menu.h"
#include "Medidor.h"
#include <iostream>
#include <cstdlib>

// Constructor
Menu::Menu()
    : gestor("selecciones_clasificadas_mundial.csv")
{
}

// Destructor
Menu::~Menu() {
    liberarMemoria();
}

// Banner principal
void Menu::mostrarBanner() const {
    std::cout << "\n=========================================\n";
    std::cout << "   SIMULADOR COPA MUNDIAL FIFA 2026\n";
    std::cout << "   Desafío Final - Informática II\n";
    std::cout << "=========================================\n";
}

// Opciones
void Menu::mostrarOpciones() const {
    std::cout << "\nSeleccione una opción:\n";
    std::cout << "1. Cargar selecciones desde CSV\n";
    std::cout << "2. Organizar bombos y grupos\n";
    std::cout << "3. Simular Mundial completo\n";
    std::cout << "4. Mostrar métricas\n";
    std::cout << "5. Salir\n";
    std::cout << "Opción: ";
}

// Cargar datos
void Menu::cargarDatos() {
    equipos = gestor.cargarEquipos();

    if (equipos.getTamanio() >= 48) {
        std::cout << "\nEquipos cargados correctamente: "
                  << equipos.getTamanio()
                  << "\n";
    } else {
        std::cout << "\nError: No se cargaron suficientes equipos.\n";
    }
}

// Organizar torneo
void Menu::organizarTorneo() {
    if (equipos.getTamanio() < 48) {
        std::cout << "\nDebe cargar primero los equipos.\n";
        return;
    }

    torneo.organizarBombos(equipos);
    torneo.crearGrupos();

    std::cout << "\nGrupos creados exitosamente.\n";
}

// Simular torneo
void Menu::simularMundial() {
    if (torneo.getGrupos().getTamanio() == 0) {
        std::cout << "\nDebe organizar primero el torneo.\n";
        return;
    }

    std::cout << "\n===== INICIANDO FASE DE GRUPOS =====\n";
    torneo.simularFaseGrupos();

    std::cout << "\n===== INICIANDO ELIMINATORIAS =====\n";
    torneo.simularEliminatorias();

    std::cout << "\n===== ESTADÍSTICAS FINALES =====\n";
    torneo.generarEstadisticas();
}

// Métricas
void Menu::mostrarMetricas() {
    Medidor::print();
}

// Liberar memoria
void Menu::liberarMemoria() {
    for (int i = 0; i < equipos.getTamanio(); i++) {
        Equipo* equipo = equipos.obtener(i);

        if (equipo) {
            delete equipo;
        }
    }

    equipos.limpiar();
}

// Ejecución principal
void Menu::iniciar() {
    int opcion = 0;

    do {
        mostrarBanner();
        mostrarOpciones();

        std::cin >> opcion;

        switch (opcion) {
        case 1:
            cargarDatos();
            break;

        case 2:
            organizarTorneo();
            break;

        case 3:
            simularMundial();
            break;

        case 4:
            mostrarMetricas();
            break;

        case 5:
            std::cout << "\nCerrando simulador...\n";
            break;

        default:
            std::cout << "\nOpción inválida.\n";
        }

    } while (opcion != 5);
}
