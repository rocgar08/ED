// NOMBRE Y APELLIDOS:
// USUARIO DEL JUEZ:

/**
  @file Pila.h

  Implementaci�n del TAD Pila utilizando una
  lista enlazada simple de nodos.

  Estructura de Datos y Algoritmos
  Facultad de Inform�tica
  Universidad Complutense de Madrid

 (c) Marco Antonio G�mez Mart�n, 2012  Mercedes G�mez Albarr�n, 2016
*/
#ifndef __PILA_LISTA_ENLAZADA_H
#define __PILA_LISTA_ENLAZADA_H
#include <cstddef>

/// Excepciones generadas por algunos m�todos
class EPilaVacia {};

/**
 Implementaci�n del TAD Pila utilizando una lista enlazada de nodos.

 Las operaciones son:

 - PilaVacia: -> Pila. Generadora implementada en el
   constructor sin par�metros.
 - apila: Pila, Elem -> Pila. Generadora
 - desapila: Pila - -> Pila. Modificadora parcial.
 - cima: Pila - -> Elem. Observadora parcial.
 - esVacia: Pila -> Bool. Observadora.

 @author Marco Antonio G�mez Mart�n  Mercedes G�mez Albarr�n
 */

template <class T>
class Pila {
public:

	/** INDICA AQU� JUSTIFICADAMENTE LA COMPLEJIDAD DE LA OPERACI�N minimoACima

	**/
	/*void invertirPila(Pila<T>& aInvertir) {

	}
	void entreMezclar(Pila<T>& aMezclar) {

	}
	void maximoACima() {
		if (!esVacia()) {
			Nodo* max = _cima;
			Nodo* busca = _cima->_sig;
			Nodo* ant = NULL;
			Nodo* ant_max = NULL;

			while (busca != NULL) {
				if (max->_elem < busca->_elem) {
					max = busca;
					ant_max = ant;
				}
				ant = busca;
				busca = busca->_sig;
			}

			if (max != _cima) {
				ant_max->_sig = max->_sig;
				max->_sig = _cima;
				_cima = max;
			}
		}
	}
	void InsertaMinimioPorDebajoCima() {
		if (!esVacia()) {
			Nodo* min = _cima;
			Nodo* busca = _cima->_sig;
			Nodo* ant = NULL;
			Nodo* ant_min = NULL;

			while (busca != NULL) {
				if (min->_elem > busca->_elem) {
					min = busca;
					ant_min = ant;
				}
				ant = busca;
				busca = busca->_sig;
			}

			
		}
	}
	void InsertaPorPorEncimaCima() {

	}
	void llevaAlaCima(int pos) {

	}
	void inserta(const T& elem, int pos) {

	}
	void eliminaElem(const T& elem, int pos) {

	}
	void llevaAlaCima(const T& elem) {
		Nodo* it = _cima;
		Nodo* busca = _cima;

		Nodo* ant = NULL;
		Nodo* antBusca = NULL;
		if (!esVacia()) {
			while (it != NULL) {
				if (it->_elem == elem) {
					busca = it;
					antBusca = ant;
				}
				ant = it;
				it = it->_sig;
			}

			if (busca != _cima) {
				antBusca->_sig = busca->_sig;
				busca->_sig = _cima;
				_cima = busca;
			}
		}
	}*/
	/// <summary>
	/// Coste lineal, porque en el peor de los casos da n vueltas
	/// </summary>
	void minimoACima() {
		// IMPLEMENTA AQU� LA OPERACI�N
		
		if (!esVacia()) {
			Nodo* min = _cima;
			Nodo* busca = _cima->_sig;
			Nodo* ant = NULL;
			Nodo* ant_min = NULL;

			while (busca != NULL) {
				if (min->_elem > busca->_elem) {
					min = busca;
					ant_min = ant;
				}
				ant = busca;
				busca = busca->_sig;
			}

			if (min != _cima) {
				ant_min->_sig = min->_sig;
				min->_sig = _cima;
				_cima = min;
			}
		}
			
	}



	/** Constructor; operaci�n PilaVacia */
	Pila() : _cima(NULL) {
	}
	
	/**
	 Apila un elemento. Operaci�n generadora.

	 @param elem Elemento a apilar.
	*/
	void apila(const T &elem) {
		_cima = new Nodo(elem, _cima);
	}
	
	/**
	 Desapila un elemento. Operaci�n modificadora parcial.

	 error: falla si la pila est� vac�a
	*/
	void desapila() {
		if (esVacia())
			throw EPilaVacia();
		Nodo *aBorrar = _cima;
		_cima = _cima->_sig;
		delete aBorrar;
	}

	/**
	 Devuelve el elemento en la cima de la pila. Operaci�n
	 observadora parcial.

	 error: falla si la pila est� vac�a.
	 @return Elemento en la cima de la pila.
	 */
	const T &cima() const {
		if (esVacia())
			throw EPilaVacia();
		return _cima->_elem;
	}

	/**
	 Devuelve true si la pila no tiene ning�n elemento.

	 @return true si la pila no tiene ning�n elemento.
	 */
	bool esVacia() const {
		return _cima == NULL;
	}

	/** Destructor; elimina la lista enlazada. */
	~Pila() {
		libera();
		_cima = NULL;
	}

	/** Constructor copia */
	Pila(const Pila<T> &other) {
		copia(other);
	}

	/** Operador de asignaci�n */
	Pila<T> &operator=(const Pila<T> &other) {
		if (this != &other) { // no se intenta copiar una pila sobre s� misma
			libera();
			copia(other);
		}
		return *this;
	}

	/** Operador de comparaci�n. */
	bool operator==(const Pila<T> &rhs) const {
		Nodo *cima1 = _cima;
		Nodo *cima2 = rhs._cima;
		while ((cima1 != NULL) && (cima2 != NULL) && (cima1->_elem == cima2->_elem)) {
			cima1 = cima1->_sig;
			cima2 = cima2->_sig;
		}
		return (cima1 == NULL) && (cima2 == NULL);
	}

	bool operator!=(const Pila<T> &rhs) const {
		return !(*this == rhs);
	}

private:
	
	/**
	 Clase nodo que almacena internamente el elemento (de tipo T),
	 y un puntero al nodo siguiente, que podr�a ser NULL si
	 el nodo es el �ltimo de la lista enlazada.
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
	Elimina todos los nodos de la lista enlazada que soporta la pila. 
	*/
	void libera() {
		while (_cima != NULL) {
			Nodo *aBorrar = _cima;
			_cima = _cima->_sig;
			delete aBorrar;
		}
	}

	/**
	Genera una copia de other en la pila receptora
	*/
	void copia(const Pila &other) {
		if (other.esVacia()) 
			_cima = NULL;
		else {
			Nodo *puntAOrigen = other._cima; 
			Nodo *ultimo; 
			_cima = new Nodo(puntAOrigen->_elem); 
			ultimo = _cima; 
			while (puntAOrigen->_sig != NULL) { 
				puntAOrigen = puntAOrigen->_sig; 
				ultimo->_sig = new Nodo(puntAOrigen->_elem); 
				ultimo = ultimo->_sig; 
			}
		}
	}


	/** Puntero al primer elemento */
	Nodo *_cima;

	//Nodo* minimo(Nodo *a, Nodo *b) {
	//	return a->_elem < b->_elem ? a : b;
	//}

};

#endif // __PILA_LISTA_ENLAZADA_H
