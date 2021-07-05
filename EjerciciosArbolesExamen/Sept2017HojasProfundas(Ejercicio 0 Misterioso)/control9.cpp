
#include "Arbin.h"
#include <iostream>
#include <string>

using namespace std;

bool esHoja(const Arbin<int>& a) {
	return !a.esVacio() && a.hijoIz().esVacio() && a.hijoDer().esVacio();
}
//O(n)
unsigned int numHojasProfundas(Arbin<int> a, unsigned int k, unsigned NIVEL) {

	if (a.esVacio()) return 0;
	else if (esHoja(a)) {
		if (NIVEL > k) return 1;
	}
	else 
		return numHojasProfundas(a.hijoDer(), k, NIVEL + 1) + numHojasProfundas(a.hijoIz(), k, NIVEL + 1);

}

unsigned int numero_hojas_mas_profundas_que(Arbin<int> a, unsigned int k) {
	// A IMPLEMENTAR
	unsigned nivel = 1;
	return numHojasProfundas(a, k, nivel);
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
		int k;
		cin >> k;
		cout << numero_hojas_mas_profundas_que(a, k) << endl;
		string resto_linea;
		getline(cin, resto_linea);
	}
	return 0;
}