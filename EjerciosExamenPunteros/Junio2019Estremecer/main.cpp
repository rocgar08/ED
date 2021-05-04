/*
NOMBRE Y APELLIDOS:
	Carla Pe�arrieta Uribe
	Rocio Garc�a N��ez
	Grupo 14
*/

#include <iostream>
#include "lista.h"
using namespace std;

bool lee_lista(Lista<int>& lista) {
	int n_elems;
	cin >> n_elems;
	if (n_elems >= 0) {
		while (n_elems-- != 0) {
			int elem;
			cin >> elem;
			lista.pon_final(elem);
		}
		return true;
	}
	else {
		return false;
	}
}

bool ejecuta_caso() {
	Lista<int> lista;
	if (lee_lista(lista)) {
		lista.estremece();
		lista.imprime();
		cout << "#";
		lista.imprime_inv();
		cout << endl;
		return true;
	}
	else {
		return false;
	}
}

int main() {
	while (ejecuta_caso());
	return 0;
}