#include "Menu.h"
#include "Medidor.h"
#include <iostream>

Menu::Menu()
    : gestor("selecciones_clasificadas_mundial.csv") // 🔥 PATH RELATIVO
{
}

// Destructor
Menu::~Menu() {
    liberarMemoria();
}

// Banner
void Menu::mostrarBanner() const {
    std::cout << "\n=========================================\n";
    std::cout << "   SIMULADOR COPA MUNDIAL FIFA 2026\n";
    std::cout << "=========================================\n";
}

// Opciones
void Menu::mostrarOpciones() const {
    std::cout << "\n1. Cargar selecciones\n";
    std::cout << "2. Organizar torneo\n";
    std::cout << "3. Simular mundial\n";
    std::cout << "4. Métricas\n";
    std::cout << "5. Salir\n";
    std::cout << "Opción: ";
}


void Menu::cargarDatos() {
    equipos = gestor.cargarEquipos();

    std::cout << "\nEquipos cargados: "
              << equipos.getTamanio() << "\n";

    if (equipos.getTamanio() < 48) {
        std::cout << "⚠ ERROR: CSV no cargado correctamente\n";
    }
}


void Menu::organizarTorneo() {
    if (equipos.getTamanio() < 48) {
        std::cout << "\n❌ ERROR: faltan equipos ("
                  << equipos.getTamanio() << ")\n";
        return;
    }

    torneo.organizarBombos(equipos);
    torneo.crearGrupos();

    std::cout << "\nGrupos creados correctamente\n";
}

// Simular
void Menu::simularMundial() {
    if (torneo.getGrupos().getTamanio() == 0) {
        std::cout << "\n❌ Debe organizar el torneo primero\n";
        return;
    }

    torneo.simularFaseGrupos();
    torneo.simularEliminatorias();
    torneo.generarEstadisticas();
}

// Métricas
void Menu::mostrarMetricas() {
    Medidor::print();
}

// Liberar memoria
void Menu::liberarMemoria() {
    for (int i = 0; i < equipos.getTamanio(); i++) {
        delete equipos.obtener(i);
    }
    equipos.limpiar();
}

// Loop principal
void Menu::iniciar() {
    int opcion;

    do {
        mostrarBanner();
        mostrarOpciones();
        std::cin >> opcion;

        switch (opcion) {
        case 1: cargarDatos(); break;
        case 2: organizarTorneo(); break;
        case 3: simularMundial(); break;
        case 4: mostrarMetricas(); break;
        case 5: std::cout << "Saliendo...\n"; break;
        default: std::cout << "Opción inválida\n";
        }

    } while (opcion != 5);
}
