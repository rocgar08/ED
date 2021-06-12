/*
NOMBRE Y APELLIDOS:

*/


#include "Arbin.h"
#include <iostream>
#include <string>
using namespace std;

int max_renta(int a, int b) {
	return a > b ? a : b;
}
bool esHoja(Arbin<int> a) {
	return !a.esVacio() && a.hijoDer().esVacio() && a.hijoIz().esVacio();
}
/* Puedes implementar aquí las funciones auxiliares que consideres
   oportuno */
//Coste O(n) ya que solo recorremos cada nodo 1 vez
void  esRentableAux(Arbin<int> a, int ancestros, int& renta_maxima, bool &rentable) {
	
	int rentaIzq = 0, rentaDer = 0;
	if (a.esVacio()) {
		rentable = false;
		renta_maxima = 0;
	}
	else if (esHoja(a)) {

		renta_maxima = max_renta(ancestros + a.raiz(), max_renta(rentaDer, rentaIzq));
		rentable = (a.raiz() > 0);
	}

	else {
	
		rentable = (ancestros + a.raiz() > 0);
		esRentableAux(a.hijoIz(), ancestros + a.raiz(), rentaIzq, rentable);
		esRentableAux(a.hijoDer(), ancestros + a.raiz(), rentaDer, rentable);
	
		renta_maxima = max_renta(rentaDer, rentaIzq);


	}

}

void muestra_solucion(bool rentable, int renta_max) {
	if (rentable) {
		cout << renta_max << endl;
	}
	else {
		cout << "NO_RENTABLE " << endl;
	}
}

/*
COMPLEJIDAD: Determina justificadamente la complejidad del procedimiento 

*/
void mejor_renta(Arbin<int> a, bool& es_rentable, int& renta_maxima) {
	/* A IMPLEMENTAR */
	int suma = 0;
	esRentableAux(a,suma, renta_maxima, es_rentable);

}


Arbin<int> lee_arbol(istream& in) {
	char c;
	in >> c;
	switch (c) {
	case '#': return Arbin<int>();
	case '[': {
		int raiz;
		in >> raiz;
  		in >> c;
		return Arbin<int>(raiz);
	}
	case '(': {
		Arbin<int> iz = lee_arbol(in);
		int raiz;
		in >> raiz;
		Arbin<int> dr = lee_arbol(in);
		in >> c;
		return Arbin<int>(iz, raiz, dr);
	}
	default: return Arbin<int>();
	}
}


int main() {
	Arbin<int> arbol;
	while (cin.peek() != EOF)  {
		Arbin<int> a = lee_arbol(cin);
		bool es_rentable;
		int renta_maxima;
		mejor_renta(a,es_rentable,renta_maxima);
		muestra_solucion(es_rentable,renta_maxima);
		string resto_linea;
		getline(cin, resto_linea);
	}
    return 0;       
}