#include "Arbin.h"
#include <iostream>
#include <string>

using namespace std;

bool esHoja(const Arbin<int>& a) {
	return !a.esVacio() && a.hijoDer().esVacio() && a.hijoIz().esVacio();
}

/** Indica aqu�, razonadamente, la complejidad de numero_neutros
  La complejida es O(n) ya que solo se recorren los nodos una sola vez.
*/
void numero_adivinos_aux(const Arbin<int>& a, int& nodos, int& adivinosTotales) {
	int nodoI = 0, nodoD = 0;
	if (a.esVacio() && esHoja(a)) {
		nodos = 0;
		adivinosTotales = 0;
	}

	else {

		if (!a.hijoIz().esVacio()) numero_adivinos_aux(a.hijoIz(), nodoI, adivinosTotales);
		if (!a.hijoDer().esVacio()) numero_adivinos_aux(a.hijoDer(), nodoD, adivinosTotales);

		nodos = nodoI + nodoD;

		if (a.raiz() % 2 == 0) nodos++;
	}

	if (a.raiz() == nodoD + nodoI) adivinosTotales++;
	
}

unsigned int numero_adivinos(const Arbin<int>& a) {
	// A IMPLEMENTAR
	int nodos = 0, adivinos=0;
	if (!a.esVacio()) {
		numero_adivinos_aux(a, nodos, adivinos);
		return adivinos;
	}
	else return 0;


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
	while (cin.peek() != EOF) {
		Arbin<int> a = lee_arbol(cin);
		cout << numero_adivinos(a) << endl;
		string resto_linea;
		getline(cin, resto_linea);
	}
	return 0;
}