#ifndef CONJUNTO_H_
#define CONJUNTO_H_

#include <assert.h>
#include <string>
#include <iostream>

using namespace std;

template<class T>
class Conjunto {
public:

    // Constructor. Genera un conjunto vacío.
    Conjunto();

    // Destructor. Debe dejar limpia la memoria.
    ~Conjunto();

    // Inserta un elemento en el conjunto. Si este ya existe,
    // el conjunto no se modifica.
    void insertar(const T &);

    // Decide si un elemento pertenece al conjunto o no.
    bool pertenece(const T &) const;

    // Borra un elemento del conjunto. Si este no existe,
    // el conjunto no se modifica.
    void remover(const T &);

    // Siguiente elemento al recibido por párametro, en orden.
    // Se asume que el elemento recibido se encuentra en el conjunto y existe un elemento siguiente.
    const T &siguiente(const T &elem);

    // Devuelve el mínimo elemento del conjunto según <.
    const T &minimo() const;

    // Devuelve el máximo elemento del conjunto según <.
    const T &maximo() const;

    // Devuelve la cantidad de elementos que tiene el conjunto.
    unsigned int cardinal() const;

    // Muestra el conjunto.
    void mostrar(std::ostream &) const;

private:

    /**
     * Completar con lo que sea necesario...
     **/

    struct Nodo {
        // El constructor, toma el elemento al que representa el nodo.
        Nodo(const T &v);

        // El elemento al que representa el nodo.
        T valor;
        // Puntero a la raíz del subárbol izquierdo.
        Nodo *izq;
        // Puntero a la raíz del subárbol derecho.
        Nodo *der;

        //Puntero al padre del nodo
        Nodo *padre;

        // Decide si un elemento pertenece al subarbol que tiene como raiz al nodo o no.
        bool perteneceSubarbol(const T &clave) const;

        void meteloDondeVa(const T &clave);

        Nodo *buscarPorClave(const T &clave);

        const Nodo *subirHastaLlegarPorIzquierda() const;

        const T &dameMinimo() const;

        const T &dameMaximo() const;

        void removerDeSubarbol(const T &clave);

        void removerNodo(Conjunto<T> &c);

        void removerNodoHoja();

        void removerNodoConUnSoloHijo();

        void removerNodoConDosHijos(Conjunto<T> &c);

        void destruirHoja();

        void destruirHaciaAbajo();

    };

    void destruirNodo(Nodo *nodo);

    Nodo *buscarPorClave(const T &clave);


    // Puntero a la raíz de nuestro árbol.
    Nodo *raiz_;

    //cardinal del conjunto en O(1), porque se me canto.
    unsigned int cantidad_;

};

template<class T>
Conjunto<T>::Nodo::Nodo(const T &v) : valor(v), izq(nullptr), der(nullptr), padre(nullptr) {
}

template<class T>
bool Conjunto<T>::Nodo::perteneceSubarbol(const T &clave) const {

    if (this->valor == clave) {
        return true;
    } else if (clave < this->valor) {
        return (this->izq != nullptr && this->izq->perteneceSubarbol(clave));
    } else {
        return (this->der != nullptr && this->der->perteneceSubarbol(clave));
    }
}

template<class T>
void Conjunto<T>::Nodo::meteloDondeVa(const T &clave) {

    if (clave < this->valor) {
        if (this->izq == nullptr) {
            Nodo *nuevo_nodo = new Nodo(clave);
            nuevo_nodo->padre = this;
            this->izq = nuevo_nodo;
        } else {
            this->izq->meteloDondeVa(clave);
        }
    } else if (clave > this->valor) {
        if (this->der == nullptr) {
            Nodo *nuevo_nodo = new Nodo(clave);
            nuevo_nodo->padre = this;
            this->der = nuevo_nodo;
        } else {
            this->der->meteloDondeVa(clave);
        }
    }
}

template<class T>
const T &Conjunto<T>::Nodo::dameMinimo() const {
    if (this->izq == nullptr) {
        return this->valor;
    } else {
        return this->izq->dameMinimo();
    }
}

template<class T>
const T &Conjunto<T>::Nodo::dameMaximo() const {
    if (this->der == nullptr) {
        return this->valor;
    } else {
        return this->der->dameMaximo();
    }
}

//Precond: la clave esta en el subarbol
// Encuentra el nodo a remover y llama a removerNodo
template<class T>
void Conjunto<T>::Nodo::removerDeSubarbol(const T &clave) {
    if (this->valor == clave) {
        this->removerNodo();
    } else if (clave < this->valor) {
        this->izq->removerDeSubarbol(clave);
    } else if (clave > this->valor) {
        this->der->removerDeSubarbol(clave);
    }
}

//Efectivamente se encarga de remover el nodo
template<class T>
void Conjunto<T>::Nodo::removerNodo(Conjunto<T> &c) {
    if (this->izq == nullptr && this->der == nullptr) {          // Caso hoja
        this->removerNodoHoja();
    } else if (this->izq == nullptr || this->der == nullptr) {   // Caso un solo hijo
        this->removerNodoConUnSoloHijo();
    } else {                                                    // Caso dos hijos
        this->removerNodoConDosHijos(c);
    }
}

template<class T>
void Conjunto<T>::Nodo::removerNodoHoja() {
    if (this->padre == nullptr) {            //caso raiz
        delete this;
        return;
    } else if (this->padre->izq == this) {   //caso "Hoja izquierda"
        this->padre->izq = nullptr;
    } else if (this->padre->der == this) {   //caso "Hoja derecha"
        this->padre->der = nullptr;
    }
    delete this;
}

template<class T>
void Conjunto<T>::Nodo::removerNodoConUnSoloHijo() {
    // Ponemos al hijo del nodo a borrar bajo su "abuelo" (padre del nodo a borrar)
    Nodo *hijo;
    if (this->izq != nullptr) {
        hijo = this->izq;
    } else if (this->der != nullptr) {
        hijo = this->der;
    }
    hijo->padre = this->padre;

    if (this->padre->izq == this) {          //caso "Hijo izquierdo"
        this->padre->izq = hijo;
    } else if (this->padre->der == this) {   //caso "Hijo derecho"
        this->padre->der = hijo;
    }
    //Borremos efectrivamente el nodo:
    delete this;
}

template<class T>
void Conjunto<T>::Nodo::removerNodoConDosHijos(Conjunto<T> &c) {
    //Los que pueden ocupar su lugar son: su inmediato sucesor, o su inmediato predecesor.

    //Si NO es el maximo, entonces tiene inmediato sucesor, usaremos ese:
    if (this->valor < c.maximo()) {


        Nodo *sucesor = c.buscarPorClave(c.siguiente(this->valor));
        this->valor = c.siguiente(this->valor);


        /**
        Nodo *reemplazo = new Nodo(c.siguiente(this->valor));
        reemplazo->izq = this->izq;
        reemplazo->der = this->der;
        if (this->padre != nullptr) {
            reemplazo->padre = this->padre;
        }**/

        sucesor->removerNodo(c);
    } else if (this->valor == c.maximo()) {
        //Si es el maximo del conjunto, es el que mas a la derecha esta, asique no puede tener hijo derecho.
        //... osea, a este if nunca se deberia entrar.
        this->removerNodo(c);   //Notar que aca caera en el caso "hoja" o en el caso "un hijo"(el izq)
    }


}

//Busca y devuelve el nodo con la clave pasada por parametro, en el subarbol que tiene como raiz a this.
//Precond: la clave esta en el subarbol.
template<class T>
typename Conjunto<T>::Nodo *Conjunto<T>::Nodo::buscarPorClave(const T &clave) {
    if (this->valor == clave) {
        return this;
    } else if (this->valor < clave) {
        return this->der->buscarPorClave(clave);
    } else if (this->valor > clave) {
        return this->izq->buscarPorClave(clave);
    }
}

//"Subimos en el arbol hasta llegar a un nodo por su rama izquierda, y devolvemos ese NODO"
template<class T>
const typename Conjunto<T>::Nodo *Conjunto<T>::Nodo::subirHastaLlegarPorIzquierda() const {
    if (this->padre->izq == this) {
        return this->padre;
    } else {
        return this->padre->subirHastaLlegarPorIzquierda();
    }
}

template<class T>
void Conjunto<T>::Nodo::destruirHoja() {
    if (this->padre->izq == this) {  // es hijo izq
        this->padre->izq = nullptr;
    } else if (this->padre->der == this) { // es hijo der

    }
}

template<class T>
void Conjunto<T>::Nodo::destruirHaciaAbajo() {
    this->padre = nullptr;
    if (this->izq != nullptr) {
        Nodo *izquierdo = this->izq;
        izquierdo->destruirHaciaAbajo();
    }
    if (this->der != nullptr) {
        Nodo *derecho = this->der;
        derecho->destruirHaciaAbajo();
    }
    delete this;
}

/**
//Destruye el ABB desde la raiz
template<class T>
void Conjunto<T>::destruirHaciaAbajo(Nodo *nodo){
    nodo->padre = nullptr;
    if (nodo->izq != nullptr){
        this->destruirHaciaAbajo(nodo->izq);
    }
    if (nodo->der != nullptr){
        this->destruirHaciaAbajo(nodo->der);
    }
    delete nodo;
}**/


template<class T>
std::ostream &operator<<(std::ostream &os, const Conjunto<T> &c) {
    c.mostrar(os);
    return os;
}

#include "Conjunto.hpp"

#endif // CONJUNTO_H_
