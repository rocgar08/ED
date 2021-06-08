#include "Arbin.h"
#include <iostream>
#include <fstream>
#include <string>

/*
* Carla Paola Peñarrieta Uribe
* Rocío García Núñez
* B14
*/
using namespace std;

//Mejora
//Necesitamos llevar las horas_ac, y un contador de horas
//Si el arbol es vacio pues --> 0
//Si el arbol no esta vacio
//miramos el tiempoAux por la der y la iz, e incrementamos las horas en uno
//Si hay una intersecion las horas acumuladas += horas*2;

void tiempoAux(const Arbin<char>& falda,int& horas_ac, int horas) {

	if (falda.esVacio()) horas = 0;

		
	if(!falda.hijoIz().esVacio())
		tiempoAux(falda.hijoIz(), horas_ac, horas + 1);

	if (!falda.hijoDer().esVacio())
		tiempoAux(falda.hijoDer(), horas_ac, horas + 1);
		
	if (falda.raiz() == 'X') {
		horas_ac += horas * 2;
	}
	
}

int tiempoAyuda(const Arbin<char>& falda) {
	// A IMPLEMENTAR
  int horas_ac = 0;
  if (!falda.esVacio()) {
	  tiempoAux(falda, horas_ac, 0);
	 
  }
  return horas_ac;
}

Arbin<char> leeArbol(istream& in) {
	char c;
	in >> c;
	switch (c) {
	case '#': return Arbin<char>();
	case '[': {
		char raiz;
		in >> raiz;
		in >> c;
		return Arbin<char>(raiz);
	}
	case '(': {
		Arbin<char> iz = leeArbol(in);
		char raiz;
		in >> raiz;
		Arbin<char> dr = leeArbol(in);
		in >> c;
		return Arbin<char>(iz, raiz, dr);
	}
	default: return Arbin<char>();
	}
}

int main() {
	Arbin<char> falda;
	while (cin.peek() != EOF) {
		cout << tiempoAyuda(leeArbol(cin));
		string restoLinea;
		getline(cin, restoLinea);
		if (cin.peek() != EOF) cout << endl;
	}
	return 0;
}