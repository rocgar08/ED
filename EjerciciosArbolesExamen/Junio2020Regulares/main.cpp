#include "Arbin.h"
#include <iostream>
#include <string>

using namespace std;



int mini(int a, int b) {
	return a < b ? a : b;
}
int maxi(int a, int b) {
	return a < b ? b : a;
}

/* Determina aquí justificadamente la complejidad de numero_regulares

*/
//Coste O(n) ya que solo se recorren los nodos una sola vez
unsigned int num_regulares_aux(const Arbin<int>& a, int min_ancestros, int max_descendientes, int& totalReg) {
	if (a.esVacio()) {
		min_ancestros = 0;
		max_descendientes = 0;
		return 0;
	}
	else {
		
		int numRegIz = num_regulares_aux(a.hijoIz(), mini(min_ancestros, a.raiz()), max_descendientes, totalReg);
		int numRegDer = num_regulares_aux(a.hijoDer(), mini(min_ancestros, a.raiz()), max_descendientes, totalReg);

		max_descendientes = maxi(numRegIz, numRegDer);
		if (a.raiz() > max_descendientes && a.raiz() < min_ancestros) totalReg++;
	}
	return maxi(a.raiz(), max_descendientes);
}
unsigned int numero_regulares(const Arbin<int>& a) {
	 // A IMPLEMENTAR
	int cont = 0;
	num_regulares_aux(a, 10000, -10000, cont);
	return cont;
	 
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
		cout << numero_regulares(a) << endl;
		string resto_linea;
		getline(cin, resto_linea);
	}
	return 0;
}
