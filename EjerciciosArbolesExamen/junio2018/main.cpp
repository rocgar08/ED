#include "Arbin.h"
#include <iostream>
#include <string>

using namespace std;


/**
  FUNCION A IMPLEMENTAR.
  Aparte de esta función, puedes implementar todas las funciones auxiliares que
  consideres oportuno. 
  Debes describir y justificar aquí la complejidad de la implementación realizada:
  
  

*/
void num_a_salvo_aux(const Arbin<char>& a, int& caballeros, int& mounstros, int& salvados) {

	if (a.esVacio()) {
		salvados = 0;
	}

	if (a.raiz() == 'M')
		mounstros++;

	int caballerosIzq = 0, caballerosDer = 0;

	if (!a.hijoIz().esVacio())	num_a_salvo_aux(a.hijoIz(), caballerosIzq, mounstros, salvados);
	if (!a.hijoDer().esVacio()) num_a_salvo_aux(a.hijoDer(), caballerosDer, mounstros, salvados);

	caballeros = caballerosIzq + caballerosDer;

	if (a.raiz() == 'C')
		caballeros++;
	if (a.raiz() == 'M')
		mounstros--;
	else if (caballeros >= mounstros && a.raiz() == 'D')
		salvados++;
}
int num_a_salvo(const Arbin<char>& a) {
	/*** A IMPLEMENTAR ***/
	int caballeros = 0, mounstros = 0, salvados = 0;
	if (!a.esVacio()) num_a_salvo_aux(a, caballeros, mounstros, salvados);
	return salvados;
}



Arbin<char> lee_arbol(istream& in) {
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
		Arbin<char> iz = lee_arbol(in);
		char raiz;
		in >> raiz;
		Arbin<char> dr = lee_arbol(in);
		in >> c;
		return Arbin<char>(iz, raiz, dr);
	}
	default: return Arbin<char>();
	}
}


void escribe_arbol(Arbin<char> a) {
	if (a.esVacio()) cout << "#";
	else if (a.hijoIz().esVacio() && a.hijoDer().esVacio()) cout << "[" << a.raiz() << "]";
	else {
		cout << "("; 
		escribe_arbol(a.hijoIz()); 
		cout << a.raiz(); 
		escribe_arbol(a.hijoDer());
		cout << ")";
	}
}


int main() {
	Arbin<char> arbol;
	while (cin.peek() != EOF)  {
		Arbin<char> mapa = lee_arbol(cin);
		cout << "num_a_salvo ";
		escribe_arbol(mapa);
		cout << " => ";
		cout << num_a_salvo(mapa);
		string resto_linea;
		getline(cin, resto_linea);
		if (cin.peek() != EOF) cout << endl;
	}
	return 0;
}
