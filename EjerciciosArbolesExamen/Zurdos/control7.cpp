
#include "Arbin.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

bool esHoja(Arbin<int> a) {
	return !a.esVacio() && a.hijoDer().esVacio() && a.hijoIz().esVacio();
}

//La complejida es O(n) ya que solo se recorren los nodos una sola vez.
bool zurdo_aux(Arbin<int> a,int& suma, int& altura) {
	int sumI = 0, sumD = 0;
	if (a.esVacio()) {
		altura = 0;
		return false;
	}
	else if (esHoja(a)) {
		altura = 1;
		suma = a.raiz();
		return true;
	}
	else {
		int alturaIzq = 0, alturaDer = 0;
		if (zurdo_aux(a.hijoDer(), sumD, alturaDer) && zurdo_aux(a.hijoIz(), sumI, alturaIzq)) {
			suma = sumD + sumI + a.raiz();
			altura = 1 + max(alturaDer, alturaIzq);
			return (sumI - sumD >= altura);
		}
		
	}
}

bool es_zurdo(Arbin<int> a) {
	int min = -1000, sum =0;
	return !a.esVacio() ? zurdo_aux(a,sum,min) : false;
}

//-----------------------------------------------------------------------
// Código que se encarga de la e/s: no tocar
//o


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


/**
La entrada al programa consiste de líneas formadas por árboles de enteros
codificados de acuerdo con las siguientes reglas:
(1) El árbol vacío se codifica como #
(2) Los árboles simples se codifican como [v], con
	v el valor del nodo
(3) Los árboles complejos se codifican como (IvD),
	con I la codificación del hijo izquierdo,
	v el valor de la raíz, y D la codificación
	del hijo derecho.
Para cada línea leida, escribe en la salida estádar
ZURDO si el árbol es zurdo, y NO_ZURDO en otro caso

Ejemplo de entrada:
#
[5]
([17]5([2]1[3]))
(([2]1[3])5[17])

Salida asociada:
NO_ZURDO
ZURDO
ZURDO
NO_ZURDO


*/

int main() {
	Arbin<int> arbol;
	while (cin.peek() != EOF) {
		Arbin<int> a = lee_arbol(cin);
		string resto_linea;
		getline(cin, resto_linea);
		if (es_zurdo(a)) cout << "ZURDO";
		else cout << "NO_ZURDO";
		cout << endl;
	}
	return 0;
}