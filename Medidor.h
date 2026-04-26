#ifndef MEDIDOR_H
#define MEDIDOR_H

#include <iostream>
#include <iomanip>

class Medidor {
public:
    // Variables globales
    static long long iteraciones;
    static long long memoria;

    // Control de iteraciones
    static void it();

    // Control de memoria
    static void add(size_t bytes);
    static void sub(size_t bytes);

    // Reiniciar métricas
    static void reset();

    // Mostrar resultados
    static void print();
};

#endif
