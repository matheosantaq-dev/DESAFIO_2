#include <iostream>
#include <ctime>   
#include <cstdlib> 
#include "GestorCSV.h"
#include "Torneo.h"
#include "Grupo.h"
#include "ListaDinamica.h"
#include "Equipo.h"

int main() {
    
    srand(static_cast<unsigned int>(time(0)));

    std::cout << "==========================================" << std::endl;
    std::cout << "   SISTEMA DE SIMULACION UDEA WORLD CUP   " << std::endl;
    std::cout << "==========================================" << std::endl;

    // 1. CARGA DE DATOS 
    
    GestorCSV gestor("data/selecciones_clasificadas_mundial.csv");
    ListaDinamica<Equipo*> equipos = gestor.cargarEquipos();

    // Verificación de carga
    int totalEquipos = equipos.getTamanio();
    if (totalEquipos == 0) {
        std::cerr << "[ERROR]: No se cargaron equipos. Verifica que el archivo CSV existe en la carpeta 'data'." << std::endl;
        return 1;
    }

    std::cout << "[INFO]: Se han cargado " << totalEquipos << " equipos exitosamente." << std::endl;

    // 2. CONFIGURACIÓN DEL TORNEO
    Torneo mundial;

    // Distribuir equipos en los 4 bombos (12 equipos por bombo)
    std::cout << "[INFO]: Organizando bombos..." << std::endl;
    mundial.organizarBombos(equipos); 

    // Crear los 12 grupos y asignar un equipo de cada bombo a cada grupo
    std::cout << "[INFO]: Creando grupos y organizando encuentros..." << std::endl;
    mundial.crearGrupos();           
    
    // 3. SIMULACIÓN
    std::cout << "\n[SIMULACION]: Iniciando fase de grupos..." << std::endl;
    mundial.simularFaseGrupos();
    std::cout << "[OK]: Simulacion de partidos completada." << std::endl;

    // 4. RESULTADOS Y ESTADÍSTICAS
    
    mundial.generarEstadisticas();

    // 5. LIMPIEZA Y CIERRE
    // El destructor de 'mundial' se encargará de liberar los Grupos.
    // El destructor de cada 'Grupo' liberará sus Partidos.
    // Los Equipos suelen liberarse al final si fueron creados en el GestorCSV.
    
    std::cout << "\n==========================================" << std::endl;
    std::cout << "      SIMULACION FINALIZADA CON EXITO     " << std::endl;
    std::cout << "==========================================" << std::endl;

    return 0;
}
