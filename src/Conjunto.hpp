
#include "Conjunto.h"

template <class T>
Conjunto<T>::Conjunto() : _raiz(nullptr), cantidad_(0) {
    // Completar
}

template <class T>
Conjunto<T>::~Conjunto() { 
    // Completar
}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    if (this->_raiz->valor == clave){
        return true;
    } else if (clave < this->_raiz->valor){
        return (this->_raiz->izq != nullptr && this->_raiz->izq->perteneceSubarbol(clave));
    } else {
        return (this->_raiz->der != nullptr && this->_raiz->der->perteneceSubarbol(clave));
    }
}

template <class T>
void Conjunto<T>::insertar(const T& clave) {
    assert(false);
}

template <class T>
void Conjunto<T>::remover(const T&) {
    assert(false);
}

template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    assert(false);
}

template <class T>
const T& Conjunto<T>::minimo() const {
    assert(false);
}

template <class T>
const T& Conjunto<T>::maximo() const {
    assert(false);
}

template <class T>
unsigned int Conjunto<T>::cardinal() const {
    assert(false);
    return 0;
}

template <class T>
void Conjunto<T>::mostrar(std::ostream&) const {
    assert(false);
}


