#ifndef LISTADINAMICA_H
#define LISTADINAMICA_H

#include "Nodo.h"
#include <iostream>

template <typename T>
class ListaDinamica {
private:
    Nodo<T>* cabeza;
    int tamano;

public:
    // Constructor
    ListaDinamica() : cabeza(nullptr), tamano(0) {}

    // Constructor copia
    ListaDinamica(const ListaDinamica<T>& otra) {
        cabeza = nullptr;
        tamano = 0;

        Nodo<T>* actual = otra.cabeza;
        while (actual != nullptr) {
            insertarAlFinal(actual->getDato());
            actual = actual->getSiguiente();
        }
    }

    // Destructor
    ~ListaDinamica() {
        limpiar();
    }

    // Insertar al final
    void insertarAlFinal(const T& valor) {
        Nodo<T>* nuevoNodo = new Nodo<T>(valor);

        if (cabeza == nullptr) {
            cabeza = nuevoNodo;
        } else {
            Nodo<T>* temp = cabeza;
            while (temp->getSiguiente() != nullptr) {
                temp = temp->getSiguiente();
            }
            temp->setSiguiente(nuevoNodo);
        }

        tamano++;
    }

    // Obtener tamaño
    int getTamanio() const {
        return tamano;
    }

    // Verificar si está vacía
    bool estaVacia() const {
        return cabeza == nullptr;
    }

    // Obtener por índice
    T obtener(int indice) const {
        if (indice < 0 || indice >= tamano) {
            return T();
        }

        Nodo<T>* temp = cabeza;
        for (int i = 0; i < indice; i++) {
            temp = temp->getSiguiente();
        }

        return temp->getDato();
    }

    // Intercambiar elementos
    void intercambiar(int i, int j) {
        if (i < 0 || j < 0 || i >= tamano || j >= tamano || i == j) {
            return;
        }

        Nodo<T>* nodoI = cabeza;
        Nodo<T>* nodoJ = cabeza;

        for (int k = 0; k < i; k++) {
            nodoI = nodoI->getSiguiente();
        }

        for (int k = 0; k < j; k++) {
            nodoJ = nodoJ->getSiguiente();
        }

        T temp = nodoI->getDato();
        nodoI->setDato(nodoJ->getDato());
        nodoJ->setDato(temp);
    }

    // Limpiar lista
    void limpiar() {
        Nodo<T>* actual = cabeza;

        while (actual != nullptr) {
            Nodo<T>* siguiente = actual->getSiguiente();
            delete actual;
            actual = siguiente;
        }

        cabeza = nullptr;
        tamano = 0;
    }

    // Ordenar por ranking FIFA 
    void ordenarPorRanking() {
        if (tamano < 2) return;

        for (int i = 0; i < tamano - 1; i++) {
            for (int j = i + 1; j < tamano; j++) {
                T datoI = obtener(i);
                T datoJ = obtener(j);

                if (datoI->getRanking() > datoJ->getRanking()) {
                    intercambiar(i, j);
                }
            }
        }
    }

    // Sobrecarga operador []
    T operator[](int indice) const {
        return obtener(indice);
    }
};

#endif
