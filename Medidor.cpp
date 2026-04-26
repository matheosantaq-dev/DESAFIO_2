#include "Medidor.h"

// Inicialización
long long Medidor::iteraciones = 0;
long long Medidor::memoria = 0;

// Sumar iteración
void Medidor::it() {
    iteraciones++;
}

// Sumar memoria
void Medidor::add(size_t bytes) {
    memoria += bytes;
}

// Restar memoria
void Medidor::sub(size_t bytes) {
    memoria -= bytes;
}

// Reiniciar
void Medidor::reset() {
    iteraciones = 0;
    memoria = 0;
}

// Mostrar
void Medidor::print() {
    std::cout << "\n=========== MÉTRICAS DEL SISTEMA ===========\n";
    std::cout << "Iteraciones totales: " << iteraciones << "\n";
    std::cout << "Memoria utilizada:   " << memoria << " bytes\n";

    double kb = memoria / 1024.0;
    double mb = kb / 1024.0;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Memoria en KB:       " << kb << " KB\n";
    std::cout << "Memoria en MB:       " << mb << " MB\n";
    std::cout << "============================================\n";
}
