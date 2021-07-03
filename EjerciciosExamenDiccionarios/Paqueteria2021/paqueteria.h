/**
  NOMBRE Y APELLIDOS:
  USUARIO JUEZ:
*/

#ifndef _paqueteria_H
#define _paqueteria_H

#include "lista.h"  
#include <string>
#include "DiccionarioHash.h"
#include "cola.h"
using namespace std;

// clases para las excepciones
class EPaqueteDuplicado {};

class EPaqueteInexistente {};

class ENingunPaqueteEnEspera {};

class ENingunCamionEnEspera {};

class EErrorCarga {};

// tipo identificador paquete
typedef unsigned int IdPaquete;  



class Paqueteria {
public:
   Paqueteria();
   void recepciona_paquete(IdPaquete id, string dir, float peso);
   void info_paquete(IdPaquete id, string& dir, float& peso) const;
   void primero_en_fila(IdPaquete& id) const;
   void nuevo_camion(float peso);
   void primer_camion(float& peso) const;
   void elimina(IdPaquete id);
   bool hay_paquetes() const;
   Lista<IdPaquete> carga_camion();
private:
	class InfoPaquete {
	public:
		string _dir;
		float _peso;
		Lista<IdPaquete>::Iterator _pos;
		InfoPaquete(const string& dir, const float& peso, Lista<IdPaquete>::Iterator pos) :
			_dir(dir),
			_peso(peso),
			_pos(pos){
		};
	};
	DiccionarioHash<IdPaquete, InfoPaquete> _info;
	Lista<IdPaquete> _l_paquetes;
	Cola<float> _camiones;
};

#endif