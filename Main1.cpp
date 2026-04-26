#include "Menu.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    std::cout << "=== INICIANDO PROGRAMA ===\n";

    
    srand(time(0));

    try {
        Menu menu;
        menu.iniciar();
    }
    catch (...) {
        std::cerr << "ERROR: El programa crasheó.\n";
    }

    std::cout << "=== FIN DEL PROGRAMA ===\n";
    return 0;
}
