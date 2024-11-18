#ifndef PROCESO_H
#define PROCESO_H

#include <string>
using namespace std;

// Estructura Proceso
struct Proceso {

    // Atributos
    string nombre;
    int prioridad;
    string instrucciones;
    Proceso* siguiente;

    // Constructor
    Proceso(const string& nombre_, int prioridad_);
};

#endif 
