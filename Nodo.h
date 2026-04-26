#ifndef NODO_H
#define NODO_H

template <class T>
class Nodo {
private:
    T dato;
    Nodo<T>* siguiente;

public:
    Nodo(const T& valor) {
        dato = valor;
        siguiente = nullptr;
    }

    void setDato(const T& valor) {
        dato = valor;
    }

    T getDato() const {
        return dato;
    }

    void setSiguiente(Nodo<T>* sig) {
        siguiente = sig;
    }

    Nodo<T>* getSiguiente() const {
        return siguiente;
    }
};

#endif
