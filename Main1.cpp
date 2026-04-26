#include <iostream>
#include <ctime>
#include <cstdlib>

#include "GestorCSV.h"
#include "Torneo.h"
#include "Grupo.h"
#include "ListaDinamica.h"
#include "Equipo.h"
#include "Medidor.h"

int main() {

    srand(static_cast<unsigned int>(time(0)));

    std::cout << "==========================================\n";
    std::cout << "   SISTEMA DE SIMULACION UDEA WORLD CUP   \n";
    std::cout << "==========================================\n";

    
    // 1. CARGA DE DATOS
  
    GestorCSV gestor("data/selecciones_clasificadas_mundial.csv");
    ListaDinamica<Equipo*> equipos = gestor.cargarEquipos();

    int totalEquipos = equipos.getTamanio();

    if (totalEquipos == 0) {
        std::cerr << "[ERROR]: No se cargaron equipos.\n";
        return 1;
    }

    std::cout << "[INFO]: Se cargaron " << totalEquipos << " equipos.\n";

    
    // 2. CONFIGURACIÓN DEL TORNEO

    Torneo mundial;

    std::cout << "[INFO]: Organizando bombos...\n";
    mundial.organizarBombos(equipos);

    std::cout << "[INFO]: Creando grupos...\n";
    mundial.crearGrupos();

   
    // 3. SIMULACIÓN
 
    std::cout << "\n[SIMULACION]: Fase de grupos...\n";
    mundial.simularFaseGrupos();

    std::cout << "[OK]: Simulación completada.\n";

    // 4. RESULTADOS
 
    mundial.generarEstadisticas();


    // 5. MÉTRICAS 

    std::cout << "\n[MEDICION]\n";
    std::cout << "Memoria usada: " << Medidor::getMemoria() << " bytes\n";
    std::cout << "Iteraciones: " << Medidor::getIteraciones() << "\n";

 
    // 6. LIBERAR MEMORIA 

    for (int i = 0; i < equipos.getTamanio(); i++) {
        Equipo* e = equipos.obtener(i);
        if (e) delete e;
    }

    std::cout << "\n==========================================\n";
    std::cout << "      SIMULACION FINALIZADA CON EXITO     \n";
    std::cout << "==========================================\n";

    return 0;
}
    std::cout << "==========================================" << std::endl;

    return 0;
}
