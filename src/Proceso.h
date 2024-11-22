#ifndef PROCESO_H
#define PROCESO_H

#include <string>
using namespace std;

// Estructura Proceso
class Proceso
{
public:
    // Atributos
    string nombre;
    int prioridad;
    string instrucciones;
    Proceso *siguiente;
    string estado;

    // Constructor
    Proceso(const string &nombre_, int prioridad_);
};

#endif
