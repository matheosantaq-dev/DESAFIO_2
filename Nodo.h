#ifndef NODO_H
#define NODO_H

template <class T>
class Nodo {
private:
    T dato;
    Nodo<T>* siguiente;

public:
    // Constructor
    Nodo(const T& valor) : dato(valor), siguiente(nullptr) {}

    // Constructor copia
    Nodo(const Nodo<T>& otro) : dato(otro.dato), siguiente(nullptr) {}

    // Destructor
    ~Nodo() {}

    // Getters
    T getDato() const {
        return dato;
    }

    Nodo<T>* getSiguiente() const {
        return siguiente;
    }

    // Setters
    void setDato(const T& valor) {
        dato = valor;
    }

    void setSiguiente(Nodo<T>* sig) {
        siguiente = sig;
    }
};

#endif
