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
bool esHoja(const Arbin<int>& a) {
	return !a.esVacio() && a.hijoDer().esVacio() && a.hijoIz().esVacio();
}
//Plantilla que sigue, a veces simplemente es reordenar las condiciones
/*
* INT AUX(a,suma_ac, cont){
* 
*	if(esVacio()) RETURN 0;
*	ELSE{
*		IF ESHOJA
*			//VARIANTE 1
*			IF SUMA_AC == SUMA CONT ++
*			//VARIANTE 2
*			SUMA_AC+=A.RAIZ()
*		//SI NO ES HOJA
*		SUMA = HI + HD
*		
*	}
* }
*/
int  numCuriosoAux(const Arbin<int>& a,int suma_ac,int& cont) {
	int suma = 0;
	if (a.esVacio()) return 0;
	else {

		suma = numCuriosoAux(a.hijoDer(), suma_ac + a.raiz(),cont) +
				numCuriosoAux(a.hijoIz(), suma_ac + a.raiz(),cont);

		if (suma_ac == suma)
			cont++;
	}
	return suma + a.raiz();
 }
	
int num_curiosos(const Arbin<int>& a) {
  	/*** A IMPLEMENTAR ***/
	int nc = 0;

	if(!a.esVacio())
		numCuriosoAux(a,0,nc);
	return nc;
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

void escribe_arbol(Arbin<int> a) {
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
	Arbin<int> arbol;
	while (cin.peek() != EOF)  {
		arbol = lee_arbol(cin);
		escribe_arbol(arbol);
		cout << " => " << num_curiosos(arbol);
		string resto_linea;
		getline(cin, resto_linea);
		if (cin.peek() != EOF) cout << endl;
	}
	return 0;
}
