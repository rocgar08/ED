#include "cola.h"
#include <iostream>
using namespace std;

/**
Este programa lee por la entrada estándar líneas con el siguiente formato:
- Una secuencia de enteros (excluido el -1), que se interpreta como una
  cola.
- El -1 (centinela que marca el final de la cola)
- Una posición (entero >= 0)
Entonces, ejecuta la operación 'llevarAlPrincipio' sobre la cola indicada, y escribe
por pantalla el resultado (o POSICION_INVALIDA en caso de que la posición
no sea válida)

Ejemplo de entrada:
1 2 3 4 5 -1 1
1 2 3 4 5 -1 2
1 2 3 4 5 -1 3
1 2 3 4 5 -1 4
1 2 3 4 5 -1 5
1 2 3 4 5 -1 0 
1 2 3 4 5 -1 6 
-1 1 

Salida producida:
2 3 4 5 1
1 3 4 5 2
1 2 4 5 3
1 2 3 5 4
1 2 3 4 5
POSICION_INVALIDA
POSICION_INVALIDA
POSICION_INVALIDA

*/


bool lee_cola(Cola<int>& cola) {
	int v;
	if (cin >> v) {
	   while (v != -1) {
		  cola.pon(v);
		  cin >> v;
	   }
	   return true;
	}
	else return false;
}

int main() {
	Cola<int> cola;
	while (lee_cola(cola)) {
		int pos;
		cin >> pos;
		try {              
			cola.llevarAlFinal(pos);
			cola.print(); 
		}
		catch (EPosicionInvalida) {
			cout << "POSICION_INVALIDA" << endl;
		}
		cola = Cola<int>();
	}
}