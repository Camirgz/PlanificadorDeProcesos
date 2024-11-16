#include "Proceso.h"

Proceso::Proceso(const string& nombre, int tiempoInicio) {
    this->nombre = nombre;  //this porque no sabe que nombre es
    this->tiempoInicio = tiempoInicio;
    instrucciones = "";
    siguiente = nullptr;
}
    

