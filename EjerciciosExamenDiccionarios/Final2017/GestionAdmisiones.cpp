/**
  NOMBRE Y APELLIDOS:
  LABORATORIO:
  PUESTO:
  USUARIO DE DOMJUDGE USADO EN EL EXAMEN:
*/

#include "GestionAdmisiones.h"
#include "hash.h"
#include "lista.h"
/** 
Implementación de las operaciones de la clase Paciente 
*/

Paciente::Paciente()
{
}

Paciente::Paciente(const string& nombre, unsigned int edad, const string& sintomas):
    _nombre(nombre), _sintomas(sintomas), _edad(edad) {}	

unsigned int Paciente::edad() const {
   return _edad;	
}
const string& Paciente::nombre() const {
   return _nombre;	
}
const string& Paciente::sintomas() const {
   return _sintomas;	
}



/**
Implementa aquí los métodos de las clases adicionales
*/



InfoPaciente::InfoPaciente(const Paciente& paciente, const Lista<CodigoPaciente>::Iterator& posicion) :
	_paciente(paciente), _pos(posicion) {};
const Paciente& InfoPaciente::datos() const
{
	// TODO: Insertar una instrucción "return" aquí
	return _paciente;
}
const Lista<CodigoPaciente>::Iterator& InfoPaciente::posicion() const
{
	// TODO: Insertar una instrucción "return" aquí
	return _pos;
}
;
/**
Debes completar la implementación de las operaciones de GestionAdmisiones,
y justificar la complejidad de las mismas.
*/ 

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
*/
GestionAdmisiones::GestionAdmisiones() {
	// A IMPLEMENTAR
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
 //O(1) ya que todas las operaciones del hash y la de la lista son constantes
*/
void GestionAdmisiones::an_paciente(CodigoPaciente codigo, const string& nombre, unsigned int edad, const string& sintomas) {
	// A IMPLEMENTAR
	if (_info.contiene(codigo)) throw EPacienteDuplicado(); // 0(1)
	//Actualizamos la lista y el diccionario
	else {
		_lista_espera.pon_ppio(codigo); //O(1)
		_info.inserta(codigo, InfoPaciente(Paciente(nombre, edad, sintomas),_lista_espera.end()));//O(1)
	}
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
*/

//O(1) Todas las operaciones del diccionario tienen coste constante y actualizar los datos del paciente tambien es coste constante;
//Ojo que el orden de las cosas importa 
void GestionAdmisiones::info_paciente(CodigoPaciente codigo, string& nombre, unsigned int& edad, string& sintomas) const
{
	DiccionarioHash<CodigoPaciente, InfoPaciente>::ConstIterator ini = _info.cbusca(codigo);
	DiccionarioHash<CodigoPaciente, InfoPaciente>::ConstIterator fin = _info.cend();

	if(ini == fin) throw EPacienteNoExiste();

	Paciente p;
	p = ini.valor().datos();
	nombre = p.nombre();
	edad = p.edad();
	sintomas = p.sintomas();
	
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
 O(1) Melona que para acceder al siguiente en una lista, tal y como esta planteado tienes que acceder al 1º elemento
*/
void GestionAdmisiones::siguiente(CodigoPaciente& codigo) const {
  // A IMPLEMENTAR
	DiccionarioHash<CodigoPaciente, InfoPaciente>::ConstIterator ini = _info.cbusca(codigo);
	
	if (_lista_espera.esVacia()) throw ENoHayPacientes();
	codigo = _lista_espera.primero();
	
		
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
*/
//O(1)
bool GestionAdmisiones::hay_pacientes() const {  
  // A IMPLEMENTAR
	return (!_lista_espera.esVacia());
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
 //0(1)
*/
void GestionAdmisiones::elimina(CodigoPaciente codigo) {
	// A IMPLEMENTAR
	DiccionarioHash<CodigoPaciente, InfoPaciente> ::Iterator it = _info.busca(codigo);

	if (it == _info.end()) throw EPacienteNoExiste(); //Si no está en la lista

	
	Lista<CodigoPaciente> ::Iterator ini = _lista_espera.begin();
	if (ini.elem()== codigo) {
		if (ini != _lista_espera.end())
			_lista_espera.eliminar(ini);
	}

	_info.borra(codigo);
		
}


