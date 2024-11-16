#ifndef PROCESO_H
#define PROCESO_H

#include <string>
using namespace std;

// Estructura Proceso
struct Proceso {
    string nombre;
    int tiempoInicio;
    string instrucciones;
    Proceso* siguiente;

    Proceso(const string& nombre_, int tiempoInicio_);
};

#endif // PROCESO_H
