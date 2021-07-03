// NOMBRE Y APELLIDOS:
// USUARIO DEL JUEZ:


#include "Arbin.h"
#include <iostream>
#include <string>

using namespace std;


/*
Determinar justificadamente la complejidad del algoritmo:

*/
bool esHoja(const Arbin<int>& a) {
	return !a.esVacio() && a.hijoDer().esVacio() && a.hijoIz().esVacio();
}
//Necesitamos un contador de nodos que es un  parametro de subida y de bajada
//Necesitamo la suma para saber cual es el valor del nodo
//el parametro de salida para saber si son correctivos o no
//Coste O(n), pasa 1 vez por cada nodo del árbol
//void numeros_aux(const Arbin<int>& a,int &contadornodos,int& suma, int& correctivos) {
//	int sumaD = 0, sumaI = 0, contI = 0, contD = 0;
//	if (a.esVacio()) correctivos = 0;
//	
//	else {
//		
//		if (!a.hijoDer().esVacio()) {
//			contD++;
//			numeros_aux(a.hijoDer(), contD, sumaD, correctivos);
//		}
//		if (!a.hijoIz().esVacio()) {
//			contI++;
//			numeros_aux(a.hijoIz(), contI, sumaI, correctivos);
//		}
//	
//		contadornodos = contD + contI + 1;
//
//		if(!a.hijoDer().esVacio() && 
//			a.raiz()== sumaD - contI) {
//			correctivos++;
//		}
//
//	}
//	suma = sumaD + sumaI + a.raiz();
//}
int numeros_aux(const Arbin<int>& a,int &contadornodos, int& correctivos) {
	int sumaD = 0, sumaI = 0, contI = 0, contD = 0;
	if (a.esVacio()) correctivos = 0;
	
	else {
		
		if (!a.hijoDer().esVacio()) {
			contD++;
			sumaD = numeros_aux(a.hijoDer(), contD, correctivos);
		}
		if (!a.hijoIz().esVacio()) {
			contI++;
			sumaI = numeros_aux(a.hijoIz(), contI,correctivos);
		}
	
		contadornodos = contD + contI + 1;

		if(!a.hijoDer().esVacio() && 
			a.raiz()== sumaD - contI) {
			correctivos++;
		}

	}
	return sumaD + sumaI + a.raiz();
}
int num_correctivos(const Arbin<int>& a) {
	// A IMPLEMENTAR
	int valor = 0, correc = 0, cont = 0;
	if (!a.esVacio()) {
		/*numeros_aux(a,cont,valor, correc);*/
		numeros_aux(a, cont, correc);
	}
	return correc;
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
		cout << num_correctivos(a) << endl;
		string resto_linea;
		getline(cin, resto_linea);
	}
	return 0;
}
