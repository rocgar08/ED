#include "Arbin.h"
#include <iostream>
#include <string>
using namespace std;



/*
 COMPLEJIDAD: Justifica la complejidad de tu
algoritmo. 
 
 
*/

/**
*  SI ES VACIO --> 0
*  SI ES HOJA --> 0
*  SI NO
*	valor = HI + HD
* IF a.raiz() == valor 
*	CUENTA++
* 
* 
*/
bool esHoja(Arbin<int> a) {
	return !a.esVacio() && a.hijoDer().esVacio() && a.hijoIz().esVacio();
}
unsigned int sumativos(Arbin<int> a,int& cuenta) {
	
	int valor = 0, vI = 0, vD = 0;

	if (a.esVacio()) return 0;
	else {

		vI = sumativos(a.hijoIz(), cuenta);
		vD = sumativos(a.hijoDer(), cuenta);
		valor = vD + vI;
		if (a.raiz() == valor) {
			cuenta++;
		}
	}
	
	return vD + a.raiz();
}
unsigned int numNodosSumativos (Arbin<int> a) {
	/* A IMPLEMENTAR */

	if (a.esVacio()) return 0;
	int cuenta = 0;
	sumativos(a,cuenta);
	return cuenta;
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
		unsigned int resultado = numNodosSumativos(a);
		cout << resultado << endl;
		string resto_linea;
		getline(cin, resto_linea);
	}
    return 0;       
}