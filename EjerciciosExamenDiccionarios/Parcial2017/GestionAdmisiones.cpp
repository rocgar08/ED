/**
  NOMBRE Y APELLIDOS:
  LABORATORIO:
  PUESTO:
  USUARIO DE DOMJUDGE USADO EN EL EXAMEN:
*/

#include "GestionAdmisiones.h"
#include <iostream>

/** 
Implementación de las operaciones de la clase Paciente 
*/

Paciente::Paciente(const string& nombre, unsigned int edad, const string& sintomas):
    _nombre(nombre),  _sintomas(sintomas), _edad(edad) {}	

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
const Paciente& InfoPaciente::datos() const
{
	// TODO: Insertar una instrucción "return" aquí
	return _paciente;
}

const Gravedad& InfoPaciente::gravedades() const
{
	// TODO: Insertar una instrucción "return" aquí
	return _gravedad;
}


 
/**
Debes completar la implementación de las operaciones de GestionAdmisiones,
y justificar la complejidad de los mismos.
*/ 


/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
*/
GestionAdmisiones::GestionAdmisiones() {
	// A IMPLEMENTAR

}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
*/
void GestionAdmisiones::an_paciente(CodigoPaciente codigo, const string& nombre, unsigned int edad, const string& sintomas, Gravedad gravedad) {
	// A IMPLEMENTAR
	
	if(_pacientes.contiene(codigo)) throw EPacienteDuplicado(); //O(1)
	
	_esperas[gravedad].pon_ppio(codigo);
	_pacientes.inserta(codigo, InfoPaciente(
		Paciente(nombre,edad,sintomas),
		gravedad,_esperas[gravedad].begin())
	);//O(1)

	

}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
*/
void GestionAdmisiones::info_paciente(CodigoPaciente codigo, string& nombre, unsigned int& edad, string& sintomas) const {
	// A IMPLEMENTAR
	DiccionarioHash<CodigoPaciente, InfoPaciente> ::ConstIterator it = _pacientes.cbusca(codigo); //O(1)

	if (it == _pacientes.cend()) throw EPacienteNoExiste(); //cte
	
	nombre = it.valor().datos().nombre();
	edad = it.valor().datos().edad();
	sintomas = it.valor().datos().sintomas();
	
	
	
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
*/

void GestionAdmisiones::siguiente(CodigoPaciente& codigo, Gravedad& gravedad) const {
	// A IMPLEMENTAR
	
	if (!_esperas[GRAVE].esVacia()) {
		codigo = _esperas[GRAVE].ultimo();
		gravedad = GRAVE;
	}

	else if (!_esperas[NORMAL].esVacia()) {
		codigo = _esperas[NORMAL].ultimo();
		gravedad = NORMAL;
	}

	else {
		codigo = _esperas[LEVE].ultimo();
		gravedad = LEVE;
	}
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
*/
bool GestionAdmisiones::hay_pacientes() const {  
	// A IMPLEMENTAR
	return (!_esperas[3].esVacia());
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
*/
void GestionAdmisiones::elimina(CodigoPaciente codigo) {

	DiccionarioHash<CodigoPaciente, InfoPaciente> ::Iterator it = _pacientes.busca(codigo);

	if (it == _pacientes.end()) throw EPacienteNoExiste(); //Si no está en el diccionario
	if (hay_pacientes()){
		Lista<CodigoPaciente> ::Iterator ini = _esperas[it.valor().gravedades()].begin();
		if (ini != _esperas[it.valor().gravedades()].end()) {
			_esperas[it.valor().gravedades()].eliminar(it.valor()._pos);
			_pacientes.borra(codigo);
		}
	}
	
}
   

