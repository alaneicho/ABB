
#include "Conjunto.h"

template <class T>
Conjunto<T>::Conjunto() : raiz_(nullptr), cantidad_(0) {
    // Completar
}

template <class T>
Conjunto<T>::~Conjunto() { 
    destruirNodo(this->raiz_);
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
        Nodo* nodo_byebye = this->raiz_->buscarPorClave(clave);
        nodo_byebye->removerNodo(*this);
        this->cantidad_--;
    }
}

template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    //Siguiendo la diapo 20 de la clase de implementacion de conjuntos sobre ABBs

    //Aca estoy parado en el nodo con la clave pasada por parametro
    Nodo* nodo_clave = this->raiz_->buscarPorClave(clave);

    if (nodo_clave->der != nullptr){                                  //Caso A
        return nodo_clave->der->dameMinimo();
    } else {                                                         //Caso B
        if(nodo_clave->padre->izq == nodo_clave){
            return nodo_clave->padre->valor;                          //Caso B.1
        } else {
            //"Subimos en el arbol hasta llegar a un nodo por su rama izquierda, y devolvemos ese elemento"
            return nodo_clave->subirHastaLlegarPorIzquierda()->valor;        //Caso B.2
        }
    }
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

template<class T>
void Conjunto<T>::destruirNodo(Conjunto::Nodo *nodo) {
    if (nodo->izq == nullptr && nodo->der == nullptr){      //es hoja
        if (nodo->padre->izq == nodo){         //es hijo izq
            nodo->padre->izq = nullptr;
        } else if (nodo->padre->der == nodo){   // es hijo der
            nodo->padre->der = nullptr;
        }
        delete nodo;
    } else {                                                // no es hoja
        if (nodo->izq != nullptr){
            this->destruirNodo(nodo->izq);
        }
        if (nodo->der != nullptr){
            this->destruirNodo(nodo->der);
        }
    }
}


