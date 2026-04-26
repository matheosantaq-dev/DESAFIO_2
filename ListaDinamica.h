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

    // Destructor: elimina nodos 
    ~ListaDinamica() {
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            Nodo<T>* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
    }

    // Insertar al final
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

    // Tamaño
    int getTamanio() const {
        return tamano;
    }

    // Acceso por índice
    T obtener(int indice) const {
        if (indice < 0 || indice >= tamano) return nullptr;

        Nodo<T>* temp = cabeza;
        for (int i = 0; i < indice; i++) {
            temp = temp->siguiente;
        }
        return temp->dato;
    }

    // Intercambiar elementos
    void intercambiar(int i, int j) {
        if (i < 0 || j < 0 || i >= tamano || j >= tamano) return;

        Nodo<T>* a = cabeza;
        Nodo<T>* b = cabeza;

        for (int k = 0; k < i; k++) a = a->siguiente;
        for (int k = 0; k < j; k++) b = b->siguiente;

        T temp = a->dato;
        a->dato = b->dato;
        b->dato = temp;
    }

    // Limpiar lista 
    void limpiar() {
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            Nodo<T>* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
        cabeza = nullptr;
        tamano = 0;
    }

    // Ordenar por ranking 
    void ordenarPorRanking() {
        for (int i = 0; i < tamano; i++) {
            for (int j = i + 1; j < tamano; j++) {

                Nodo<T>* a = cabeza;
                Nodo<T>* b = cabeza;

                for (int k = 0; k < i; k++) a = a->siguiente;
                for (int k = 0; k < j; k++) b = b->siguiente;

                if (a->dato->getRanking() > b->dato->getRanking()) {
                    T temp = a->dato;
                    a->dato = b->dato;
                    b->dato = temp;
                }
            }
        }
    }
};

#endif
