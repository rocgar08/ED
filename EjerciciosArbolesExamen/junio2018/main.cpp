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

void salvando(const Arbin<char>& a,int c,int &numSalvo, bool esDama) {
	
	if (a.esVacio()) {
		numSalvo = 0;
	}
	else {
		int numIz = 0, numDer = 0;
		if (a.raiz() == 'C') c++;
		else if (a.raiz() == 'M') c--;
		else {
			esDama = true;
		}
	
		if (esDama && c >= 0) numSalvo++;

		salvando(a.hijoDer(),c,numDer,esDama);
		salvando(a.hijoIz(),c,numIz,esDama);

		numSalvo += numDer + numIz;

	}
	
}
int num_a_salvo(const Arbin<char>& a) {
	/*** A IMPLEMENTAR ***/
	int s = 0, c = 0,m=0;
	bool dama = false;
	salvando(a,c,s,dama);
	return s;
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
