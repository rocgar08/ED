#include "Arbin.h"
#include <iostream>
#include <string>

using namespace std;


/*Ejemplo de entrada
==================
#
[10]
([1]5[3])
([1]5#)
(#5[3])
([9]2([2]1#))
([9]2([2]-1#))
((#-1[2])2[9])
(([2]2[-2])4(#1[10]))
(([2]-2[-2])4[10])
((([10]2[-10])3#)6(#3([10]2[10])))
((([1]1#)-1#)10(#1(#-1[1])))

Salida asociada
============== =
0
1
3
1
1
2
3
3
4
4
5
3
*/
/** Indica aquí, razonadamente, la complejidad de numero_neutros

*/
bool esHoja(const Arbin<int>& a) {
	return !a.esVacio() && a.hijoDer().esVacio() && a.hijoIz().esVacio();
}
//0(n) ya que recorre 1 sola vez los nodos del arbol
void nuemero_neutro_aux(const Arbin<int>& a, int& neutroTotales, int& nodo) {

	if (a.esVacio()) {
		neutroTotales = 0;
		nodo = 0;
	}

	else {
		int nodoD = 0, nodoI = 0;

		if (!a.hijoDer().esVacio())
			nuemero_neutro_aux(a.hijoDer(), neutroTotales, nodoD);
		if (!a.hijoIz().esVacio())
			nuemero_neutro_aux(a.hijoIz(), neutroTotales, nodoI);

		if (nodoD == nodoI) neutroTotales++;

		if (a.raiz() > 0) nodo++;

		nodo += nodoD + nodoI;
	}

}

unsigned int numero_neutros(const Arbin<int>& a) {
	// A IMPLEMENTAR
	int nodos = 0, contar = 0;
	if (a.esVacio()) return 0;
	nuemero_neutro_aux(a, contar, nodos);
	return contar;
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
		cout << numero_neutros(a) << endl;
		string resto_linea;
		getline(cin, resto_linea);
	}
	return 0;
}
