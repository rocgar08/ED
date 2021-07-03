/**
  NOMBRE Y APELLIDOS:
  USUARIO JUEZ:
*/

#include "paqueteria.h"

/**
 COMPLEJIDAD: Determina y justifica aqu� la complejidad de la operaci�n
*/
Paqueteria::Paqueteria() {
    // A IMPLEMENTAR

}

/**
 COMPLEJIDAD: Determina y justifica aqu� la complejidad de la operaci�n
 O(1) ya que las operaciones que usamos del hash como las de la lista son constantes
*/
void Paqueteria::recepciona_paquete(IdPaquete id, string dir, float peso) {
    // A IMPLEMENTAR
    if (_info.contiene(id)) throw EPaqueteDuplicado();
    _l_paquetes.pon_ppio(id);
    _info.inserta(id, InfoPaquete(dir, peso, _l_paquetes.begin()));

}

/**
 COMPLEJIDAD: Determina y justifica aqu� la complejidad de la operaci�n
 Como estamos consultando valor dentro de un hash es de coste constante
*/
void Paqueteria::info_paquete(IdPaquete id, string& dir, float& peso) const {
    // A IMPLEMENTAR
    DiccionarioHash<IdPaquete, InfoPaquete> ::ConstIterator it = _info.cbusca(id);
    id = it.clave();
    dir = it.valor()._dir;
    peso = it.valor()._peso;
}

/**
 COMPLEJIDAD: Determina y justifica aqu� la complejidad de la operaci�n
 Consultamos los elementos que tiene la lista por lo que la operacion es de coste constante
*/
bool Paqueteria::hay_paquetes() const {
    // A IMPLEMENTAR
    return(!_l_paquetes.esVacia());
}

/**
 COMPLEJIDAD: Determina y justifica aqu� la complejidad de la operaci�n
 cOMO LAS OPERACIONES QUE USAMOS DE LA LISTA TIENEN COSTE CONSTANTE, LA OPERACION ES O(1)
 */
void Paqueteria::primero_en_fila(IdPaquete& id) const {
    // A IMPLEMENTAR
    id = _l_paquetes.ultimo();
    if (_l_paquetes.esVacia()) throw ENingunPaqueteEnEspera();
}

/**
 COMPLEJIDAD: Determina y justifica aqu� la complejidad de la operaci�n
 Coste contante
 */
void Paqueteria::nuevo_camion(float peso) {
    // A IMPLEMENTAR
    _camiones.pon(peso);
}

/**
 COMPLEJIDAD: Determina y justifica aqu� la complejidad de la operaci�n
 Coste constante
*/
void Paqueteria::primer_camion(float& peso) const {
    // A IMPLEMENTAR
    if (_camiones.esVacia()) throw ENingunCamionEnEspera();
    peso = _camiones.primero();

}

/**
 COMPLEJIDAD: Determina y justifica aqu� la complejidad de la operaci�n
 coste lineal por la operacion de eliminar de la lista

*/
void Paqueteria::elimina(IdPaquete id) {
    // A IMPLEMENTAR
    DiccionarioHash<IdPaquete, InfoPaquete> ::Iterator it = _info.busca(id);
    if (it != _info.end()) {
        _l_paquetes.eliminar(it.valor()._pos);
        _info.borra(id);
    }
}

/**
 COMPLEJIDAD: Determina y justifica aqu� la complejidad de la operaci�n
 Esta es lineal seguro....
 carga el primer cami�n de la fila de camiones con el
mayor n�mero de paquetes en espera posible, tal que el peso total de dichos paquetes no
supere el peso que puede cargar el cami�n. La carga de los paquetes se realiza respetando
el orden de espera. Se devuelve una lista con los identificadores de los paquetes cargados
(el primero que esperaba ser� el primer elemento de la lista devuelta, el segundo que
esperaba ser� el segundo en la lista devuelta, y as� hasta el �ltimo paquete que se cargue),
y tanto la informaci�n del cami�n como la de los paquetes cargados en �l desparecen del
sistema. Obs�rvese que, en el caso de que el peso del primer paquete exceda el que admite
el cami�n, se devuelve una lista vac�a, y solo la informaci�n del cami�n desaparece del
sistema. Si no hay camiones esperando a ser cargados, o no hay paquetes esperando a ser
repartidos se eleva la excepci�n EErrorCarga.
*/
Lista<IdPaquete> Paqueteria::carga_camion() {
    // A IMPLEMENTAR
    Cola<float> aux;
    Lista<IdPaquete> l;
    DiccionarioHash<IdPaquete, InfoPaquete> ::Iterator it = _info.begin();
    Lista<IdPaquete> ::Iterator it_l = _l_paquetes.begin();
    unsigned int pesoPaquetes=0;
    if (it != _info.end()) {
        pesoPaquetes += it.valor()._peso;
        if (pesoPaquetes > _camiones.primero() || _l_paquetes.esVacia()) throw EErrorCarga();

        while (_l_paquetes.end() != it_l)
            if (!_camiones.esVacia()) {
                aux.pon(_camiones.primero());
                l.pon_ppio(it.clave());
                _camiones.quita();
                _l_paquetes.quita_final();
                it.next();
            }
            else return l;
    }
    return l;
  
}


   
