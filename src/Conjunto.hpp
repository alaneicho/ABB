
#include "Conjunto.h"

template <class T>
Conjunto<T>::Conjunto() : raiz_(nullptr), cantidad_(0) {
    // Completar
}

template <class T>
Conjunto<T>::~Conjunto() { 
    // Completar
}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    if (this->cantidad_ == 0){
        return false;
    }else if (this->raiz_->valor == clave){
        return true;
    } else if (clave < this->raiz_->valor){
        return (this->raiz_->izq != nullptr && this->raiz_->izq->perteneceSubarbol(clave));
    } else {
        return (this->raiz_->der != nullptr && this->raiz_->der->perteneceSubarbol(clave));
    }
}

template <class T>
void Conjunto<T>::insertar(const T& clave) {
    if (this->cantidad_ == 0){
        this->raiz_ = new Nodo(clave);
        this->cantidad_++;
        return;
    } else if (this->pertenece(clave)){
        return;
    } else {
        this->raiz_->meteloDondeVa(clave);
        this->cantidad_++;
        return;
    }
}

template <class T>
void Conjunto<T>::remover(const T& clave) {
    if (not this->pertenece(clave)){
        return;
    } else {
        //removerlo posta
        this->cantidad_--;
    }
}

template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    assert(false);
}

template <class T>
const T& Conjunto<T>::minimo() const {
    return this->raiz_->dameMinimo();
}

template <class T>
const T& Conjunto<T>::maximo() const {
    return this->raiz_->dameMaximo();
}

template <class T>
unsigned int Conjunto<T>::cardinal() const {
    return this->cantidad_;
}

template <class T>
void Conjunto<T>::mostrar(std::ostream&) const {
    assert(false);
}


