#include <iostream>
#include "GestorCSV.h"
#include "Torneo.h" // Asegúrate de tener tu clase Torneo bien definida
#include "Grupo.h"
#include "ListaDinamica.h"

int main() {
    std::cout << "Iniciando sistema de simulacion..." << std::endl;

    // 1. CARGA DE DATOS 
    GestorCSV gestor("data/selecciones_clasificadas_mundial.csv");
    ListaDinamica<Equipo*> equipos = gestor.cargarEquipos();

    if (equipos.getTamanio() == 0) {
        std::cerr << "Error: No se cargaron equipos. Revisa el archivo CSV." << std::endl;
        return 1;
    }

    
    //  clase Torneo que maneja los 12 grupos
    Torneo mundial;
    mundial.organizarBombos(equipos); 
    mundial.crearGrupos();           
    
    // 3. SIMULACIÓN
    std::cout << "Simulando fase de grupos..." << std::endl;
    mundial.simularFaseGrupos();

    // 4. RESULTADOS
    mundial.generarEstadisticas();

    // 5. LIMPIEZA
    // La memoria dinámica debería liberarse en los destructores de Torneo y ListaDinamica.
    std::cout << "\nSimulacion completada exitosamente." << std::endl;
    return 0;
}
