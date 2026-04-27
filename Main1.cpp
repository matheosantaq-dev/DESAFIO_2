#include "Menu.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {

    
    srand(static_cast<unsigned>(time(nullptr)));

    std::cout << "=== INICIANDO PROGRAMA ===\n";

    try {
        Menu menu;
        menu.iniciar();
    }
    catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << "\n";
    }
    catch (...) {
        std::cerr << "ERROR desconocido.\n";
    }

    std::cout << "=== FIN DEL PROGRAMA ===\n";
    return 0;
}

