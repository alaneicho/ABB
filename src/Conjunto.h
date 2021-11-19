#ifndef CONJUNTO_H_
#define CONJUNTO_H_

#include <assert.h>
#include <string>
#include <iostream>

using namespace std;

template <class T>
class Conjunto
{
    public:

        // Constructor. Genera un conjunto vacío.
        Conjunto();

        // Destructor. Debe dejar limpia la memoria.
        ~Conjunto();

        // Inserta un elemento en el conjunto. Si este ya existe,
        // el conjunto no se modifica.
        void insertar(const T&);

        // Decide si un elemento pertenece al conjunto o no.
        bool pertenece(const T&) const;

        // Borra un elemento del conjunto. Si este no existe,
        // el conjunto no se modifica.
        void remover(const T&);

        // Siguiente elemento al recibido por párametro, en orden.
        const T& siguiente(const T& elem);

        // Devuelve el mínimo elemento del conjunto según <.
        const T& minimo() const;

        // Devuelve el máximo elemento del conjunto según <.
        const T& maximo() const;

        // Devuelve la cantidad de elementos que tiene el conjunto.
        unsigned int cardinal() const;

        // Muestra el conjunto.
        void mostrar(std::ostream&) const;

    private:

        /**
         * Completar con lo que sea necesario...
         **/

        struct Nodo
        {
            // El constructor, toma el elemento al que representa el nodo.
            Nodo(const T& v);
            // El elemento al que representa el nodo.
            T valor;
            // Puntero a la raíz del subárbol izquierdo.
            Nodo* izq;
            // Puntero a la raíz del subárbol derecho.
            Nodo* der;

            // Decide si un elemento pertenece al subarbol que tiene como raiz al nodo o no.
            bool perteneceSubarbol(const T& clave) const;
            void meteloDondeVa(const T& clave);
            const T& dameMinimo() const;
            const T& dameMaximo() const;
        };

        // Puntero a la raíz de nuestro árbol.
        Nodo* raiz_;
        unsigned int cantidad_;

};

template<class T>
Conjunto<T>::Nodo::Nodo(const T &v) : valor(v) , izq(nullptr), der(nullptr) {
}

template<class T>
bool Conjunto<T>::Nodo::perteneceSubarbol(const T & clave) const {
    if (this->valor == clave){
        return true;
    } else if (clave < this->valor){
        return (this->izq != nullptr && this->izq->perteneceSubarbol(clave));
    } else {
        return (this->der != nullptr && this->der->perteneceSubarbol(clave));
    }
}

template<class T>
void Conjunto<T>::Nodo::meteloDondeVa(const T &clave) {

    if (clave < this->valor){
        if (this->izq == nullptr){
            Nodo* nuevo_nodo = new Nodo(clave);
            this->izq = nuevo_nodo;
        } else {
            this->izq->meteloDondeVa(clave);
        }
    } else if (clave > this->valor){
        if (this->der == nullptr){
            Nodo* nuevo_nodo = new Nodo(clave);
            this->der = nuevo_nodo;
        } else {
            this->der->meteloDondeVa(clave);
        }
    }
}

template<class T>
const T& Conjunto<T>::Nodo::dameMinimo() const {
    if (this->izq == nullptr){
        return this->valor;
    } else {
        return this->izq->dameMinimo();
    }
}

template<class T>
const T& Conjunto<T>::Nodo::dameMaximo() const {
    if (this->der == nullptr){
        return this->valor;
    } else {
        return this->der->dameMaximo();
    }
}

template<class T>
std::ostream& operator<<(std::ostream& os, const Conjunto<T>& c) {
	 c.mostrar(os);
	 return os;
}

#include "Conjunto.hpp"

#endif // CONJUNTO_H_
