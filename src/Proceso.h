#ifndef PROCESO_H
#define PROCESO_H

#include <string>
using namespace std;

// Estructura Proceso
struct Proceso {
    string nombre;
    int prioridad;
    string instrucciones;
    Proceso* siguiente;

    Proceso(const string& nombre_, int prioridad_);
};

#endif // PROCESO_H
