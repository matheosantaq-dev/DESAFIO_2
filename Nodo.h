#ifndef NODO_H
#define NODO_H

template <typename T>
struct Nodo {
    T dato;
    Nodo<T>* siguiente;

    Nodo(T valor) : dato(valor), siguiente(nullptr) {}
};

#endif
