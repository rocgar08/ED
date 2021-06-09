/**
NOMBRE Y APELLIDOS INTEGRANTE 1:
NOMBRE Y APELLIDOS INTEGRANTE 2:
GRUPO: 
*/


/**
@file Cola.h

Implementación del TAD Cola utilizando una
lista enlazada de nodos.

Estructura de Datos y Algoritmos
Facultad de Informática
Universidad Complutense de Madrid

(c) Marco Antonio Gómez Martín, 2012   Mercedes Gómez Albarrán, 2021
*/
#ifndef __COLA_LISTA_ENLAZADA_H
#define __COLA_LISTA_ENLAZADA_H
#include <cstddef>
#include <iostream>

/// Excepciones generadas por algunos métodos
class EColaVacia {};

//Excepción que se levanta si se especifica
//una posición inválida para la operación
//llevarAlPrincipio. 
class EPosicionInvalida {};

/**
Implementación del TAD Cola utilizando una lista enlazada.

Las operaciones son:

- ColaVacia: -> Cola. Generadora implementada en el
constructor sin parámetros.
- pon: Cola, Elem -> Cola. Generadora
- quita: Cola - -> Cola. Modificadora parcial.
- primero: Cola - -> Elem. Observadora parcial.
- esVacia: Cola -> Bool. Observadora.
- longitud: unsigned int. Devuelve el número de elementos
- print: Cola -->  . Observadora
de la cola.

@author Marco Antonio Gómez Martín   Mercedes Gómez Albarrán
*/
template <class T>
class Cola {
public:

	

	/**
	Desplaza un nodo, identificado por su posición, al principio de la cola.
	En una cola no vacía, las posiciones válidas varían entre 1 y 
	la longitud de la cola.
	En caso de que la posición del nodo no sea válida, se levantará
	la excepción EPosicionInvalida.
	@param pos Posición del nodo a desplazar.
	**/

	
	// COMPLEJIDAD: 
	// Incluye aquí un comentario donde, justificadamente, indiques la complejidad de esta operación
	

	void llevarAlFinal(unsigned int pos) {

		// A IMPLEMENTAR
		if (esVacia() || pos <= 0 || pos > longitud()) throw EPosicionInvalida();

		Nodo* act = _prim; // ini
		Nodo* ant = NULL;
		Nodo* aMover = NULL;
		Nodo* fin = _ult;
	
		unsigned int cont = 1;
		if (esVacia() || pos <= 0 || pos > longitud()) throw EPosicionInvalida();

		if (pos < longitud()) {
	
			while (cont <= pos) {
				if (cont == pos) {
					aMover = ant->_sig;

				}
				else ant = act->_sig;
				cont++;
			}

			if (aMover == _prim) {
				_prim = ant;
				fin->_sig = aMover;
				_ult = aMover;
				aMover->_sig = NULL;
				
			}
			else {
				ant->_sig = aMover->_sig;
				fin->_sig = aMover;
				_ult = aMover;
				aMover->_sig = NULL;			
			}
		}

	}

	
	/** 
	Imprime la cola por pantalla.
	Operación observadora.
	*/
	void print() const {
		if (_prim != NULL) {
			Nodo* aux = _prim;
			while (aux != _ult) {
				std::cout << aux->_elem << " ";
				aux = aux->_sig;
			}
			std::cout << aux->_elem;
			std::cout << std::endl;
		}
	}



	/** Constructor; operacion ColaVacia */
	Cola() : _prim(NULL), _ult(NULL), _nelems(0) {
	}


	/**
	Añade un elemento en la parte trasera de la cola.
	Operación generadora.

	@param elem Elemento a añadir.
	*/
	void pon(const T &elem) {
		Nodo *nuevo = new Nodo(elem);
		if (esVacia()) _prim = nuevo;
		else _ult->_sig = nuevo;
		_ult = nuevo;
		_nelems++;
	}

	/**
	Elimina el primer elemento de la cola.
	Operación modificadora parcial.

	error: falla si la cola está vacía
	*/
	void quita() {
		if (esVacia())
			throw EColaVacia();
		Nodo *aBorrar = _prim;
		if (_prim == _ult)
			_prim = _ult = NULL;
		else
			_prim = _prim->_sig;
		delete aBorrar;
		_nelems--;
	}

	/**
	Devuelve el primer elemento de la cola. Operación
	observadora parcial.

	error: falla si la cola está vacía
	@return El primer elemento de la cola.
	*/
	const T &primero() const {
		if (esVacia())
			throw EColaVacia();
		return _prim->_elem;
	}

	/**
	Indica si la cola tiene elementos o no.

	@return true si la cola no tiene ningún elemento.
	*/
	bool esVacia() const {
		return _prim == NULL;
	}

	/**
	Devuelve el número de elementos de la cola.

	@return Número de elementos de la cola.
	*/
	unsigned int longitud() const {
		return _nelems;
	}

	/** Destructor; elimina la lista enlazada. */
	~Cola() {
		libera();
		_prim = _ult = NULL;
	}


	/** Constructor copia */
	Cola(const Cola<T> &other) : _prim(NULL), _ult(NULL) {
		copia(other);
	}

	/** Operador de asignación */
	Cola<T> &operator=(const Cola<T> &other) {
		if (this != &other) {
			libera();
			copia(other);
		}
		return *this;
	}

	/** Operador de comparación. */
	bool operator==(const Cola<T> &rhs) const {
		Nodo *p1 = _prim;
		Nodo *p2 = rhs._prim;
		while ((p1 != NULL) && (p2 != NULL) && (p1->_elem == p2->_elem)) {
			p1 = p1->_sig;
			p2 = p2->_sig;
		}
		return (p1 == NULL) && (p2 == NULL);
	}

	bool operator!=(const Cola<T> &rhs) const {
		return !(*this == rhs);
	}


private:

	/**
	Clase nodo que almacena internamente el elemento (de tipo T),
	y un puntero al nodo siguiente, que podría ser NULL si
	el nodo es el último de la lista enlazada.
	*/
	class Nodo {
	public:
		Nodo() : _sig(NULL) {}
		Nodo(const T &elem) : _elem(elem), _sig(NULL) {}
		Nodo(const T &elem, Nodo *sig) :
			_elem(elem), _sig(sig) {}

		T _elem;
		Nodo *_sig;
	};


	/**
	Genera una copia de other en la cola receptora
	*/
	void copia(const Cola &other) {
		if (other.esVacia())
			_prim = _ult = NULL;
		else {
			Nodo *puntAOrigen = other._prim;
			Nodo *ultimo;
			_prim = new Nodo(puntAOrigen->_elem);
			ultimo = _prim;
			while (puntAOrigen->_sig != NULL) {
				puntAOrigen = puntAOrigen->_sig;
				ultimo->_sig = new Nodo(puntAOrigen->_elem);
				ultimo = ultimo->_sig;
			}
			_ult = ultimo;
		}
		_nelems = other._nelems;
	}


	/**
	Elimina todos los nodos de la lista enlazada que soporta la cola.
	*/
	void libera() {
		while (_prim != NULL) {
			Nodo *aBorrar = _prim;
			_prim = _prim->_sig;
			delete aBorrar;
		}
	}


	/** Puntero al primer elemento. */
	Nodo *_prim;

	/** Puntero al último elemento. */
	Nodo *_ult;

	/** Número de elementos */
	unsigned int _nelems;
};

#endif // __PILA_LISTA_ENLAZADA_H


	
