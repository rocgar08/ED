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
([9]2([2] - 1#))
((# - 1[2])2[9])
(([2]2[-2])4(#1[10]))
(([2] - 2[-2])4[10])
((([10]2[-10])3#)6(#3([10]2[10])))
((([1]1#) - 1#)10(#1(# - 1[1])))

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

void nuemero_neutro_aux(const Arbin<int>& a,unsigned int& nodosenutros,unsigned int& contadorneutros) {

	unsigned int nodosI = 0, nodoDer=0;
	//int cont = 0;
	//Si es hoja va incluido en la recursión
	if (a.esVacio()) contadorneutros = 0;
	else {
		if (!a.hijoDer().esVacio()) nuemero_neutro_aux(a.hijoDer(), nodoDer, contadorneutros);
		if (!a.hijoIz().esVacio())  nuemero_neutro_aux(a.hijoDer(), nodosI, contadorneutros);

		if (nodoDer == nodosI) 
			contadorneutros++;

		if (a.raiz() > 0)
			nodosenutros++;

		
		nodosenutros += (nodoDer + nodosI ) + (a.raiz() > 0);

	}

	
}
unsigned int numero_neutros(const Arbin<int>& a) {
	// A IMPLEMENTAR
	unsigned int nodos = 0, contar = 0;
	if (!a.esVacio()) {
		nuemero_neutro_aux(a, nodos, contar);
		return contar;
	}
	else
		return 0;
	
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
		cout << numero_neutros(a) << endl;
		string resto_linea;
		getline(cin, resto_linea);
	}
	return 0;
}
