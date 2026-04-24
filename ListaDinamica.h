#ifndef LISTADINAMICA_H
#define LISTADINAMICA_H

#include "Nodo.h"

template <typename T>
class ListaDinamica {
private:
    Nodo<T>* cabeza;
    int tamano;

public:
    ListaDinamica() : cabeza(nullptr), tamano(0) {}

    // Destructorv donde limpia la memoria de todos los nodos
    ~ListaDinamica() {
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            Nodo<T>* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
    }

    void insertarAlFinal(T valor) {
        Nodo<T>* nuevoNodo = new Nodo<T>(valor);
        if (cabeza == nullptr) {
            cabeza = nuevoNodo;
        } else {
            Nodo<T>* temp = cabeza;
            while (temp->siguiente != nullptr) {
                temp = temp->siguiente;
            }
            temp->siguiente = nuevoNodo;
        }
        tamano++;
    }

    int getTamanio() const {
        return tamano;
    }

    // Acceso por índice para recorrer la lista fácilmente
    T obtener(int indice) {
        Nodo<T>* temp = cabeza;
        for (int i = 0; i < indice; i++) {
            if (temp != nullptr) temp = temp->siguiente;
        }
        return (temp != nullptr) ? temp->dato : nullptr;
    }
};

#endif
