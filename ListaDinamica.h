#ifndef LISTADINAMICA_H
#define LISTADINAMICA_H

#include "Nodo.h"

template <typename T>
class ListaDinamica {
private:
    Nodo<T>* cabeza;
    int tamano;

public:
    // Constructor
    ListaDinamica() : cabeza(nullptr), tamano(0) {}

    // Constructor de copia
    ListaDinamica(const ListaDinamica<T>& otra)
        : cabeza(nullptr), tamano(0)
    {
        Nodo<T>* actual = otra.cabeza;

        while (actual != nullptr) {
            insertarAlFinal(actual->getDato());
            actual = actual->getSiguiente();
        }
    }

    // Operador de asignación
    ListaDinamica<T>& operator=(const ListaDinamica<T>& otra) {
        if (this != &otra) {
            limpiar();

            Nodo<T>* actual = otra.cabeza;

            while (actual != nullptr) {
                insertarAlFinal(actual->getDato());
                actual = actual->getSiguiente();
            }
        }

        return *this;
    }

    // Destructor
    ~ListaDinamica() {
        limpiar();
    }

    // Insertar al final
    void insertarAlFinal(T valor) {
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

    // Obtener elemento por índice
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

    // Ordenar por ranking FIFA (para punteros a Equipo)
    void ordenarPorRanking() {
        for (int i = 0; i < tamano; i++) {
            for (int j = i + 1; j < tamano; j++) {

                Nodo<T>* a = cabeza;
                Nodo<T>* b = cabeza;

                for (int k = 0; k < i; k++) {
                    a = a->getSiguiente();
                }

                for (int k = 0; k < j; k++) {
                    b = b->getSiguiente();
                }

                if (a->getDato()->getRanking() >
                    b->getDato()->getRanking()) {

                    T temp = a->getDato();
                    a->setDato(b->getDato());
                    b->setDato(temp);
                }
            }
        }
    }
};

#endif
