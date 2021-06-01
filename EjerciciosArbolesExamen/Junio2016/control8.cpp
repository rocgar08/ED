#include "Arbin.h"
#include <iostream>
#include <string>
#include <algorithm>
/*
Planteamiento
*/
using namespace std;
bool esHoja(const Arbin<int>& cuenca) {
	return !cuenca.esVacio() && cuenca.hijoDer().esVacio() && cuenca.hijoIz().esVacio();
}
//O(n) 
int busca_navegable(const Arbin<int>& cuenca, int& cont) {
	//Opcion a
	int tramo = 0;
	if (cuenca.esVacio()) return 0;
	else if (esHoja(cuenca)) return 1;
	else {
		int tramoI = 0, tramoD = 0;
		
		tramoD = busca_navegable(cuenca.hijoDer(),cont);
		
		tramoI = busca_navegable(cuenca.hijoIz(), cont);

		tramo = tramoD + tramoI + cuenca.raiz();

		if (tramo >= 3) cont++;
		//Ojo que el tramo no puede ser negativo
		if(tramo< 0) cont = 0;
	}
	return tramo;

	//Opcion b
	//Casos base si es vacio y si esHoja
	//Caso recursivo
	/*
	   llevas el tramo por la derecha y por la izquierda
	   y el contador llevas los caudales por la Izquierda y por la derecha

	   int tramoI = 0, tramoD = 0, caudalIz, caudalDer;

		tramoD = busca_navegable(cuenca.hijoDer(),caudalDer);

		tramoI = busca_navegable(cuenca.hijoIz(), caudalIz);
		//contado = nivelCaudal
		cont = caudalDer + caudalIz - a.raiz();
		tramo = tramoD + tramoI;

		if(caudalDer>=3 || caudalIz>=3) tramo++;

		if(cont < 0 ) cont = 0;

		return tramo;


	*/
}

int numeroTramosNavegables(const Arbin<int>& cuenca) {
	//Opcion a
	int cont = 0;
	if (cuenca.esVacio()) return 0;
	
	int suma = busca_navegable(cuenca, cont);
	//o bien un embalse, en cuyo caso el nodo contiene un número negativo que representa cuanto caudal puede absorber el embalse
	if (suma >= 3) cont--; 
	return cont;

	//Opcion b
	/*
	if (cuenca.esVacio()) return 0;
	
	return busca_navegable(cuenca, cont)
	*/
	
}

Arbin<int> leeArbol(istream& in) {
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
		Arbin<int> iz = leeArbol(in);
		int raiz;
		in >> raiz;
		Arbin<int> dr = leeArbol(in);
		in >> c;
		return Arbin<int>(iz, raiz, dr);
	}
	default: return Arbin<int>();
	}
}

int main() {
	Arbin<int> cuenca;
	while (cin.peek() != EOF) {
		cout << numeroTramosNavegables(leeArbol(cin));
		string restoLinea;
		getline(cin, restoLinea);
		if (cin.peek() != EOF) cout << endl;
	}
	return 0;
}